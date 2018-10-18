/*
 * Copyright (C) 2012 Nexell Co., All Rights Reserved
 * Nexell Co. Proprietary & Confidential
 *
 * NEXELL INFORMS THAT THIS CODE AND INFORMATION IS PROVIDED "AS IS" BASE
 * AND WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Module	: library
 * File		: libplat.c
 * Description	: various chip library
 * Author	: Hans
 * History	: 2016.08.12 First Implementation
 */

#include <nx_gpio.h>

#if defined(QEMU_RISCV) || defined(SOC_SIM)
#include <nx_qemu_sim_printf.h>
#else
#include <nx_swallow_printf.h>
#endif
#include <nx_swallow.h>

/* void GPIOReleasePAD(const struct nxpadi *pad) */
/* { */
/*     pAlive->GPIO_PWR[pad->grp].DOWN &= ~(1 << pad->pin);	// pad retention */
/* } */
void GPIOSetAltFunction(const struct nxpadi pad, int setalt)
{
    unsigned int regvalue;
    unsigned int alt = setalt ? pad.alt : 0;

    struct NX_GPIO (*const pGPIOxReg)[1] =
        (struct NX_GPIO (*)[])PHY_BASEADDR_GPIO3_MODULE;

    if (!pad.flag)
        return;

    if (GPIO_ALT_BITWIDTH == GPIO_ALT_BITWIDTH_3BIT) {
        regvalue = pGPIOxReg[pad.grp]->RWGPIO.GPIOx_ALTFN[pad.pin >> 4];
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_ALTFN[pad.pin >> 4] =
            (regvalue & ~(3 << ((pad.pin & 0xF) * 2))) |
            (alt << ((pad.pin & 0xF) * 2));
    } else if (GPIO_ALT_BITWIDTH == GPIO_ALT_BITWIDTH_2BIT) {
        regvalue = pGPIOxReg[pad.grp]->RWGPIO.GPIOx_ALTFN[0];
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_ALTFN[0] = (regvalue & ~(1 << pad.pin)) | (alt << pad.pin);
    } else {
        return;
    }
}

void GPIOSetDrvSt(const struct nxpadi pad, NX_GPIO_DRVSTRENGTH str)
{
    struct NX_GPIO (*const pGPIOxReg)[1] =
        (struct NX_GPIO (*)[])PHY_BASEADDR_GPIO3_MODULE;

    unsigned int d0 = str & 1, d1 = (str >> 1) & 1;

    if (!pad.flag)
        return;

    if (d0) {
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_DRV0 = 0x1 << pad.pin;
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_DRV0_DISABLE_DEFAULT = 0x1 << pad.pin;
    } else {
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_DRV0 &= ~(0x1 << pad.pin);
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_DRV0_DISABLE_DEFAULT &= ~(0x1 << pad.pin);
    }
    if (d1) {
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_DRV1 = 0x1 << pad.pin;
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_DRV1_DISABLE_DEFAULT = 0x1 << pad.pin;
    } else {
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_DRV1 &= ~(0x1 << pad.pin);
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_DRV1_DISABLE_DEFAULT &= ~(0x1 << pad.pin);
    }
}
void GPIOSetPullup(const struct nxpadi pad, NX_GPIO_PULL pull)
{
    struct NX_GPIO (*const pGPIOxReg)[1] =
        (struct NX_GPIO (*)[])PHY_BASEADDR_GPIO3_MODULE;

    unsigned int pullupdown = pull & 1, pullen = !((pull >> 1) & 1);

    if (!pad.flag)
        return;

    if (pullupdown) {
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_PULLSEL = 1 << pad.pin;
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_PULLSEL_DISABLE_DEFAULT = 1 << pad.pin;
    } else {
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_PULLSEL &= ~(1 << pad.pin);
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_PULLSEL_DISABLE_DEFAULT &= ~(1 << pad.pin);
    }
    if (pullen) {
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_PULLENB = 1 << pad.pin;
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_PULLENB_DISABLE_DEFAULT = 1 << pad.pin;
    } else {
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_PULLENB &= ~(1 << pad.pin);
        pGPIOxReg[pad.grp]->RWGPIO.GPIOx_PULLENB_DISABLE_DEFAULT &= ~(1 << pad.pin);
    }
}

void GPIOSetIO(const struct nxpadi pad, int inout)   /* 0: out, 1: in */
{
    struct NX_GPIO (*const pGPIOxReg)[1] =
        (struct NX_GPIO (*)[])PHY_BASEADDR_GPIO3_MODULE;

	if (!pad.flag)
		return;

	if (inout)
		pGPIOxReg[pad.grp]->RWGPIO.GPIOx_OUTENB &= ~(1 << pad.pin);
	else
		pGPIOxReg[pad.grp]->RWGPIO.GPIOx_OUTENB = 1 << pad.pin;
}

void GPIOSetOutput(const struct nxpadi pad, int outvalue)
{
    struct NX_GPIO (*const pGPIOxReg)[1] =
        (struct NX_GPIO (*)[])PHY_BASEADDR_GPIO3_MODULE;

	if (!pad.flag)
		return;

	if (outvalue)
		pGPIOxReg[pad.grp]->RWGPIO.GPIOx_OUT = 1 << pad.pin;
	else
		pGPIOxReg[pad.grp]->RWGPIO.GPIOx_OUT &= ~(1 << pad.pin);
}

void setpad(const struct nxpadi pad, int enable)
{
    int i;
        if (enable) {
            GPIOSetAltFunction(pad, 1);
            GPIOSetDrvSt(pad, NX_GPIO_DRVSTRENGTH_3);
            GPIOSetPullup(pad, NX_GPIO_PULL_OFF);
            /* if (ppad[i].padd) */
            /* 	GPIOReleasePAD(&ppad[i].padi); */
        } else {
            GPIOSetAltFunction(pad, 0);
            GPIOSetDrvSt(pad, NX_GPIO_DRVSTRENGTH_3);
        }
}
