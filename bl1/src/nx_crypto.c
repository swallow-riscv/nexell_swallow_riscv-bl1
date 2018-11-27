/*
 * Copyright (C) 2016  Nexell Co., Ltd.
 * Author: Sangjong, Han <hans@nexell.co.kr>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <nx_swallow.h>

#if defined(QEMU_RISCV) || defined(SOC_SIM)
#include <nx_qemu_sim_printf.h>
#else
#ifdef DEBUG
#include <nx_swallow_printf.h>
#endif
#endif

#include <nx_crypto.h>
#include <nx_chip_iomux.h>
#include <nx_gpio.h>
#include <nx_clock.h>
#include <nx_lib.h>

#ifdef SW_CRYPTO_EMUL
unsigned int erk[64];
unsigned int drk[64]; /* decryption round keys */
int nr;      /* number of rounds */

/* uncomment the following line to use pre-computed tables */
/* otherwise the tables will be generated at the first run */

/* forward S-box & tables */

unsigned int FSb[256];
unsigned int FT0[256];
unsigned int FT1[256];
unsigned int FT2[256];
unsigned int FT3[256];

/* reverse S-box & tables */

unsigned int RSb[256];
unsigned int RT0[256];
unsigned int RT1[256];
unsigned int RT2[256];
unsigned int RT3[256];

/* round constants */

unsigned int RCON[10];

/* tables generation flag */

int do_init = 1;

/* tables generation routine */

#define ROTR8(x) (((x << 24) & 0xFFFFFFFF) | ((x & 0xFFFFFFFF) >> 8))

#define XTIME(x) ( ( x <<  1 ) ^ ( ( x & 0x80 ) ? 0x1B : 0x00 ) )
#define MUL(x,y) ( ( x &&  y ) ? pow[(log[x] + log[y]) % 255] : 0 )

void aes_gen_tables(void)
{
	int i;
	unsigned short x, y;
	unsigned short pow[256];
	unsigned short log[256];

	/* compute pow and log tables over GF(2^8) */
	for (i = 0, x = 1; i < 256; i++, x ^= XTIME(x)) {
		pow[i] = x;
		log[x] = i;
	}

	/* calculate the round constants */
	for (i = 0, x = 1; i < 10; i++, x = XTIME(x)) {
		RCON[i] = (unsigned int)x << 24;
	}

	/* generate the forward and reverse S-boxes */
	FSb[0x00] = 0x63;
	RSb[0x63] = 0x00;

	for (i = 1; i < 256; i++) {
		x = pow[255 - log[i]];

		y = x;  y = ( y << 1 ) | ( y >> 7 );
		x ^= y; y = ( y << 1 ) | ( y >> 7 );
		x ^= y; y = ( y << 1 ) | ( y >> 7 );
		x ^= y; y = ( y << 1 ) | ( y >> 7 );
		x ^= y ^ 0x63;

		FSb[i] = x;
		RSb[x] = i;
	}

	/* generate the forward and reverse tables */
	for (i = 0; i < 256; i++) {
		x = (unsigned short)FSb[i];
		y = XTIME(x);

		FT0[i] = (unsigned int)(x ^ y) ^ ((unsigned int)x << 8) ^ ((unsigned int)x << 16) ^
			((unsigned int)y << 24);

		FT0[i] &= 0xFFFFFFFF;

		FT1[i] = ROTR8(FT0[i]);
		FT2[i] = ROTR8(FT1[i]);
		FT3[i] = ROTR8(FT2[i]);

		y = (unsigned char)RSb[i];

		RT0[i] = ((unsigned int)MUL(0x0B, y)) ^ ((unsigned int)MUL(0x0D, y) << 8) ^
			((unsigned int)MUL(0x09, y) << 16) ^ ((unsigned int)MUL(0x0E, y) << 24);

		RT0[i] &= 0xFFFFFFFF;

		RT1[i] = ROTR8(RT0[i]);
		RT2[i] = ROTR8(RT1[i]);
		RT3[i] = ROTR8(RT2[i]);
	}
}

/* platform-independant 32-bit integer manipulation macros */

