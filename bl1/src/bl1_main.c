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
#elif MEMTEST2
#include <memtester2.h>
#endif
#ifdef SOC_SIM
#include <nx_qemu_sim_printf.h>
#else
#include <nx_swallow_printf.h>
#include <serial.h>
#endif

#include <nx_gpio.h>
#include <nx_chip_iomux.h>

unsigned int* bl1main()
{
    int result = 0;
    int nDDRC_init = 0;
    unsigned int ddr_phy_config = 0x00000000;
    unsigned int ddr_addr_size = 0x00000001;
    unsigned int ddr_timing_0 = 0x000C0C06;
    unsigned int ddr_timing_1 = 0x00623233;
    unsigned int ddr_timing_2 = 0x753008B3;

#ifdef SOC_SIM
    _dprintf("bl1 enter---\n");
#endif

#if defined(MEMTEST) && defined(DEBUG) //early printf
   serial_init(0); //channel = 0
   _dprintf("\r\n\r\n\r\n\r\n\r\nbl1 enter---\r\n");
#endif

    //-------------------------------------------------------------
    //DDR1 memory initialize
    //-------------------------------------------------------------
    // 1. DDR_ADDR_SIZE set
    //-------------------------------------------------------------
    ddr_addr_size = (DDR_ADDR_SIZE_COL_SIZE    | \
                     DDR_ADDR_SIZE_ROW_SIZE    | \
                     DDR_ADDR_SIZE_BANK_SIZE   | \
                     DDR_ADDR_SIZE_ADDR_MAP    | \
                     DDR_ADDR_SIZE_SEL_MDDR    | \
                     DDR_ADDR_SIZE_IO_STRENGTH | \
                     DDR_ADDR_SIZE_IO_DRIVESEL | \
                     DDR_ADDR_SIZE_IO_ODTSEL   | \
                     DDR_ADDR_SIZE_IO_ODTEN      \
                     );
   
    nx_cpuif_reg_write_one(DDRC_REG_4, ddr_addr_size); // address : {bank, row, column} || OK //C8A
    //    nx_cpuif_reg_write_one(	DDRC_REG_8   , 0xC0C06   ); // reset default
#ifdef DEBUG
    _dprintf("W: DDR_ADDR_SIZE val = 0x%08x\r\n",ddr_addr_size);
#endif

    //-------------------------------------------------------------
    // 2. DDR_TIMING_0 set
    //-------------------------------------------------------------
    ddr_timing_0 = (DDR_TIMING_0_TRAS | \
                    DDR_TIMING_0_TRFC | \
                    DDR_TIMING_0_TRC \
                    );
    nx_cpuif_reg_write_one(DDRC_REG_8, ddr_timing_0);//0x181414); // for 200MHz operation //B270 //0xE280E
    //nx_cpuif_reg_write_one(	DDRC_REG_8   , 0x000B270); // for 200MHz operation //B270
#ifdef DEBUG
    _dprintf("DDR_TIMING_0 val = 0x%08x\r\n",ddr_timing_0);
#endif

    //-------------------------------------------------------------
    // 3. DDR_TIMING_1 set
    //-------------------------------------------------------------
    ddr_timing_1 = (DDR_TIMING_1_TRCD | \
                    DDR_TIMING_1_TRP | \
                    DDR_TIMING_1_TRRD | \
                    DDR_TIMING_1_TWR | \
                    DDR_TIMING_1_TWTR | \
                    DDR_TIMING_1_TMRD | \
                    DDR_TIMING_1_TDQSS \
                    );
    nx_cpuif_reg_write_one(DDRC_REG_C, ddr_timing_1); //13443
#ifdef DEBUG
    _dprintf("DDR_TIMING_1 val = 0x%08x\r\n",ddr_timing_1);
#endif

    //-------------------------------------------------------------
    // 4. DDR_TIMING_2 set
    //-------------------------------------------------------------
    ddr_timing_2 = (DDR_TIMING_2_TREFR | \
                    DDR_TIMING_2_INIT_TIME \
                    );
    
    nx_cpuif_reg_write_one(DDRC_REG_10, ddr_timing_2); //0x618
#ifdef DEBUG
    _dprintf("DDR_TIMING_2 val = 0x%08x\r\n",ddr_timing_2);
#endif

    //-------------------------------------------------------------
    // 5. DDR_PHY_CONFIG set
    //-------------------------------------------------------------
    //nx_cpuif_reg_write_one(DDRC_REG_0, 0x9E81); //start

    ddr_phy_config = (DDR_PHY_CONFIG_START | \
                      /* DDR_PHY_CONFIG_DIS_CALIB \ */
                      DDR_PHY_CONFIG_DIS_PWRSEQ | //|             \
                      /* DDR_PHY_CONFIG_DIS_RDQCPT | \ */
                      /* DDR_PHY_CONFIG_DIS_ALIGN | \ */
                      DDR_PHY_CONFIG_DIS_LATENCY | \
                      DDR_PHY_CONFIG_DIS_VERIFY \
                      /* DDR_PHY_CONFIG_ERR_IGNORE \ */
                      );
#ifdef DEBUG
    _dprintf("DDR_PHY_CONFIG val = 0x%08x\r\n",ddr_phy_config);
#endif
    nx_cpuif_reg_write_one(DDRC_REG_0, ddr_phy_config);

    do {
	    nDDRC_init = nx_cpuif_reg_read_one(DDRC_REG_0, 0);
            udelay(500);
#ifdef DEBUG
            _dprintf("nDDRC_init loop = 0x%08x\r\n",nDDRC_init);
            _dprintf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\r\n");
            _dprintf("DDRC_REG_1C = 0x%x\r\n", nx_cpuif_reg_read_one(DDRC_REG_1C, 0)); //DDR_CFG_RDQ_LATENCY
            _dprintf("DDRC_REG_20 = 0x%x\r\n", nx_cpuif_reg_read_one(DDRC_REG_20, 0)); //DDR_CFG_RDQ_DLYVAL 
            _dprintf("DDRC_REG_24 = 0x%x\r\n", nx_cpuif_reg_read_one(DDRC_REG_24, 0)); //DDR_CFG_CMD_DLYVAL 
            _dprintf("DDRC_REG_40 = 0x%x\r\n", nx_cpuif_reg_read_one(DDRC_REG_40, 0)); //DDR_STS_RDQ_LATENCY
            _dprintf("DDRC_REG_48 = 0x%x\r\n", nx_cpuif_reg_read_one(DDRC_REG_48, 0)); //DDR_STS_RDQ_DLYVAL 
            _dprintf("DDRC_REG_4C = 0x%x\r\n", nx_cpuif_reg_read_one(DDRC_REG_4C, 0)); //DDR_STS_CMD_DLYVAL 
            _dprintf("DDRC_REG_50 = 0x%x\r\n", nx_cpuif_reg_read_one(DDRC_REG_50, 0)); //DDR_STS_VERF_ERRPOS
            _dprintf("DDRC_REG_54 = 0x%x\r\n", nx_cpuif_reg_read_one(DDRC_REG_54, 0)); //DDR_STS_VERF_ERRDATA_L
            _dprintf("DDRC_REG_58 = 0x%x\r\n", nx_cpuif_reg_read_one(DDRC_REG_58, 0)); //DDR_STS_VERF_ERRDATA_H
            _dprintf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\r\n");   
#endif
    } while(!((nDDRC_init & DDR_PHY_CONFIG_SUCCESS)>>4));

#ifdef DEBUG
    _dprintf("nDDRC_init = 0x%x \r\n",nDDRC_init);
    if ((nDDRC_init & DDR_PHY_CONFIG_COMPLETE) >> 4) {
        _dprintf("==> DDRC init complete !! \r\n");
        _dprintf("==> read one = 0x%x \r\n",mmio_read_32((unsigned int*)PHY_BASEADDR_DDRC0_MODULE));
    }
    
    nDDRC_init = nx_cpuif_reg_read_one(DDRC_REG_0, 0);
    if ((nDDRC_init & DDR_PHY_CONFIG_SUCCESS) >> 5) {
        _dprintf("==> DDRC init Success !! \r\n");
        _dprintf("==> read one = 0x%x \r\n",mmio_read_32((unsigned int*)PHY_BASEADDR_DDRC0_MODULE));
    }

#endif

    //-------------------------------------------------------------

#ifdef MEMTEST
   udelay(200);
   /* if (simple_memtest_8bit() == 0) { */
   /*      _dprintf("memtest 8b end\r\n"); */
   /*      return ; */
   /* } */
   /* if (simple_memtest_16bit() == 0) { */
   /* 	_dprintf("memtest 16b end\r\n"); */
   /*      return ; */
   /* } */
   /* if (simple_memtest_32bit() == 0) { */
   /* 	_dprintf("memtest 32b end\r\n"); */
   /*      return ; */
   /* } */
   if (simple_memtest_burst() == 0) {
   	_dprintf("memtest burst end\r\n");
        return ;
   }

#else //MEMTEST

#ifdef DEBUG
   serial_init(0); //channel = 0

   _dprintf("bootloader~start\r\n");
   _dprintf("Bl1 Start \r\n");
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
