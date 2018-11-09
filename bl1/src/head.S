// See LICENSE for license details.
#include <nx_swallow.h>

        .option norvc
        .section .text.init, "ax", @progbits
	.globl bl1start
bl1start:
	li x1, 0
	li x2, 0
	li x3, 0
	li x4, 0
	li x5, 0
	li x6, 0
	li x7, 0
	li x8, 0
	li x9, 0
        li x10, 0
        li x11, 0
	li x12, 0
	li x13, 0
	li x14, 0
	li x15, 0
	li x16, 0
	li x17, 0
	li x18, 0
	li x19, 0
	li x20, 0
	li x21, 0
	li x22, 0
	li x23, 0
	li x24, 0
	li x25, 0
	li x26, 0
	li x27, 0
	li x28, 0
	li x29, 0
	li x30, 0
	li x31, 0
	csrw mscratch, x0
	csrw mcause, x0
	csrw mip, x0

        li sp, (SRAM_ADDR + SRAM_SIZE - VECTOR_SIZE)

        call bl1main

        li s3, 0
        addi s3, a0, 0

        jr s3

stop_and_go:
        j stop_and_go

.section .text.hang, "ax", @progbits
.globl _hang
_hang:
        csrr a0, mhartid