#define GET_UINT32(n,b,i)					\
{											\
	(n) = ( (unsigned int) (b)[(i)    ] << 24 )		\
	| ( (unsigned int) (b)[(i) + 1] << 16 )		\
	| ( (unsigned int) (b)[(i) + 2] <<  8 ) 		\
	| ( (unsigned int) (b)[(i) + 3]       );		\
}

#define PUT_UINT32(n,b,i)					\
{											\
	(b)[(i)    ] = (unsigned short) ( (n) >> 24 );		\
	(b)[(i) + 1] = (unsigned short) ( (n) >> 16 );		\
	(b)[(i) + 2] = (unsigned short) ( (n) >>  8 );		\
	(b)[(i) + 3] = (unsigned short) ( (n)       );		\
}

/* decryption key schedule tables */

int KT_init = 1;

unsigned int KT0[256];
unsigned int KT1[256];
unsigned int KT2[256];
unsigned int KT3[256];

/* AES key scheduling routine */

int aes_set_key(unsigned short *key, int nbits)
{
	int i;
	unsigned int *RK, *SK;

	if (do_init) {
		aes_gen_tables();

		do_init = 0;
	}

	nr = 10;
	RK = erk;

	for (i = 0; i < (nbits >> 5); i++) {
		GET_UINT32(RK[i], key, i * 4);
	}

	/* setup encryption round keys */

	for( i = 0; i < 10; i++, RK += 4 ) {
		RK[4]  = RK[0] ^ RCON[i] ^
			( FSb[ (unsigned short) ( RK[3] >> 16 ) ] << 24 ) ^
			( FSb[ (unsigned short) ( RK[3] >>  8 ) ] << 16 ) ^
			( FSb[ (unsigned short) ( RK[3]       ) ] <<  8 ) ^
			( FSb[ (unsigned short) ( RK[3] >> 24 ) ]       );

		RK[5] = RK[1] ^ RK[4];
		RK[6] = RK[2] ^ RK[5];
		RK[7] = RK[3] ^ RK[6];
	}

	/* setup decryption round keys */

	if (KT_init) {
		for (i = 0; i < 256; i++) {
			KT0[i] = RT0[FSb[i]];
			KT1[i] = RT1[FSb[i]];
			KT2[i] = RT2[FSb[i]];
			KT3[i] = RT3[FSb[i]];
		}

		KT_init = 0;
	}

	SK = drk;

	*SK++ = *RK++;
	*SK++ = *RK++;
	*SK++ = *RK++;
	*SK++ = *RK++;

	for (i = 1; i < nr; i++) {
		RK -= 8;

		*SK++ = KT0[ (unsigned short) ( *RK >> 24 ) ] ^
			KT1[ (unsigned short) ( *RK >> 16 ) ] ^
			KT2[ (unsigned short) ( *RK >>  8 ) ] ^
			KT3[ (unsigned short) ( *RK       ) ]; RK++;

		*SK++ = KT0[ (unsigned short) ( *RK >> 24 ) ] ^
			KT1[ (unsigned short) ( *RK >> 16 ) ] ^
			KT2[ (unsigned short) ( *RK >>  8 ) ] ^
			KT3[ (unsigned short) ( *RK       ) ]; RK++;

		*SK++ = KT0[ (unsigned short) ( *RK >> 24 ) ] ^
			KT1[ (unsigned short) ( *RK >> 16 ) ] ^
			KT2[ (unsigned short) ( *RK >>  8 ) ] ^
			KT3[ (unsigned short) ( *RK       ) ]; RK++;

		*SK++ = KT0[ (unsigned short) ( *RK >> 24 ) ] ^
			KT1[ (unsigned short) ( *RK >> 16 ) ] ^
			KT2[ (unsigned short) ( *RK >>  8 ) ] ^
			KT3[ (unsigned short) ( *RK       ) ]; RK++;
	}

	RK -= 8;

	*SK++ = *RK++;
	*SK++ = *RK++;
	*SK++ = *RK++;
	*SK++ = *RK++;

	return (0);
}

/* AES 128-bit block decryption routine */

