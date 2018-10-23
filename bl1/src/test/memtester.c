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
#include <memtester.h>
#include <nx_qemu_sim_printf.h>
#include <nx_lib.h>

#define BLOCK_LENGTH 512

int simple_memtest_8bit(void)
{
	volatile unsigned int* start, *end, *ptr;
        volatile unsigned int loopCount=0;
        volatile unsigned int countStart=0;

	start = ((unsigned int *)0x80000000);
        end   = ((unsigned int *)0x80001000);
	_dprintf("############## Simple Memory 8 Bit Test Start!! ###############\r\n");
	
        for (int i = 1; i < 2; i++) {
                _dprintf("Read/Write 8 bit Test : StartAddr = 0x%x\r\n",start);
                ptr = start;
                loopCount = 0;

                _dprintf("Write 8 bit \r\n");
                while (ptr < end) {
                	countStart = (loopCount << i*8);
                        _dprintf("W: addr = 0x%08x, writeVal = 0x%08x, ptrAddr = 0x%08x\r\n",(unsigned int)ptr, countStart,ptr);
                        *ptr = (unsigned int)countStart;
                        loopCount++;
                        if ((loopCount & 0x100) >> 8) {
	                        _dprintf(".");
	                        loopCount = 0;
                        }
                        ptr++;
                }

                _dprintf("\r\nCompare 8bit Try %01x \r\n",i+1);

		udelay(100);
                
                ptr = start;
                loopCount = 0;
                while (ptr < end) {
                	countStart = (loopCount << i*8);
                        _dprintf("R: addr = 0x%08x, readVal = 0x%08x, ptrVal = 0x%08x\r\n",(unsigned int)ptr, countStart,*ptr);
                        if ((unsigned int)*ptr != (unsigned int)countStart) {
                        	_dprintf("Read/Write 8 bit test Fail1!\r\n");
                                _dprintf("Address = 0x%08x\r\n",(unsigned int)ptr);
                                _dprintf("readVal-1 = 0x%08x\r\n",(unsigned int)*ptr);
                                _dprintf("readVal = 0x%08x\r\n",(unsigned int)*ptr);
                                _dprintf("readVal+1 = 0x%08x\r\n",(unsigned int)*ptr);
                                _dprintf("wantVal = 0x%08x\r\n",(unsigned int)countStart);
                                return 0;
                	}

                        loopCount++;
                        if ((loopCount & 0x100) >> 8) {
                                _dprintf(".");                               
                                loopCount = 0;
                        }
                        ptr++;

                }
                 _dprintf("=================================================\r\n");
        }

	_dprintf("Done!   \r\n");
        return 1;
}

int simple_memtest_16bit(void)
{
	volatile unsigned int* start, *end, *ptr;
        volatile unsigned int loopCount=0;
        volatile unsigned int countStart=0;

	start = ((unsigned int *)0x90000000);
        end   = ((unsigned int *)0x90001000);
	_dprintf("############## Simple Memory 16 Bit Test Start!! ###############\r\n");
	
        for (int i = 0; i < 2; i++) {
                _dprintf("Read/Write 16 bit Test : StartAddr = 0x%x\r\n", start);
                ptr = start;
                loopCount = 0;

                _dprintf("Write 16 bit \r\n");
                while (ptr < end) {
                	countStart = (loopCount << i*16);
                        /* _dprintf("W: addr = 0x%08x, writeVal = 0x%08x, ptrAddr = 0x%08x\r\n",(unsigned int)ptr, countStart,ptr); */
                        *ptr = (unsigned int)countStart;
                        loopCount++;
                        if ((loopCount & 0x10000) >> 16) {
                        //_dprintf(".");
	                        loopCount = 0;
                        }
                        ptr++;
                }

                _dprintf("\r\nCompare 16 bit Try %01x \r\n",i+1);

		udelay(100);
                
                ptr = start;
                loopCount = 0;
                while (ptr < end) {
                	countStart = (loopCount << i*16);
                        _dprintf("R: addr = 0x%08x, readVal = 0x%08x, ptrVal = 0x%08x\r\n",(unsigned int)ptr,countStart,*ptr);
                        if ((unsigned int)*ptr != (unsigned int)countStart) {
                        	_dprintf("Read/Write 16 bit test Fail1!\r\n");
                                _dprintf("Address = 0x%08x\r\n",(unsigned int)ptr);
                                _dprintf("readVal = 0x%08x\r\n",(unsigned int)*ptr);
                                _dprintf("wantVal = 0x%08x\r\n",(unsigned int)countStart);
                                return 0;
                	}

                        loopCount++;
                        if ((loopCount & 0x10000) >> 16) {
                        //_dprintf(".");                               
                                loopCount = 0;
                        }
                        ptr++;

                }
                 _dprintf("=================================================\r\n");
        }

	_dprintf("Done!   \r\n");
        return 1;        
}

