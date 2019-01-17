/*
 * Copyright (C) 2018  Nexell Co., Ltd.
 * Author: deoks <truevirtue@nexell.co.kr>
 *
 * Nexell informs that this code and information is provided "as Is" base
 * and without warranty of any kind, either expressed or implied, including,
 * but not limited to the implied warranties of merchantabulity and/or
 * fitness for a aparticular purpose.
 *
 * This program is copyrighted by Nexell and does not allow modification or
 * distribution. In addition to the author (person in charge), the modifier
 * is responsible for the modification.
 */
//#include <nx_swallow.h>
#include <nx_uart.h>
#include <nx_gpio.h>
#include <serial.h>
#include <nx_clock.h>
#include <nx_chip_iomux.h>
#include <nx_swallow_platform.h>

#define CONFIG_DEFAULT_REQ_UART_SRC_FREQ	(200000000)
#define CONFIG_REQ_UCLK_FREQ			(100000000)			// 100Mhz
#define CONFIG_SERIAL_BAUDRATE			(115200)

void serial_set_baudrate (int channel, int uclk, int baud_rate, unsigned int type)
{
	volatile unsigned int base;

	int ibrd, fbrd;

	base = (volatile unsigned int)(PHY_BASEADDR_UART0_MODULE);

	/* Divisor Latch Access Bit. */
	mmio_set_32((base + LCR), DLAB);
        mmio_set_32((base + LCR), 3);

	/* step xx. calculates an integer at the baud rate */
	//ibrd = (uclk / ((baud_rate/1) * 16));					// ibrd = 8, 115200bps
        ibrd = 108;					// ibrd = 8, 115200bps

	/* step xx. calculates an fractional at the baud rate */
	//fbrd = ((uclk % ((((baud_rate/1) * 16) + 32) * 64)) / (baud_rate / 1) * 16);		// fbrd = 0,
        fbrd = 8;

        //mmio_write_32((base + DLH), ((ibrd >> 8) & 0xFF));			// Divider Latch High 8bit
	mmio_write_32((base + DLL), ((ibrd >> 0) & 0xFF));			// Divider Latch Low 8bit

	// DLF - After confirming the number of bits in the field, write it down.
	mmio_write_32((base + DLF), fbrd);

	/* Divisor Latch Access Bit. */
	mmio_clear_32((base + LCR), DLAB);
}

int serial_init(unsigned int channel, unsigned int type)
{
	volatile unsigned int reg_value = 0;
	unsigned int g_uart_reg = PHY_BASEADDR_UART0_MODULE;
	struct nxpadi uart_tx_gpio = { 1, 12, 0, 1 };
	struct nxpadi uart_rx_gpio = { 1, 13, 0, 1 };
        //	unsigned int g_clk_num[2] = {NX_CMU_CLK_APB, NX_CMU_CLK_CLK400};

	/* step xx. set the cmu (source clock) */
        //	set_uclk_source(CONFIG_REQ_UCLK_FREQ);

	/* step xx. enable the (ext:uart clock)clock in uart block*/
        //	set_uclk_enb(TRUE);

	/* step xx. calculates an integer at the baud rate */
	serial_set_baudrate(channel, CONFIG_DEFAULT_REQ_UART_SRC_FREQ, CONFIG_SERIAL_BAUDRATE, type);

	/* step xx. change the (tx, rx)gpio-alternative function */
	//setpad(g_uart_pad[channel][0].padi, 1);
        setpad(uart_tx_gpio, 1, PHY_BASEADDR_GPIO3_MODULE);
        setpad(uart_rx_gpio, 1, PHY_BASEADDR_GPIO3_MODULE);

	/* step xx. set the serial (:uart) */
#if 0
	reg_value = (XMIT_FIFO_RESET|RCVR_FIFO_RESET|UART_RESET);		// Software - Tx, Rx FIFO Reset, Uart Reset
	mmio_write_32((g_uart_reg + SRR), reg_value);
#endif

        reg_value = (XFIFOR|RFIFOR|FIFO_ENB);					// Tx, Rx FIFO Reset, FIFO Enable (Rx:0x2 Tx:0x1)
	mmio_write_32((g_uart_reg + FCR), reg_value);

	reg_value = DATA_LENGTH(0x3);						// Parity Bit: Even, Stop Bit: 1Bit, Data Length: 8Bit
	mmio_write_32((g_uart_reg + LCR), reg_value);

	return 0;
}

void serial_putc(char ch)
{
	unsigned int g_uart_reg = PHY_BASEADDR_UART0_MODULE;
	while (!(mmio_read_32(g_uart_reg + USR) & TX_FIFO_NOTFULL));
        mmio_write_32((g_uart_reg + THR), (unsigned int)ch);
}
