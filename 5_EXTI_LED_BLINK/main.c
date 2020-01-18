#include "stm32f10x.h"                  // Device header

void EXTI0_IRQHandler(void); 

volatile uint32_t flag;

int main(){
	
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Clock enable for Port C
		GPIOC->CRH |= GPIO_CRH_MODE13_0;    // Pin 13 output mode
		GPIOC->ODR |= GPIO_ODR_ODR13;       // LED off
	
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Clock enable for Port A
		GPIOA->CRL &= 0x00;                 // Port A all pins input mode
		GPIOA->CRL |= 0x00000008;						// Port A pin 0 in input pull up/down configuration
	
		RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;	// Clock enable for pin alternate functions
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA; // Set PA0 as external interrupt
		EXTI->IMR |= EXTI_IMR_MR0;					// Unmask EXTI0 line 0
		EXTI->RTSR |= EXTI_RTSR_TR0;				// EXTI0 rising edge configuration on line 0 set
		EXTI->FTSR |= 0X00;									// EXTI0 falling edge configuration on line 0 not set
		NVIC_EnableIRQ(EXTI0_IRQn);					// Enable interrupts on EXTI0
		
		while(1){
			
		}
		
}

void EXTI0_IRQHandler(void){

	EXTI->PR |= EXTI_PR_PR0;							// Pending bit on EXTI0 line 0
	GPIOC->ODR ^= GPIO_ODR_ODR13;					// LED switch state

}
