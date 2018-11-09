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

#define PLLCON                                   		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_SYS_CON0_MODULE, 0x0, 0, 32 }

#define DDRC_REG_PHY_CONFIG		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x0>>0, 0, 32 }
#define DDRC_REG_ADDR_SIZE		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x4>>2, 0, 32 }
#define DDRC_REG_TIMING0		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x8>>2, 0, 32 }
#define DDRC_REG_TIMING1		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xC>>2, 0, 32 }
#define DDRC_REG_TIMING2		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x10>>2, 0, 32 }
#define DDRC_REG_LMR_EXT_STD		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x14>>2, 0, 32 }

#define DDRC_REG_PHY_CONFIG_ADDR	(PHY_BASEADDR_DDRC0_MODULE + 0x0)
#define DDRC_REG_ADDR_SIZE_ADDR		(PHY_BASEADDR_DDRC0_MODULE + 0x4)
#define DDRC_REG_TIMING0_ADDR		(PHY_BASEADDR_DDRC0_MODULE + 0x8)
#define DDRC_REG_TIMING1_ADDR		(PHY_BASEADDR_DDRC0_MODULE + 0xC)
#define DDRC_REG_TIMING2_ADDR		(PHY_BASEADDR_DDRC0_MODULE + 0x10)
#define DDRC_REG_LMR_EXT_STD_ADDR	(PHY_BASEADDR_DDRC0_MODULE + 0x14)

#define DDRC_REG_18		        (__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x18>>2, 0, 32 } //only DDR2, DDR3

#define DDRC_REG_CFG_RDQ_LATENCY	(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x1C>>2, 0, 32 } //DDR_CFG_RDQ_LATENCY
#define DDRC_REG_CFG_RDQ_DLYVAL		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x20>>2, 0, 32 } //DDR_CFG_RDQ_DLYVAL

#define DDRC_REG_24		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x24>>2, 0, 32 } //DDR_CFG_CMD_DLYVAL
#define DDRC_REG_40		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x40>>2, 0, 32 } //DDR_STS_RDQ_LATENCY
#define DDRC_REG_48		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x48>>2, 0, 32 } //DDR_STS_RDQ_DLYVAL
#define DDRC_REG_4C		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x4C>>2, 0, 32 } //DDR_STS_CMD_DLYVAL

#define DDRC_REG_50		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x50>>2, 0, 32 } //DDR_STS_VERF_ERRPOS   
#define DDRC_REG_54		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x54>>2, 0, 32 } //DDR_STS_VERF_ERRDATA_L
#define DDRC_REG_58		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x58>>2, 0, 32 } //DDR_STS_VERF_ERRDATA_H

#define DDRC_REG_60		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x60>>2, 0, 32 }
#define DDRC_REG_64		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x64>>2, 0, 32 }
#define DDRC_REG_68		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x68>>2, 0, 32 }
#define DDRC_REG_6C		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x6C>>2, 0, 32 }
#define DDRC_REG_70		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x70>>2, 0, 32 }
#define DDRC_REG_74		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x74>>2, 0, 32 }
#define DDRC_REG_78		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x78>>2, 0, 32 }
#define DDRC_REG_7C		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x7C>>2, 0, 32 }
#define DDRC_REG_80		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x80>>2, 0, 32 }
#define DDRC_REG_84		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x84>>2, 0, 32 }
#define DDRC_REG_88		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x88>>2, 0, 32 }
#define DDRC_REG_8C		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x8C>>2, 0, 32 }
#define DDRC_REG_90		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x90>>2, 0, 32 }
#define DDRC_REG_94		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x94>>2, 0, 32 }
#define DDRC_REG_98		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x98>>2, 0, 32 }
#define DDRC_REG_9C		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x9C>>2, 0, 32 }
#define DDRC_REG_A0		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xA0>>2, 0, 32 }
#define DDRC_REG_A4		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xA4>>2, 0, 32 }
#define DDRC_REG_A8		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xA8>>2, 0, 32 }
#define DDRC_REG_AC		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xAC>>2, 0, 32 }
#define DDRC_REG_B0		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xB0>>2, 0, 32 }
#define DDRC_REG_B4		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xB4>>2, 0, 32 }
#define DDRC_REG_B8		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xB8>>2, 0, 32 }
#define DDRC_REG_BC		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xBC>>2, 0, 32 }
#define DDRC_REG_C0		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xC0>>2, 0, 32 }
#define DDRC_REG_C4		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xC4>>2, 0, 32 }
#define DDRC_REG_C8		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xC8>>2, 0, 32 }
#define DDRC_REG_CC		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xCC>>2, 0, 32 }
#define DDRC_REG_D0		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xD0>>2, 0, 32 }
#define DDRC_REG_D4		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xD4>>2, 0, 32 }
#define DDRC_REG_D8		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xD8>>2, 0, 32 }
#define DDRC_REG_DC		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xDC>>2, 0, 32 }
#define DDRC_REG_E0		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xE0>>2, 0, 32 }
#define DDRC_REG_E4		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xE4>>2, 0, 32 }
#define DDRC_REG_E8		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xE8>>2, 0, 32 }
#define DDRC_REG_EC		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xEC>>2, 0, 32 }
#define DDRC_REG_F0		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xF0>>2, 0, 32 }
#define DDRC_REG_F4		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xF4>>2, 0, 32 }
#define DDRC_REG_F8		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xF8>>2, 0, 32 }
#define DDRC_REG_FC		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0xFC>>2, 0, 32 }
#define DDRC_REG_100		(__nx_cpuif_symbol__){(unsigned int*)PHY_BASEADDR_DDRC0_MODULE, 0x100>>2, 0, 32 }

