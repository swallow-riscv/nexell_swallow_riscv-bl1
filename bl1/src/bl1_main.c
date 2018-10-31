////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2009 Nexell Co., Ltd All Rights Reserved
// Nexell Co. Proprietary & Confidential
//
// Nexell informs that this code and information is provided "as is" base
// and without warranty of any kind, either expressed or implied, including
// but not limited to the implied warranties of merchantability and/or
// fitness for a particular puporse.
//
// Module	:
// File		: iROMBOOT.c
// Description	:
// Author	: Hans
// History	:
//		2014-01-12	Hans create
//		2017-10-09	Hans modified for NXP3220
//		2018-01-15	Hans sim done
////////////////////////////////////////////////////////////////////////////////
#include <nx_swallow.h>
#include <nx_cpuif_regmap.h>
#include <nx_bootheader.h>
#include <iSDBOOT.h>
#ifdef MEMTEST
#include <memtester.h>
#endif
#ifdef SOC_SIM
#include <nx_qemu_sim_printf.h>
#else
#include <nx_swallow_printf.h>
#include <serial.h>
#endif

unsigned int* bl1main()
{
    int result = 0;
    
#ifdef SOC_SIM
    _dprintf("bl1 enter---\n");
#endif

    //todo
    //uart init
    //debug print
    
    //DDR1 memory initialize
#ifdef SOC_SIM    
    _dprintf("DDR1 init start\n");
#endif

    nx_cpuif_reg_write_one(	DDRC_REG_4   , 0x8C   ); // address : {bank, row, column} || OK
    //nx_cpuif_reg_write_one(	DDRC_REG_8   , 0xC0C06   ); // reset default
    nx_cpuif_reg_write_one(	DDRC_REG_8   , 0x0B270   ); // for 200MHz operation
    nx_cpuif_reg_write_one(	DDRC_REG_0   , 0x1    );

    while(0 == nx_cpuif_reg_read_one(DDRC_REG_0, 0) );
#ifdef SOC_SIM
   _dprintf("DDR1 init done\n");
#endif

#ifdef MEMTEST   
   simple_memtest();
#else

#ifdef DEBUG
   serial_init(0); //channel = 0
   _dprintf("Bl1 Start\r\n");
#endif

   //Boot mode check and BBL+linux loading
   result = iSDBOOT();

   //reset vector test
#ifdef VECTOR_TEST
   volatile unsigned int* pCLINT1Reg = (unsigned int*)(0x02000004);
   _dprintf("CPU1 wake-up\r\n");
   *pCLINT1Reg = 0x1;
   return 0;
#else
#ifdef DEBUG
    _dprintf(">> bl1 boot result = 0x%x <<\r\n",result);
#endif
    
    if (result) {
#ifdef DEBUG
        _dprintf(">> Launch to 0x%x\r\n", BASEADDR_DRAM);
#endif
        return (unsigned int*)(BASEADDR_DRAM);
    }
#endif //VECTOR_TEST
#endif //MEMTEST

    while(1);
    return 0;
}
