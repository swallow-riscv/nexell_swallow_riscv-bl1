/*
 *      Copyright (C) 2012 Nexell Co., All Rights Reserved
 *      Nexell Co. Proprietary & Confidential
 *
 *      NEXELL INFORMS THAT THIS CODE AND INFORMATION IS PROVIDED "AS IS" BASE
 *      AND WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING
 *      BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
 *	FITNESS
 *      FOR A PARTICULAR PURPOSE.
 *
 *      Module          : Crypto
 *      File            : nx_crypto.h
 *      Description     :
 *      Author          :
 *      History         :
 */
#ifndef __NX_CRYPTO_H__
#define __NX_CRYPTO_H__

#include <stdbool.h>

#ifdef	__cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
/// @defgroup	CRYPTO
//------------------------------------------------------------------------------
//@{

//--------------------------------------------------------------------------
/// @brief	register map
typedef struct NX_CRYPTO_RegisterSet
{
	volatile unsigned int CRYPTO_CRT_CTRL0 ; // 0x00
	volatile unsigned int _Reserved[2]     ; // 0x04, 0x08
	volatile unsigned int CRYPTO_AES_CTRL0 ; // 0x0c
	volatile unsigned int CRYPTO_AES_IV0   ;
	volatile unsigned int CRYPTO_AES_IV1   ;
	volatile unsigned int CRYPTO_AES_IV2   ;
	volatile unsigned int CRYPTO_AES_IV3   ;
	volatile unsigned int CRYPTO_AES_CNT0  ;
	volatile unsigned int CRYPTO_AES_CNT1  ;
	volatile unsigned int CRYPTO_AES_CNT2  ;
	volatile unsigned int CRYPTO_AES_CNT3  ;
	volatile unsigned int CRYPTO_AES_KEY0  ;
	volatile unsigned int CRYPTO_AES_KEY1  ;
	volatile unsigned int CRYPTO_AES_KEY2  ;
	volatile unsigned int CRYPTO_AES_KEY3  ;
	volatile unsigned int CRYPTO_AES_KEY4  ;
	volatile unsigned int CRYPTO_AES_KEY5  ;
	volatile unsigned int CRYPTO_AES_KEY6  ;
	volatile unsigned int CRYPTO_AES_KEY7  ;
	volatile unsigned int CRYPTO_AES_TIN0  ;
	volatile unsigned int CRYPTO_AES_TIN1  ;
	volatile unsigned int CRYPTO_AES_TIN2  ;
	volatile unsigned int CRYPTO_AES_TIN3  ;
	volatile unsigned int CRYPTO_AES_TOUT0 ;
	volatile unsigned int CRYPTO_AES_TOUT1 ;
	volatile unsigned int CRYPTO_AES_TOUT2 ;
	volatile unsigned int CRYPTO_AES_TOUT3 ;
	volatile unsigned int CRYPTO_DES_CTRL0 ;
	volatile unsigned int CRYPTO_DES_IV0   ;
	volatile unsigned int CRYPTO_DES_IV1   ;
	volatile unsigned int CRYPTO_DES_KEY0_0;
	volatile unsigned int CRYPTO_DES_KEY0_1;
	volatile unsigned int CRYPTO_DES_KEY1_0;
	volatile unsigned int CRYPTO_DES_KEY1_1;
	volatile unsigned int CRYPTO_DES_KEY2_0;
	volatile unsigned int CRYPTO_DES_KEY2_1;
	volatile unsigned int CRYPTO_DES_TIN0  ;
	volatile unsigned int CRYPTO_DES_TIN1  ;
	volatile unsigned int CRYPTO_DES_TOUT0 ;
	volatile unsigned int CRYPTO_DES_TOUT1 ;
	volatile unsigned int CRYPTO_CRT_BDMAR ; // DMA Access Region ( DMA에 설정해주는 Register Addr  )
	volatile unsigned int CRYPTO_CRT_BDMAW ; // DMA Access Region
	volatile unsigned int CRYPTO_CRT_HDMAR ; // DMA Access Region
	volatile unsigned int CRYPTO_HASH_CTRL0;
	volatile unsigned int CRYPTO_HASH_IV0  ;
	volatile unsigned int CRYPTO_HASH_IV1  ;
	volatile unsigned int CRYPTO_HASH_IV2  ;
	volatile unsigned int CRYPTO_HASH_IV3  ;
	volatile unsigned int CRYPTO_HASH_IV4  ;
	volatile unsigned int CRYPTO_HASH_TOUT0;
	volatile unsigned int CRYPTO_HASH_TOUT1;
	volatile unsigned int CRYPTO_HASH_TOUT2;
	volatile unsigned int CRYPTO_HASH_TOUT3;
	volatile unsigned int CRYPTO_HASH_TOUT4;
	volatile unsigned int CRYPTO_HASH_TIN  ;
	volatile unsigned int CRYPTO_HASH_MSZE0;
	volatile unsigned int CRYPTO_HASH_MSZE1;
} NX_CRYPTO_RegisterSet;


