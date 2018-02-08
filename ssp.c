/* Niraj Khadka
console1913@gmail.com
2018, kathmandu, nepal
*/

#include "ssp.h"

int init_ssp(enum PORTS){
	
	switch PORTS{
		case 0:
			device_power_on( LPC_SC, PCSSP0)
			//PCLKSEL1 for SSP0 and PCLKSEL0 for SSP1
			LPC_SC->PCLKSEL1 &= ~(3 << 20); // Clear clock Bits
			LPC_SC->PCLKSEL1 |=  (1 << 20); // CLK / 1
		
			// Select SCK pin-select functionality
			LPC_PINCON->PINSEL0 &= ~( (3 << 30));	//setting bit 30 to 1 
			LPC_PINCON->PINSEL0 |=  ( (2 << 30));
			// Select MISO and MOSI pin-select functionality
			LPC_PINCON->PINSEL1 &= ~( (3 << 2) | (3 << 4) );
			LPC_PINCON->PINSEL1 |=  ( (2 << 2) | (2 << 4 |) );
		
			LPC_SSP0->CR0 = 7;          // 8-bit mode
			LPC_SSP0->CR1 = (1 << 1);   // Enable SSP as Master
			LPC_SSP0->CPSR = 8;         // SCK speed = CPU / 8
			break;
			
		case 1:
			device_power_on( LPC_SC, PCSSP1)
			//PCLKSEL1 for SSP0 and PCLKSEL0 for SSP1
			LPC_SC->PCLKSEL0 &= ~(3 << 20); // Clear clock Bits
			LPC_SC->PCLKSEL0 |=  (1 << 20); // CLK / 1
		
			// Select MISO, MOSI, and SCK pin-select functionality
			LPC_PINCON->PINSEL0 &= ~( (3 << 14) | (3 << 16) | (3 << 18) );
			LPC_PINCON->PINSEL0 |=  ( (2 << 14) | (2 << 16) | (2 << 18) );

			LPC_SSP1->CR0 = 7;          // 8-bit mode
			LPC_SSP1->CR1 = (1 << 1);   // Enable SSP as Master
			LPC_SSP1->CPSR = 8;         // SCK speed = CPU / 8
			break;
		
		default:
			return 0;
	}
	return 1;
}

char spi_ExchangeByte(enum PORTS, char out)
{
	if(PORTS == 0){
		LPC_SSP0->DR = out;
		while(LPC_SSP0->SR & (1 << 4)); // Wait until SSP is busy
		return LPC_SSP0->DR;
	}
	else if(PORTS == 1){
		LPC_SSP1->DR = out;
		while(LPC_SSP1->SR & (1 << 4)); // Wait until SSP is busy
		return LPC_SSP1->DR;
	}
	return NULL;
}
