#ifndef SSP_H
#define SSP_H

#include "lpc17xx.h"

enum PORTS
{
	SSP0=0,
	SSP1
};

enum PERIPHERALS
{ 
		PCTIM0=1,
		PCTIM1,
		PCUART0,
		PCUART1,
		PCPWM1=6,
		PCI2C0,
		PCSPI,
		PCRTC,
		PCSSP1,
		PCADC=12,
		PCCAN1,
		PCCAN2,
		PCGPIO,
		PCRIT,
		PCMCPWM,
		PCQEI,
		PCI2C1,
		PCSSP0=21,
		PCTIM2,
		PCTIM3,
		PCUART2,
		PCUART3, 
		PCI2C2, 
		PCI2S, 
		PCGPDMA=29,
		PCENET,
		PCUSB 
};

int init_ssp(enum PORTS);
char spi_ExchangeByte(enum PORTS, char out);

void device_power_on( LPC_SC_TypeDef        * sc, enum PERIPHERALS  peripheral_device )
{
	sc->PCONP |= ( 1 << peripheral_device );
}

void device_power_off( LPC_SC_TypeDef			* sc, enum PERIPHERALS peripheral_device )
{
	sc->PCONP &= ~( 1 << peripheral_device );
}