//------------------------------------------------------------------------------
///	@name	CRYPTO Interface
//------------------------------------------------------------------------------
//@{
//unsigned int   NX_CRYPTO_GetTEMP( unsigned int ModuleIndex );
//@}

//------------------------------------------------------------------------------
///	@name	Basic Interface
//------------------------------------------------------------------------------
//@{
bool NX_CRYPTO_Initialize( void );
unsigned int   NX_CRYPTO_GetNumberOfModule( void );

unsigned int   NX_CRYPTO_GetSizeOfRegisterSet( void );
void  NX_CRYPTO_SetBaseAddress( unsigned int ModuleIndex, void* BaseAddress );
void*  NX_CRYPTO_GetBaseAddress( unsigned int ModuleIndex );
unsigned int   NX_CRYPTO_GetPhysicalAddress ( unsigned int ModuleIndex );
bool NX_CRYPTO_OpenModule( unsigned int ModuleIndex );
bool NX_CRYPTO_CloseModule( unsigned int ModuleIndex );
//bool NX_CRYPTO_CheckBusy( unsigned int ModuleIndex );
//@}

//------------------------------------------------------------------------------
///	@name	clock Interface : PCLK Gating
//------------------------------------------------------------------------------
unsigned int NX_CRYPTO_GetClockNumber (unsigned int ModuleIndex);

//------------------------------------------------------------------------------
///	@name	reset Interface
//------------------------------------------------------------------------------
//@{
unsigned int NX_CRYPTO_GetResetNumber ( unsigned int ModuleIndex );
//@}

//------------------------------------------------------------------------------
///	@name	No Interrupt Interface
//------------------------------------------------------------------------------
unsigned int NX_CRYPTO_GetInterruptNumber( unsigned int ModuleIndex );
void	NX_CRYPTO_SetInterruptEnable( unsigned int ModuleIndex, bool Enb );
void	NX_CRYPTO_SetInterruptMask( unsigned int ModuleIndex, unsigned int Mask );

bool	NX_CRYPTO_GetInterruptPendingAll( unsigned int ModuleIndex );
void	NX_CRYPTO_ClearInterruptPendingAll( unsigned int ModuleIndex );

//------------------------------------------------------------------------------
///	@name	DMA Interface
//------------------------------------------------------------------------------
//@{
/// @brief	DMA index for DMAChannelIndex
typedef enum {
	CRYPDMA_BR		= 0,
	CRYPDMA_BW		= 1,
	CRYPDMA_HR		= 2,
}NX_CRYPTO_DMACHANNEL;

unsigned int NX_CRYPTO_GetDMANumber ( unsigned int ModuleIndex , NX_CRYPTO_DMACHANNEL Channel);
unsigned int NX_CRYPTO_GetDMABusWidth( );
//@}

//------------------------------------------------------------------------------
///	@name	No PAD Interface
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
///	@name	Basic Use Functions
//------------------------------------------------------------------------------
//@{