void aes_decrypt(unsigned short input[16], unsigned short output[16])
{
	unsigned int *RK, X0, X1, X2, X3, Y0, Y1, Y2, Y3;

	RK = drk;

	GET_UINT32( X0, input,  0 ); X0 ^= RK[0];
	GET_UINT32( X1, input,  4 ); X1 ^= RK[1];
	GET_UINT32( X2, input,  8 ); X2 ^= RK[2];
	GET_UINT32( X3, input, 12 ); X3 ^= RK[3];

#define AES_RROUND(X0,X1,X2,X3,Y0,Y1,Y2,Y3)     \
	{                                               \
		RK += 4;                                    \
		\
		X0 = RK[0] ^ RT0[ (unsigned short) ( Y0 >> 24 ) ] ^ 	\
		RT1[ (unsigned short) ( Y3 >> 16 ) ] ^		\
		RT2[ (unsigned short) ( Y2 >>  8 ) ] ^		\
		RT3[ (unsigned short) ( Y1       ) ]; 		\
		\
		X1 = RK[1] ^ RT0[ (unsigned short) ( Y1 >> 24 ) ] ^		\
		RT1[ (unsigned short) ( Y0 >> 16 ) ] ^		\
		RT2[ (unsigned short) ( Y3 >>  8 ) ] ^		\
		RT3[ (unsigned short) ( Y2       ) ];		\
		\
		X2 = RK[2] ^ RT0[ (unsigned short) ( Y2 >> 24 ) ] ^ 	\
		RT1[ (unsigned short) ( Y1 >> 16 ) ] ^ 	\
		RT2[ (unsigned short) ( Y0 >>  8 ) ] ^ 	\
		RT3[ (unsigned short) ( Y3       ) ]; 		\
		\
		X3 = RK[3] ^ RT0[ (unsigned short) ( Y3 >> 24 ) ] ^ 	\
		RT1[ (unsigned short) ( Y2 >> 16 ) ] ^ 	\
		RT2[ (unsigned short) ( Y1 >>  8 ) ] ^ 	\
		RT3[ (unsigned short) ( Y0       ) ]; 		\
	}

	AES_RROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );       /* round 1 */
	AES_RROUND( X0, X1, X2, X3, Y0, Y1, Y2, Y3 );       /* round 2 */
	AES_RROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );       /* round 3 */
	AES_RROUND( X0, X1, X2, X3, Y0, Y1, Y2, Y3 );       /* round 4 */
	AES_RROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );       /* round 5 */
	AES_RROUND( X0, X1, X2, X3, Y0, Y1, Y2, Y3 );       /* round 6 */
	AES_RROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );       /* round 7 */
	AES_RROUND( X0, X1, X2, X3, Y0, Y1, Y2, Y3 );       /* round 8 */
	AES_RROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );       /* round 9 */

	/* last round */

	RK += 4;

	X0 = RK[0] ^ ( RSb[ (unsigned short) ( Y0 >> 24 ) ] << 24 ) ^
		( RSb[ (unsigned short) ( Y3 >> 16 ) ] << 16 ) ^
		( RSb[ (unsigned short) ( Y2 >>  8 ) ] <<  8 ) ^
		( RSb[ (unsigned short) ( Y1       ) ]       );

	X1 = RK[1] ^ ( RSb[ (unsigned short) ( Y1 >> 24 ) ] << 24 ) ^
		( RSb[ (unsigned short) ( Y0 >> 16 ) ] << 16 ) ^
		( RSb[ (unsigned short) ( Y3 >>  8 ) ] <<  8 ) ^
		( RSb[ (unsigned short) ( Y2       ) ]       );

	X2 = RK[2] ^ ( RSb[ (unsigned short) ( Y2 >> 24 ) ] << 24 ) ^
		( RSb[ (unsigned short) ( Y1 >> 16 ) ] << 16 ) ^
		( RSb[ (unsigned short) ( Y0 >>  8 ) ] <<  8 ) ^
		( RSb[ (unsigned short) ( Y3       ) ]       );

	X3 = RK[3] ^ ( RSb[ (unsigned short) ( Y3 >> 24 ) ] << 24 ) ^
		( RSb[ (unsigned short) ( Y2 >> 16 ) ] << 16 ) ^
		( RSb[ (unsigned short) ( Y1 >>  8 ) ] <<  8 ) ^
		( RSb[ (unsigned short) ( Y0       ) ]       );

	PUT_UINT32(X0, output, 0);
	PUT_UINT32(X1, output, 4);
	PUT_UINT32(X2, output, 8);
	PUT_UINT32(X3, output, 12);
}

