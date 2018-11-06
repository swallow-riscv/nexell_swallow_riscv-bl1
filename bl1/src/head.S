// See LICENSE for license details.
#include <nx_swallow.h>

.section .text.start, "ax", @progbits
.option norvc        
.globl bl1start
bl1start:
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
