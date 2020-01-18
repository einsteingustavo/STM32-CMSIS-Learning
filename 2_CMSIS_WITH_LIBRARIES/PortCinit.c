#include "stm32f10x.h"
#include "PortCinit.h"

void PortCinit(void){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= GPIO_CRH_MODE13_0;
	GPIOC->CRH |= GPIO_CRH_MODE14;
	GPIOC->CRH |= GPIO_CRH_CNF14_1;
}
