#include "stm32f10x.h"                  // Device header
#include "delay.h"
#define LEDON (GPIO_ODR_ODR12<<1)

/*
#define RCC_APB2ENR (*(unsigned int *)0x40021018U)
#define GPIOC_CRL (*(unsigned int *)0x40011000U)
#define GPIOC_CRH (*(unsigned int *)0x40011004U)
#define GPIOC_ODR (*(unsigned int *)0x4001100CU)
*/

int main(){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // 0x00000010U = 0b 0000 0000 0000 0000 0000 0000 0001 0000
	GPIOC->CRH |= GPIO_CRH_MODE13_0;      // 0x00100000U = 0b 0000 0000 0001 0000 0000 0000 0000 0000
	
	while(1){
	
		GPIOC->ODR ^= LEDON; // 0x00002000U = 0b 0000 0000 0000 0000 0010 0000 0000 0000
		delay(2000000);
		
}
}
