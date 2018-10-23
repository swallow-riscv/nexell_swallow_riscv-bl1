#ifndef __NX_CPUIF_REGMAP_H__
#define __NX_CPUIF_REGMAP_H__

#include "nx_chip_sfr.h"

typedef struct __nx_cpuif_symbol_struct__ {
    unsigned int *baseaddr;
    unsigned int offset;
    unsigned int startbit;
    unsigned int bitwidth;
}__nx_cpuif_symbol__ ;

#define CPUIF_END (__nx_cpuif_symbol__){0,0,0,0}
#define nx_cpuif_regmap_MAX_LIST 128

// modified with Prototype/nx_base/nx_clockcontrol.c
/*     { PHY_BASEADDR_CMU_SYS_MODULE, },  ///\*CMU_SYS[0] *\/ (0x20030000),}, */
#define CMU_INFO_DEF__SYS_0___CLK400__group_clock_source	(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_CMU_SYS_MODULE, 0x200>>2, 0, 32 }
#define CMU_INFO_DEF__SYS_0___CLK400__dynamic_divider_value	(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_CMU_SYS_MODULE, 0x260>>2, 0, 32 }
#define CMU_INFO_DEF__SYS_0___AXI__dynamic_divider_value	(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_CMU_SYS_MODULE, 0x264>>2, 0, 32 }
#define CMU_INFO_DEF__SYS_0___APB__dynamic_divider_value	(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_CMU_SYS_MODULE, 0x268>>2, 0, 32 }
#define CMU_INFO_DEF__SYS_0___CLK133__dynamic_divider_value	(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_CMU_SYS_MODULE, 0x26c>>2, 0, 32 }
#define CMU_INFO_DEF__SYS_0___CLK50__dynamic_divider_value	(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_CMU_SYS_MODULE, 0x270>>2, 0, 32 }
#define CMU_INFO_DEF__SYS_0___CLK40__dynamic_divider_value	(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_CMU_SYS_MODULE, 0x274>>2, 0, 32 }

#define CMU_INFO_DEF__CPU_0___CORE__group_clock_source		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_CMU_SYS_MODULE, 0x400>>2, 0, 32 }
#define CMU_INFO_DEF__CPU_0___CORE__dynamic_divider_value	(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_CMU_SYS_MODULE, 0x460>>2, 0, 32 }

#define PLL_INFO_0_CPUIF                         		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_PLL0_MODULE, 0x0, 3, 1 }
#define PLL_INFO_1_CPUIF                         		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_PLL1_MODULE, 0x0, 3, 1 }

#define DDRC_REG_0		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x0>>0, 0, 32 }
#define DDRC_REG_4		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x4>>2, 0, 32 }
#define DDRC_REG_8		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x8>>2, 0, 32 }
#define DDRC_REG_C		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xC>>2, 0, 32 }
#define DDRC_REG_10		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x10>>2, 0, 32 }

#define DDRC_REG_1C		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x1C>>2, 0, 32 } //DDR_CFG_RDQ_LATENCY
#define DDRC_REG_20		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x20>>2, 0, 32 } //DDR_CFG_RDQ_DLYVAL
#define DDRC_REG_24		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x24>>2, 0, 32 } //DDR_CFG_CMD_DLYVAL
#define DDRC_REG_40		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x40>>2, 0, 32 } //DDR_STS_RDQ_LATENCY
#define DDRC_REG_48		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x48>>2, 0, 32 } //DDR_STS_RDQ_DLYVAL
#define DDRC_REG_4C		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x4C>>2, 0, 32 } //DDR_STS_CMD_DLYVAL

#define DDRC_REG_50		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x50>>2, 0, 32 } //DDR_STS_VERF_ERRPOS   
#define DDRC_REG_54		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x54>>2, 0, 32 } //DDR_STS_VERF_ERRDATA_L
#define DDRC_REG_58		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x58>>2, 0, 32 } //DDR_STS_VERF_ERRDATA_H

#define DDR_ADDR_SIZE_COL_SIZE      (2 << 0)
#define DDR_ADDR_SIZE_ROW_SIZE      (2 << 2)
#define DDR_ADDR_SIZE_BANK_SIZE     (0 << 4)
#define DDR_ADDR_SIZE_ADDR_MAP      (0 << 5)
#define DDR_ADDR_SIZE_SEL_MDDR      (1 << 7)
#define DDR_ADDR_SIZE_IO_STRENGTH   (3 << 8)
#define DDR_ADDR_SIZE_IO_DRIVESEL   (1 << 10)
#define DDR_ADDR_SIZE_IO_ODTSEL     (0 << 11)
#define DDR_ADDR_SIZE_IO_ODTEN      (1 << 12)

#define DDR_PHY_CONFIG_START        (1 << 0)
#define DDR_PHY_CONFIG_CLEAR        (1 << 1)
#define DDR_PHY_CONFIG_COMPLETE     (1 << 4)
#define DDR_PHY_CONFIG_SUCCESS      (1 << 5)
#define DDR_PHY_CONFIG_DIS_CALIB    (1 << 7)
#define DDR_PHY_CONFIG_DIS_PWRSEQ   (1 << 8)
#define DDR_PHY_CONFIG_DIS_RDQCPT   (1 << 9)
#define DDR_PHY_CONFIG_DIS_ALIGN    (1 << 10)
#define DDR_PHY_CONFIG_DIS_LATENCY  (1 << 11)
#define DDR_PHY_CONFIG_DIS_VERIFY   (1 << 12)
#define DDR_PHY_CONFIG_ERR_IGNORE   (1 << 15)

#define DDR_TIMING_0_TRAS           (0xE << 0)
#define DDR_TIMING_0_TRFC           (0x28 << 8)
#define DDR_TIMING_0_TRC            (0xE << 16)

#define DDR_TIMING_1_TRCD           (0xF << 0) //4bit
#define DDR_TIMING_1_TRP            (0xF << 4) //4bit
#define DDR_TIMING_1_TRRD           (0xF << 7) //4bit
#define DDR_TIMING_1_TWR            (0xF << 11) //4bit
#define DDR_TIMING_1_TWTR           (0x7 << 15) //3bit
#define DDR_TIMING_1_TMRD           (0x3 << 18) //2bit
#define DDR_TIMING_1_TDQSS          (0x3 << 21) //2bit

#define DDR_TIMING_2_TREFR          (0x618 << 0) //7.8us
#define DDR_TIMING_2_INIT_TIME      (0xFFFF << 16)

#ifdef	__cplusplus
extern "C"
{
#endif

/* #ifdef __SOC__ */
/* void NX_CONSOLE_Printf(const char *FormatString, ...); */
/* #endif */

void nx_cpuif_reg_write_one(__nx_cpuif_symbol__ symbol, unsigned int  regval);
unsigned int nx_cpuif_reg_read_one ( __nx_cpuif_symbol__ symbol, unsigned int * regval );
/* void setSFRINFO(void); */
    
#ifdef	__cplusplus
}
#endif

#ifndef __ASSEMBLY__
#define csr_write(csr, val)					\
({								\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrw " #csr ", %0"		\
			      : : "rK" (__v)			\
			      : "memory");			\
})
#endif


#endif //__NX_CPUIF_REGMAP_H__
