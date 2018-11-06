/*
 * Copyright (C) 2016  Nexell Co., Ltd.
 * Author: DeokJin, Lee <truevirtue@nexell.co.kr>
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
//#include <sysheader.h>
#include "memtester.h"
#include <nx_swallow_printf.h>
#include <nx_cpuif_regmap.h>
#include <nx_lib.h>

#define BLOCK_LENGTH 512

/* int simple_memtest_8bit(volatile unsigned int rdqdlyval) */
/* { */
/* 	volatile unsigned int *start;// = 0x90020000; */
/* 	volatile unsigned int *end;// = 0x90021400; */
/* 	volatile unsigned int *sram_start;// = 0x90020000; */
/* 	volatile unsigned int *sram_end;// = 0x90021400; */
/* 	volatile unsigned int *ptr, *sram_ptr; */
/*         volatile unsigned int readVal = 0, sram_readVal = 0; */
/*         unsigned int loop = 1; */

/* 	start = ((volatile unsigned int *)0x80013200); */
/*         end   = ((volatile unsigned int *)0x80014200); */
/* 	sram_start = ((volatile unsigned int *)0x40006000); */
/*         sram_end   = ((volatile unsigned int *)0x40007000); */

/* 	_dprintf("############## Read to SRAM Start!! ###############\r\n"); */
/*         ptr = start; */
/*         sram_ptr = sram_start; */
/*         while (ptr < end) { */
/* 	        *sram_ptr = *ptr; */
/*                 _dprintf("W: writeVal = 0x%08x, sram_addr = 0x%08x\r\n", *sram_ptr, sram_ptr); */
/*                 sram_ptr++; */
/*                 ptr++; */
/*         } */


/*         _dprintf("read test\r\n"); */
/*         udelay(1000000); */
/*         for (int i = 0; i < loop; i++) { */
/* 	        ptr = start; */
/* 	        sram_ptr = sram_start; */

/*                 _dprintf("\r\nCompare 8bit Try %01x \r\n",i+1); */
        
/* 	        while (ptr < end) { */
/* 	                readVal = (unsigned int)(*ptr); */
/* 	                sram_readVal = (unsigned int)(*sram_ptr); */
/* 	                _dprintf("R: dram_addr = 0x%08x, dram_val = 0x%08x\r\n", ptr, (unsigned int)(*ptr)); */
/* 	                _dprintf("R: sram_addr = 0x%08x, sram_val = 0x%08x\r\n\r\n", sram_ptr, (unsigned int)(*sram_ptr)); */
	
/* 	                if (readVal != sram_readVal) { */
/* 	                      	_dprintf("Read test Fail1!\r\n"); */
/* 	                        _dprintf("dram_addr = 0x%08x\r\n",ptr); */
/* 	                        _dprintf("sram_addr = 0x%08x\r\n",sram_ptr); */
/* 	                        _dprintf("dram_readVal = 0x%08x\r\n",(unsigned int)*ptr); */
/* 	                        _dprintf("sram_readVal = 0x%08x\r\n",(unsigned int)*sram_ptr); */
/* 	                        _dprintf("=================================================\r\n"); */
/*                                 return 0; */
/* 	              	} */
/* 	                ptr++; */
/* 	                sram_ptr++; */
/* 	        } */
/*                 udelay(64000); //64ms */
/* 	} */
        
/*         _dprintf("=================================================\r\n"); */
/* 	_dprintf("Done!   \r\n"); */
/*         return 1; */
/* } */