unsigned short key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

void Decrypt(unsigned int *SrcAddr, unsigned int *DestAddr, unsigned int iv[], unsigned int key[], unsigned int Size)
{
	register unsigned int i = 0;

	aes_set_key(key, 128);

	while (i < (Size >> 2)) {
		aes_decrypt((unsigned short *)&DestAddr[i], (unsigned short *)&SrcAddr[i]);
		i += 4;
	}
}
#else

void Encrypt(unsigned int *SrcAddr, unsigned int *DestAddr, unsigned int iv[], unsigned int key[], unsigned int Size)
{
	unsigned int i=0, DataSize = ((Size+15) & 0xFFFFFFF0);
	int cnt;

	register NX_CRYPTO_RegisterSet *const pCrypto =
		(NX_CRYPTO_RegisterSet *)PHY_BASEADDR_CRYPTO0_MODULE;

        pCrypto->CRYPTO_AES_IV0 = iv[0];
        pCrypto->CRYPTO_AES_IV1 = iv[1];
        pCrypto->CRYPTO_AES_IV2 = iv[2];
        pCrypto->CRYPTO_AES_IV3 = iv[3];

        pCrypto->CRYPTO_AES_KEY0 = key[0];
        pCrypto->CRYPTO_AES_KEY1 = key[1];
        pCrypto->CRYPTO_AES_KEY2 = key[2];
        pCrypto->CRYPTO_AES_KEY3 = key[3];

	while(i < (DataSize>>2))            // 128bits == 4bytes x 4
	{
		pCrypto->CRYPTO_CRT_CTRL0 |= 0x1 << 3; // cpu_aes_loadcnt 1

		pCrypto->CRYPTO_AES_CTRL0 =
			0x0 << 15 | // 0: CPU configuration, 1: ECID AESKEY
			0x1 << 9 |  // 0: Big Endian, 1: Little Endian output swap
			0x1 << 8 |  // 0: Big Endian, 1: Little Endian input swap
			0x0 << 6 |  // 0: ECB, 1: CBC, 2: CTR mode
			0x0 << 4 |  // 0: 128-bit, 1: 192-bit, 2: 256-bit
			0x1 << 3 |  // 128bit counter
			0x0 << 2 |  // 0: FIFO Mode, 1: DMA Mode
			0x1 << 1 |  // 0: Decoder, 1: Encoder
			0x0 << 0;   // 0: Disable, 1: Enable AES Enable?

		pCrypto->CRYPTO_AES_TIN0 = SrcAddr[i + 0];
		pCrypto->CRYPTO_AES_TIN1 = SrcAddr[i + 1];
		pCrypto->CRYPTO_AES_TIN2 = SrcAddr[i + 2];
		pCrypto->CRYPTO_AES_TIN3 = SrcAddr[i + 3];

		pCrypto->CRYPTO_AES_CTRL0 =
			0x0 << 15 | // 0: CPU configuration, 1: ECID AESKEY
			0x1 << 9 |  // 0: Big Endian, 1: Little Endian output swap
			0x1 << 8 |  // 0: Big Endian, 1: Little Endian input swap
			0x0 << 6 |  // 0: ECB, 1: CBC, 2: CTR mode
			0x0 << 4 |  // 0: 128-bit, 1: 192-bit, 2: 256-bit
			0x1 << 3 |  // 128bit counter
			0x0 << 2 |  // 0: FIFO Mode, 1: DMA Mode
			0x1 << 1 |  // 0: Decoder, 1: Encoder
			0x1 << 0;   // 0: Disable, 1: Enable AES Enable?

		pCrypto->CRYPTO_CRT_CTRL0 &= ~(0x1 << 3); // cpu_aes_loadcnt 0

		pCrypto->CRYPTO_CRT_CTRL0 |= 0x1 << 0; // Decryption run

		while (!(pCrypto->CRYPTO_CRT_CTRL0 & 0x1 << 0));

		DestAddr[i + 0] = pCrypto->CRYPTO_AES_TOUT0;
		DestAddr[i + 1] = pCrypto->CRYPTO_AES_TOUT1;
		DestAddr[i + 2] = pCrypto->CRYPTO_AES_TOUT2;
		DestAddr[i + 3] = pCrypto->CRYPTO_AES_TOUT3;

		i += 4;
#ifdef DEBUG
                _dprintf("ctrl\r\n %x %x\r\n",
                        pCrypto->CRYPTO_CRT_CTRL0, pCrypto->CRYPTO_AES_CTRL0);

                _dprintf("iv\r\n %x %x %x %x\r\n", pCrypto->CRYPTO_AES_IV0,
                        pCrypto->CRYPTO_AES_IV1, pCrypto->CRYPTO_AES_IV2,
                        pCrypto->CRYPTO_AES_IV3);

                _dprintf("cnt\r\n %x %x %x %x\r\n", pCrypto->CRYPTO_AES_CNT0,
                        pCrypto->CRYPTO_AES_CNT1, pCrypto->CRYPTO_AES_CNT2,
                        pCrypto->CRYPTO_AES_CNT3);

                _dprintf("key0-3\r\n %x %x %x %x\r\n", pCrypto->CRYPTO_AES_KEY0,
                        pCrypto->CRYPTO_AES_KEY1, pCrypto->CRYPTO_AES_KEY2,
                        pCrypto->CRYPTO_AES_KEY3);

                _dprintf("key4-7\r\n %x %x %x %x\r\n", pCrypto->CRYPTO_AES_KEY4,
                        pCrypto->CRYPTO_AES_KEY5, pCrypto->CRYPTO_AES_KEY6,
                        pCrypto->CRYPTO_AES_KEY7);

                _dprintf("tin\r\n %x %x %x %x\r\n", pCrypto->CRYPTO_AES_TIN0,
                        pCrypto->CRYPTO_AES_TIN1, pCrypto->CRYPTO_AES_TIN2,
                        pCrypto->CRYPTO_AES_TIN3);

                _dprintf("tout\r\n %x %x %x %x\r\n", pCrypto->CRYPTO_AES_TOUT0,
                        pCrypto->CRYPTO_AES_TOUT1, pCrypto->CRYPTO_AES_TOUT2,
                        pCrypto->CRYPTO_AES_TOUT3);
#endif
	}
}