void	NX_CRYPTO_SetAESTextIn			( unsigned int ModuleIndex, unsigned int AES_TIN0, unsigned int AES_TIN1, unsigned int AES_TIN2, unsigned int AES_TIN3 ); // AES_TIN0, AES_TIN1, AES_TIN2, AES_TIN3
void	NX_CRYPTO_SetAESInitVec			( unsigned int ModuleIndex, unsigned int AES_IV0,  unsigned int AES_IV1,  unsigned int AES_IV2,  unsigned int AES_IV3 ); // AES_IV0, AES_IV1, AES_IV2, AES_IV3
void	NX_CRYPTO_SetAESKey				( unsigned int ModuleIndex,
	unsigned int AES_KEY0, unsigned int AES_KEY1, unsigned int AES_KEY2, unsigned int AES_KEY3,
	unsigned int AES_KEY4, unsigned int AES_KEY5, unsigned int AES_KEY6, unsigned int AES_KEY7 ); // AES_KEY0, AES_KEY1, AES_KEY2, AES_KEY3, AES_KEY4, AES_KEY5, AES_KEY6, AES_KEY7
void	NX_CRYPTO_SetAESEfuseKeyMode		( unsigned int ModuleIndex, bool Enb );
void	NX_CRYPTO_SetAESOutputSwap			( unsigned int ModuleIndex, bool Enb );
void	NX_CRYPTO_SetAESInputSwap			( unsigned int ModuleIndex, bool Enb ); // 지금은 넣을때 BigEndian으로 넣어주고 있다.
void	NX_CRYPTO_SetAESBlockCiphterMode	( unsigned int ModuleIndex, unsigned int Mode );  // Block Cipher Mode-> 0:ECB, 1:CBC, 2:CTR
void	NX_CRYPTO_SetAESMode			( unsigned int ModuleIndex, unsigned int Mode ); // AES Mode->0:128, 1:192, 2:256
void	NX_CRYPTO_SetAESDMAMode			( unsigned int ModuleIndex, unsigned int Mode ); // DMA Mode->0:FIFO mode, 1:DMA mode
void	NX_CRYPTO_SetAESEncoderMode		( unsigned int ModuleIndex, unsigned int Mode ); // AES Encoder Mode->0:Decoder, 1: Encoder
void	NX_CRYPTO_SetAESEnable			( unsigned int ModuleIndex, bool Enb );
void	NX_CRYPTO_SetHASHRun			( unsigned int ModuleIndex, bool Enb ); // HASH Run : Disable
void	NX_CRYPTO_SetDESRun				( unsigned int ModuleIndex, bool Enb ); // DES Run
void	NX_CRYPTO_SetAESRun				( unsigned int ModuleIndex, bool Enb );
void	NX_CRYPTO_GetAESTextOut			( unsigned int ModuleIndex, unsigned int* AES_TOUT0, unsigned int* AES_TOUT1, unsigned int* AES_TOUT2, unsigned int* AES_TOUT3 ); // AES_TOUT0, AES_TOUT1, AES_TOUT2, AES_TOUT3
void	NX_CRYPTO_SetLoadDESIV			( unsigned int ModuleIndex, bool Enb ); // Load DES IV
void	NX_CRYPTO_SetLoadAESIV			( unsigned int ModuleIndex, bool Enb ); // Load AES IV

bool    NX_CRYPTO_GetIdleAES            ( unsigned int ModuleIndex );

bool	NX_CRYPTO_GetIdleHASH( unsigned int ModuleIndex );
bool	NX_CRYPTO_GetIdleDES ( unsigned int ModuleIndex );
void NX_CRYPTO_GetDESTextOut ( unsigned int ModuleIndex, unsigned int *DES_TOUT0, unsigned int *DES_TOUT1 );