int simple_memtest_32bit(void)
{
	volatile unsigned int* start, *end, *ptr;
        volatile unsigned int loopCount=0;
	unsigned int step = 64;

	start = ((unsigned int *)0x80000000);
        end   = ((unsigned int *)0x82000000);
	_dprintf("############## Simple Memory 32 Bit Test Start!! ###############\r\n");
	

        _dprintf("Read/Write 32 bit Test : StartAddr = 0x%x\r\n", start);
        ptr = start;
        loopCount = 0xffffffff;

        _dprintf("Write 32 bit \r\n");
        while (ptr < end) {
                _dprintf("W: addr = 0x%08x, writeVal = 0x%08x\r\n",(unsigned int)ptr, loopCount);
                *ptr = (unsigned int)loopCount;
                loopCount -= 0x11111111;
                if (loopCount == 0x00000000) {
                        loopCount = 0xffffffff;
                }
                ptr += step;
        }

        udelay(100);

        ptr = start;
        loopCount = 0xffffffff;
        while (ptr < end) {
                _dprintf("R: addr = 0x%08x, readVal = 0x%08x, ptrVal = 0x%08x\r\n",(unsigned int)ptr,loopCount,*ptr);
                if ((unsigned int)*ptr != (unsigned int)loopCount) {
                        _dprintf("Read/Write 32 bit test Fail1!\r\n");
                        _dprintf("Address = 0x%08x\r\n",(unsigned int)ptr);
                        _dprintf("readVal = 0x%08x\r\n",(unsigned int)*ptr);
                        _dprintf("wantVal = 0x%08x\r\n",(unsigned int)loopCount);
                        return 0;
                }

                loopCount -= 0x11111111;
                if (loopCount == 0x00000000) {
                        loopCount = 0xffffffff;
                }
                ptr += step;

        }
         _dprintf("=================================================\r\n");

	_dprintf("Done!   \r\n");
        return 1;        
}

int simple_memtest_burst(void)
{
	volatile unsigned int* start, *end, *ptr;
        volatile unsigned int burstData[BLOCK_LENGTH];
        unsigned int compareData = 0;
        
	start = ((unsigned int *)0x80000000);
        end   = ((unsigned int *)0x80010000);
	_dprintf("############## Simple Memory Burst 512 Byte Test Start!! ###############\r\n");

        compareData = 0xa0a0a0a1;
        nx_memset(burstData, compareData, BLOCK_LENGTH*sizeof(unsigned int));
        _dprintf("Read/Write Burst Test : StartAddr = 0x%x\r\n", start);
        ptr = start;

        _dprintf("Write 0x%x byte \r\n",BLOCK_LENGTH);
        while (ptr < end) {
                _dprintf("W: addr = 0x%08x, val = 0x%08x\r\n",(unsigned int)ptr, compareData);
                nx_memcpy(ptr, burstData, BLOCK_LENGTH);
                ptr += BLOCK_LENGTH;
        }
        udelay(100);
        ptr = start;
        while (ptr < end) {
                _dprintf("R: addr = 0x%08x, ptrVal = 0x%08x\r\n",(unsigned int)ptr, *ptr);
                if ((unsigned int)*ptr != (unsigned int)compareData) {
                        _dprintf("Read/Write 16 bit test Fail1!\r\n");
                        _dprintf("Address = 0x%08x\r\n",(unsigned int)ptr);
                        for (int j = 0; j < BLOCK_LENGTH; j++)
	                        _dprintf("readVal = 0x%08x\r\n",(unsigned int)*(ptr+j));

                        _dprintf("wantVal = 0x%08x\r\n",(unsigned int)compareData);
                        return 0;
                }
                ptr += BLOCK_LENGTH;
        }
         _dprintf("=================================================\r\n");

	_dprintf("Done!   \r\n");
        return 1;        
}