int simple_memtest_8bit(void)
{
	volatile unsigned int *start;// = 0x90020000;
	volatile unsigned int *end;// = 0x90021400;
	volatile unsigned int *ptr;
        volatile unsigned int loop = 1;
        volatile unsigned int readVal = 0;
        volatile unsigned int testVal = 0;
        unsigned int testValStart = 0xa5a5a500;

	start = ((volatile unsigned int *)0x87000000);
        end   = ((volatile unsigned int *)0x87000100);

        for (int i = 0; i < loop; i++) {
                ptr = start;
                testVal = testValStart;

                //write
                while (ptr < end) {
                        *ptr = (unsigned int)(testVal);
                        testVal++;
                        if ((testVal & 0x100) >> 8) {
	                        testVal = 0;
                        }
                        ptr++;
                }
        }

        __asm__ __volatile__ ("fence" : : : "memory");
 read:
        //udelay(3000000);
        for (int i = 0; i < loop; i++) {
                ptr = start;
                testVal = testValStart;
                while (ptr < end) {
                        readVal = (unsigned int)(*ptr);
                        if (readVal != testVal) {
                                _dprintf("R: addr = 0x%08x, correctVal = 0x%02x, ptrVal = 0x%02x\r\n",ptr, testVal, readVal);
                                /* return 0; */
                	}
                        testVal++;
                        if ((testVal & 0x100) >> 8) {
                                testVal = 0;
                        }
                        ptr++;
                }
        }
	_dprintf("Done!   \r\n");
        return 1;
}


int simple_memtest_32bit(void)
{
	volatile unsigned int *start;// = 0x90020000;
	volatile unsigned int *end;// = 0x90021400;
	volatile unsigned int *ptr;
        volatile unsigned int loop = 1;
        volatile unsigned int readVal = 0;
        volatile unsigned int testVal = 0;
        volatile unsigned int testValStart = 0xa0a0a0a0;

	start = ((volatile unsigned int *)0x87020000);
        end   = ((volatile unsigned int *)0x87020200);

	_dprintf("############## Simple Memory 8 Bit Test Start!! ###############\r\n");
        testVal = testValStart;
        for (int i = 0; i < loop; i++) {
                ptr = start;
                _dprintf("Write 8 bit \r\n");
                while (ptr < end) {
                        _dprintf("W: addr = 0x%08x, writeVal = 0x%08x\r\n",ptr, testVal);
                        *ptr = (unsigned int)(testVal);
                        /* testVal++; */
                        /* if ((testVal & 0x100) >> 8) { */
	                /*         testVal = 0; */
                        /* } */

                        testVal = ~testVal;
                        ptr++;// += 0x10;
                }
        }
        _dprintf("read test\r\n");
        udelay(1000000);

        for (int i = 0; i < loop; i++) {
                _dprintf("\r\nCompare 8bit Try %01x \r\n",i+1);
                ptr = start;
                testVal = testValStart;
                while (ptr < end) {
                        readVal = (unsigned int)(*ptr);
                        /* _dprintf("R: addr = 0x%08x, correctVal = 0x%08x, ptrVal = 0x%08x\r\n",ptr, testVal, readVal); */
                        if (readVal != testVal) {
                        	/* _dprintf("Read/Write 8 bit test Fail1!\r\n"); */
                                /* _dprintf("Address = 0x%08x\r\n",ptr); */
                                /* _dprintf("readVal-1 = 0x%08x\r\n",(unsigned int)*ptr); */
                                /* _dprintf("readVal = 0x%08x\r\n",(unsigned int)*ptr); */
                                /* _dprintf("readVal+1 = 0x%08x\r\n",(unsigned int)*ptr); */
	                        _dprintf("Fail : Addr=0x%08x, correct_value=0x%08x, invalid_value=0x%08x\r\n", ptr, testVal, readVal);
                                return 0;
                	}
                        testVal = ~testVal;
                        /* testVal++; */
                        /* if ((testVal & 0x100) >> 8) { */
                        /*         testVal = 0; */
                        /* } */
                        ptr++;// += 0x10;
                }
        }
        _dprintf("=================================================\r\n");
        _dprintf("=================================================\r\n");
	_dprintf("MemTest PASS!   \r\n");
        _dprintf("=================================================\r\n");
        _dprintf("=================================================\r\n");
        return 1;
}