#define DDR_ADDR_SIZE_COL_SIZE      (2 << 0)
#define DDR_ADDR_SIZE_ROW_SIZE      (1 << 2)
#define DDR_ADDR_SIZE_BANK_SIZE     (0 << 4)
#define DDR_ADDR_SIZE_ADDR_MAP      (0 << 5)
#define DDR_ADDR_SIZE_SEL_MDDR      (1 << 7)
#define DDR_ADDR_SIZE_IO_STRENGTH   (1 << 8) //0
#define DDR_ADDR_SIZE_IO_DRIVESEL   (1 << 10)
#define DDR_ADDR_SIZE_IO_ODTSEL     (1 << 11)
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

#define DDR_LMR_EXT_STD_SLMR        (0x32 << 0)
#define DDR_LMR_EXT_STD_ELMR        ((0x2<<5) << 16) //0

#define DDR_CFG_RDQ_LATENCY_LATENCY (0x7 << 0)
#define DDR_CFG_RDQ_LATENCY_ALIGN   (0x0 << 8)

#define DDR_CFG_RDQ_DLYVAL_0   (0x0 << 0)
#define DDR_CFG_RDQ_DLYVAL_1   (0x0 << 8)
#define DDR_CFG_RDQ_DLYVAL_2   (0x0 << 16)
#define DDR_CFG_RDQ_DLYVAL_3   (0x0 << 24)

//-----------------------------------------
//---------------- TIMING -----------------
//-----------------------------------------
#define CLK_200MHZ     (200)
#define CLK_166MHZ     (150)
#define CLK_100MHZ     (100)
#define CLK_50MHZ      (50)

#define CLK_SPEED      CLK_100MHZ
#define CL_3
//#define CL_2

#if CLK_SPEED == CLK_200MHZ //-5 degree
#ifdef CL_3
#define TCK            5
#else //CL_2
#define TCK            12
#endif
#define TRAS           (40) //ns
#define TRFC           (72) //ns
#define TRP            (3*TCK)
#define TRC            (TRAS + TRP) //ns
#define TRCD 	       (15) //ns
#define TRRD           (10) //ns
#define TWR            (15) //ns
#define TWTR           (1*TCK)
#define TMRD           (2*TCK)
#define TDQSS          (1*TCK) //0.75 tCK
#define TREFR          (7.8 * 1000) //ns
#define INIT_TIME      (200 * 1000) //ns
#define EXTRA_FACTOR   0
#else // !200MHZ  -6 degree
#ifdef CL_3
#if CLK_SPEED == CLK_100MHZ //-5 degree
#define TCK            10 //6
#else
#define TCK            20 //6
#endif
#else //CL_2
#define TCK            12
#endif
#define TRAS           (42) //ns
#define TRFC           (72) //ns
#define TRP            (3*TCK)
#define TRC            (TRAS + TRP) //ns
#define TRCD 	       (18) //ns
#define TRRD           (12) //ns
#define TWR            (15) //ns
#define TWTR           (1*TCK)
#define TMRD           (2*TCK)
#define TDQSS          (1*TCK) //0.75 tCK
#define TREFR          (7.8 * 1000) //ns
#define INIT_TIME      (200 * 1000) //ns
#define EXTRA_FACTOR   1
#endif

