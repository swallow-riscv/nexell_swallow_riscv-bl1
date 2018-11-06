//#include "nx_qemu_sim_printf.h"
#define mmio_write_32(addr,data) (*(volatile unsigned int *)(addr)) = ((unsigned int)(data))
#define mmio_read_32(addr)       (*(volatile unsigned int *)(addr))

/* #define csr_read(csr)						\ */
/* ({								\ */
/* 	register unsigned long __v;				\ */
/* 	__asm__ __volatile__ ("csrr %0, " #csr			\ */
/* 			      : "=r" (__v) :			\ */
/* 			      : "memory");			\ */
/* 	__v;							\ */
/* }) */

int main()
{
//for test
 #ifdef SOC_SIM
    volatile unsigned char *reg = (unsigned char*)0x20A00000;//PHY_BASEADDR_DUMMY_MODULE;

    *reg = 'v';
    *reg = 'e';
    *reg = 'c';
    /* unsigned char test[32] = "vector table test\n"; */
    /* int i = 0; */
    /* while(test[i] != '\0') { */
    /*     *reg = test[i]; */
    /*     i++; */
    /* } */
    /* _dprintf("vector run\n"); */
    /* _dprintf("pc addr = 0x%x\n",csr_read(mepc)); */
#endif
   
    unsigned int g_uart_reg = 0x20880000;
    char s[16] = "Jump Test\r\n";
    for (int i=0; i<=16; i++) {
        while (!(mmio_read_32(g_uart_reg + 0x7C) & (1 << 1)));
        mmio_write_32((g_uart_reg + 0x00), (unsigned int)(s[i]));
    }

    while(1);
    return 0;
}