void NX_CRYPTO_SetDESTextIn            ( unsigned int ModuleIndex, unsigned int DES_TIN0, unsigned int DES_TIN1 ); // DES_TIN0, DES_TIN1
void NX_CRYPTO_SetDESInitVec           ( unsigned int ModuleIndex, unsigned int DES_IV0,  unsigned int DES_IV1);
void NX_CRYPTO_SetDESKeyIn0            ( unsigned int ModuleIndex, unsigned int DES_KEY0_0, unsigned int DES_KEY1_0 );
void NX_CRYPTO_SetDESKeyIn1            ( unsigned int ModuleIndex, unsigned int DES_KEY1_0, unsigned int DES_KEY1_1 );
void NX_CRYPTO_SetDESKeyIn2            ( unsigned int ModuleIndex, unsigned int DES_KEY2_0, unsigned int DES_KEY2_1 );
void NX_CRYPTO_SetTDESMode             ( unsigned int ModuleIndex, unsigned int TDESMODE ); // TDESMODE
void NX_CRYPTO_SetDESOutputSwap        ( unsigned int ModuleIndex, bool Enb );
void NX_CRYPTO_SetDESInputSwap         ( unsigned int ModuleIndex, bool Enb ); // 지금은 넣을때 BigEndian으로 넣어주고 있다.
void NX_CRYPTO_SetDESBlockCiphterMode  ( unsigned int ModuleIndex, unsigned int Mode );  // Block Cipher Mode-> 0:ECB, 1:CBC
void NX_CRYPTO_SetDESDMAMode           ( unsigned int ModuleIndex, unsigned int Mode ); // DMA Mode->0:FIFO mode, 1:DMA mode
void NX_CRYPTO_SetDESMode              ( unsigned int ModuleIndex, unsigned int Mode ); // 0:DES, 1:TDES
void NX_CRYPTO_SetDESEncoderMode       ( unsigned int ModuleIndex, unsigned int Mode ); // DES Encoder Mode->0:Decoder, 1: Encoder
void NX_CRYPTO_SetDESEnable            ( unsigned int ModuleIndex, bool Enb ); // DES Enable
void NX_CRYPTO_SetDMAWritePath         ( unsigned int ModuleIndex, unsigned int Mode ); // DMA Write Path : 0:AES, 1:DES
void NX_CRYPTO_SetMSZEE0               ( unsigned int ModuleIndex, unsigned int HASH_MSZE0, unsigned int HASH_MSZE1 );
void NX_CRYPTO_SetINITTABLE            ( unsigned int ModuleIndex, unsigned int HASH_IV0,
										unsigned int HASH_IV1, unsigned int HASH_IV2, unsigned int HASH_IV3, unsigned int HASH_IV4 );

void NX_CRYPTO_SetHASHDMAPath          ( unsigned int ModuleIndex, unsigned int Mode );// DMA Path
void NX_CRYPTO_SetHASHInputSwap        ( unsigned int ModuleIndex, bool Enb ); // Input Swap
void NX_CRYPTO_SetHASHMode             ( unsigned int ModuleIndex, unsigned int Mode ); // 0:SHA1, 1:MD5
void NX_CRYPTO_SetHASHCont             ( unsigned int ModuleIndex, unsigned int Mode ); // HASH Cont
void NX_CRYPTO_SetDMAMode              ( unsigned int ModuleIndex, unsigned int Mode ); // DMA Mode->0:FIFO mode, 1:DMA mode
void NX_CRYPTO_SetHASHEnable           ( unsigned int ModuleIndex, unsigned int Mode );

void NX_CRYPTO_GetHASHTextOut( unsigned int ModuleIndex,
	unsigned int *HASH_TOUT0, unsigned int *HASH_TOUT1, unsigned int *HASH_TOUT2, unsigned int *HASH_TOUT3, unsigned int *HASH_TOUT4 );

void NX_CRYPTO_SetAES64bitCounter( unsigned int ModuleIndex, unsigned int Mode ); // 64bit counter
void	NX_CRYPTO_SetHASHTextIn			( unsigned int ModuleIndex, unsigned int HASH_TIN ) ;
bool NX_CRYPTO_GetIdleHASHCore( unsigned int ModuleIndex );

//@}

//=================
// Register R/W Test Function
// prototype 으로 제공한다.
//=================
bool NX_CRYPTO_RegTest( unsigned int ModuleIndex );
bool NX_CRYPTO_CheckReg( unsigned int Addr, unsigned int initvalue, unsigned int writevalue, char *RegName);

bool NX_CRYPTO_RegTest_ECO_20130129( unsigned int ModuleIndex );

void Encrypt(unsigned int *SrcAddr, unsigned int *DestAddr, unsigned int iv[], unsigned int key[], unsigned int Size);
void Decrypt(unsigned int *SrcAddr, unsigned int *DestAddr, unsigned int iv[], unsigned int key[], unsigned int Size);

//@}

#ifdef	__cplusplus
}
#endif


#endif // __NX_CRYPTO_H__