#define DDR_TIMING_0_TRAS           (((unsigned int)(TRAS * CLK_SPEED / 1000) + EXTRA_FACTOR) << 0)  //8
#define DDR_TIMING_0_TRFC           (((unsigned int)(TRFC * CLK_SPEED / 1000) + EXTRA_FACTOR) << 8)  //14.4
#define DDR_TIMING_0_TRC            (((unsigned int)(TRC  * CLK_SPEED / 1000) + EXTRA_FACTOR) << 16) //11
#define DDR_TIMING_1_TRCD           (((unsigned int)(TRCD * CLK_SPEED / 1000) + EXTRA_FACTOR) << 0)  //3
#define DDR_TIMING_1_TRP            (((unsigned int)(TRP  * CLK_SPEED / 1000) + EXTRA_FACTOR) << 4)  //3
#define DDR_TIMING_1_TRRD           (((unsigned int)(TRRD * CLK_SPEED / 1000) + EXTRA_FACTOR) << 8)  //2
#define DDR_TIMING_1_TWR            (((unsigned int)(TWR  * CLK_SPEED / 1000) + EXTRA_FACTOR) << 12) //2
#define DDR_TIMING_1_TWTR           (((unsigned int)(TWTR * CLK_SPEED / 1000) + EXTRA_FACTOR) << 16) //1
#define DDR_TIMING_1_TMRD           (((unsigned int)(TMRD * CLK_SPEED / 1000) + EXTRA_FACTOR) << 20) //2 (1 << 20)
#define DDR_TIMING_1_TDQSS          (((unsigned int)(TDQSS* CLK_SPEED / 1000)) << 22) //1 (1 << 22)
#define DDR_TIMING_2_TREFR          (((unsigned int)(TREFR * CLK_SPEED / 1000)) << 0) //0x618
#define DDR_TIMING_2_INIT_TIME      (((unsigned int)(INIT_TIME * CLK_SPEED / 1000)) << 16) //0x9C40


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

#define MSTATUS_UIE         0x00000001
#define MSTATUS_SIE         0x00000002
#define MSTATUS_HIE         0x00000004
#define MSTATUS_MIE         0x00000008
#define MSTATUS_UPIE        0x00000010
#define MSTATUS_SPIE        0x00000020
#define MSTATUS_HPIE        0x00000040
#define MSTATUS_MPIE        0x00000080
#define MSTATUS_SPP         0x00000100
#define MSTATUS_HPP         0x00000600
#define MSTATUS_MPP         0x00001800

#define IRQ_S_SOFT   1
#define IRQ_H_SOFT   2
#define IRQ_M_SOFT   3
#define IRQ_S_TIMER  5
#define IRQ_H_TIMER  6
#define IRQ_M_TIMER  7
#define IRQ_S_EXT    9
#define IRQ_H_EXT    10
#define IRQ_M_EXT    11

#define MIP_SSIP            (1 << IRQ_S_SOFT)
#define MIP_HSIP            (1 << IRQ_H_SOFT)
#define MIP_MSIP            (1 << IRQ_M_SOFT)
#define MIP_STIP            (1 << IRQ_S_TIMER)
#define MIP_HTIP            (1 << IRQ_H_TIMER)
#define MIP_MTIP            (1 << IRQ_M_TIMER)
#define MIP_SEIP            (1 << IRQ_S_EXT)
#define MIP_HEIP            (1 << IRQ_H_EXT)
#define MIP_MEIP            (1 << IRQ_M_EXT)

#ifndef __ASSEMBLY__

#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })

#define write_csr(reg, val) ({ \
  asm volatile ("csrw " #reg ", %0" :: "rK"(val)); })

#define swap_csr(reg, val) ({ unsigned long __tmp; \
  asm volatile ("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "rK"(val)); \
  __tmp; })

#define set_csr(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); \
  __tmp; })

#define clear_csr(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); \
  __tmp; })

#define rdtime() read_csr(time)
#define rdcycle() read_csr(cycle)
#define rdinstret() read_csr(instret)
#endif

#define CSR_CYCLE 0xc00
#define CSR_TIME 0xc01
#define CSR_INSTRET 0xc02
#define CSR_CYCLEH 0xc80
#define CSR_TIMEH 0xc81
#define CSR_INSTRETH 0xc82

#define CSR_MSTATUS 0x300
#define CSR_MEDELEG 0x302
#define CSR_MIDELEG 0x302
#define CSR_MIE 0x304
#define CSR_MSCRATCH 0x340
#define CSR_MCAUSE 0x342
#define CSR_MIP 0x344

#ifdef DECLARE_CSR
DECLARE_CSR(cycle, CSR_CYCLE)
DECLARE_CSR(time, CSR_TIME)
DECLARE_CSR(instret, CSR_INSTRET)
DECLARE_CSR(cycleh, CSR_CYCLEH)
DECLARE_CSR(timeh, CSR_TIMEH)
DECLARE_CSR(instreth, CSR_INSTRETH)

DECLARE_CSR(mstatus, CSR_MSTATUS)
DECLARE_CSR(medeleg, CSR_MEDELEG)
DECLARE_CSR(mideleg, CSR_MIDELEG)
DECLARE_CSR(mie, CSR_MIE)
DECLARE_CSR(mcause, CSR_MCAUSE)
DECLARE_CSR(mip, CSR_MIP)
DECLARE_CSR(mscratch, CSR_MSCRATCH)
#endif

#endif //__NX_CPUIF_REGMAP_H__