void Decrypt(unsigned int *SrcAddr, unsigned int *DestAddr, unsigned int iv[], unsigned int key[], unsigned int Size)
{
	unsigned int i=0, DataSize = ((Size+15) & 0xFFFFFFF0);
	int cnt;

	register NX_CRYPTO_RegisterSet *const pCrypto =
		(NX_CRYPTO_RegisterSet *)PHY_BASEADDR_CRYPTO0_MODULE;

        pCrypto->CRYPTO_AES_IV0 = iv[0];
        pCrypto->CRYPTO_AES_IV1 = iv[1];
        pCrypto->CRYPTO_AES_IV2 = iv[2];
        pCrypto->CRYPTO_AES_IV3 = iv[3];

        pCrypto->CRYPTO_AES_KEY0 = key[0];
        pCrypto->CRYPTO_AES_KEY1 = key[1];
        pCrypto->CRYPTO_AES_KEY2 = key[2];
        pCrypto->CRYPTO_AES_KEY3 = key[3];

	while(i < (DataSize>>2))            // 128bits == 4bytes x 4
	{
		unsigned int j, temp[4];
		unsigned short *LittleEndian, *BigEndian;

		pCrypto->CRYPTO_CRT_CTRL0 |= 0x1 << 3; // cpu_aes_loadcnt 1

		pCrypto->CRYPTO_AES_CTRL0 =
			0x0 << 15 | // 0: CPU configuration, 1: ECID AESKEY
			0x1 << 9 |  // 0: Big Endian, 1: Little Endian output swap
			0x1 << 8 |  // 0: Big Endian, 1: Little Endian input swap
			0x0 << 6 |  // 0: ECB, 1: CBC, 2: CTR mode
			0x0 << 4 |  // 0: 128-bit, 1: 192-bit, 2: 256-bit
			0x1 << 3 |  // 128bit counter
			0x0 << 2 |  // 0: FIFO Mode, 1: DMA Mode
			0x0 << 1 |  // 0: Decoder, 1: Encoder
			0x0 << 0;   // 0: Disable, 1: Enable AES Enable?

		pCrypto->CRYPTO_AES_TIN0 = SrcAddr[i + 0];
		pCrypto->CRYPTO_AES_TIN1 = SrcAddr[i + 1];
		pCrypto->CRYPTO_AES_TIN2 = SrcAddr[i + 2];
		pCrypto->CRYPTO_AES_TIN3 = SrcAddr[i + 3];

		pCrypto->CRYPTO_AES_CTRL0 =
			0x0 << 15 | // 0: CPU configuration, 1: ECID AESKEY
			0x1 << 9 |  // 0: Big Endian, 1: Little Endian output swap
			0x1 << 8 |  // 0: Big Endian, 1: Little Endian input swap
			0x0 << 6 |  // 0: ECB, 1: CBC, 2: CTR mode
			0x0 << 4 |  // 0: 128-bit, 1: 192-bit, 2: 256-bit
			0x1 << 3 |  // 128bit counter
			0x0 << 2 |  // 0: FIFO Mode, 1: DMA Mode
			0x0 << 1 |  // 0: Decoder, 1: Encoder
			0x1 << 0;   // 0: Disable, 1: Enable AES Enable?

		pCrypto->CRYPTO_CRT_CTRL0 &= ~(0x1 << 3); // cpu_aes_loadcnt 0

		pCrypto->CRYPTO_CRT_CTRL0 |= 0x1 << 0; // Decryption run

		while (!(pCrypto->CRYPTO_CRT_CTRL0 & 0x1 << 0));

		DestAddr[i + 0] = pCrypto->CRYPTO_AES_TOUT0;
		DestAddr[i + 1] = pCrypto->CRYPTO_AES_TOUT1;
		DestAddr[i + 2] = pCrypto->CRYPTO_AES_TOUT2;
		DestAddr[i + 3] = pCrypto->CRYPTO_AES_TOUT3;

		i += 4;
#ifdef DEBUG
                _dprintf("ctrl\r\n %x %x\r\n",
                        pCrypto->CRYPTO_CRT_CTRL0, pCrypto->CRYPTO_AES_CTRL0);

                _dprintf("iv\r\n %x %x %x %x\r\n", pCrypto->CRYPTO_AES_IV0,
                        pCrypto->CRYPTO_AES_IV1, pCrypto->CRYPTO_AES_IV2,
                        pCrypto->CRYPTO_AES_IV3);

                _dprintf("cnt\r\n %x %x %x %x\r\n", pCrypto->CRYPTO_AES_CNT0,
                        pCrypto->CRYPTO_AES_CNT1, pCrypto->CRYPTO_AES_CNT2,
                        pCrypto->CRYPTO_AES_CNT3);

                _dprintf("key0-3\r\n %x %x %x %x\r\n", pCrypto->CRYPTO_AES_KEY0,
                        pCrypto->CRYPTO_AES_KEY1, pCrypto->CRYPTO_AES_KEY2,
                        pCrypto->CRYPTO_AES_KEY3);

                _dprintf("key4-7\r\n %x %x %x %x\r\n", pCrypto->CRYPTO_AES_KEY4,
                        pCrypto->CRYPTO_AES_KEY5, pCrypto->CRYPTO_AES_KEY6,
                        pCrypto->CRYPTO_AES_KEY7);

                _dprintf("tin\r\n %x %x %x %x\r\n", pCrypto->CRYPTO_AES_TIN0,
                        pCrypto->CRYPTO_AES_TIN1, pCrypto->CRYPTO_AES_TIN2,
                        pCrypto->CRYPTO_AES_TIN3);

                _dprintf("tout\r\n %x %x %x %x\r\n", pCrypto->CRYPTO_AES_TOUT0,
                        pCrypto->CRYPTO_AES_TOUT1, pCrypto->CRYPTO_AES_TOUT2,
                        pCrypto->CRYPTO_AES_TOUT3);
#endif
	}
}
#endif
