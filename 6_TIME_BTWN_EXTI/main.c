#include "stm32f10x.h"                  			// Device header
#include "delay.h"														// Auxiliary delay function included for tests (1 second = 6000000 counts)
#include <math.h>															// Math Library

void TIMER_SETUP(void);
void PORT_SETUP(void);
void INTERRUPT_SETUP(void);

void EXTI0_IRQHandler(void);

volatile uint32_t count=0;
volatile float time1=0,time2=0;

int main(){
	
		PORT_SETUP(); 														// Set PC13 as outpout and PA0 as input
		INTERRUPT_SETUP(); 												// Enable interrupts and set PA0 as interrupt input
		TIMER_SETUP(); 														// Enable TIMER2 and iniciate it

	while(1){
		
		time1 = TIM2->CNT;
		GPIOA->ODR ^= GPIO_ODR_ODR1;							// Switch PA1 state
		delay(6000000);
				
		if(count==1){
			time2 = TIM2->CNT - time1;
			if(time2>=3000){
				GPIOC->ODR ^= GPIO_ODR_ODR13;					// Switch LED state
		}
		count=0;
		time2=0;
		TIM2->CNT = 0x00;													// Reset TIMER2 counting
		}
				
}

}

void TIMER_SETUP(){
	
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 			// TIMER2 clock enabled
		TIM2->CR1 = 0x00U; 												// Reset TIMER2 Control Register 1
		TIM2->CR2 = 0x00U; 												// Reset TIMER2 Control Register 2
		TIM2->CR1 |= TIM_CR1_ARPE; 								// TIMER2 auto reload preload enable
		TIM2->DIER |= TIM_DIER_UIE; 							// TIMER2 enable update interrupt
		TIM2->PSC = 24000 -1; 										// TIMER2 prescaler set
		TIM2->ARR = 65535 -1; 										// TIMER2 re-start counting set (in miliseconds*3)
		TIM2->SR  = 0x00U;												// TIMER2 Status Register reset
		TIM2->CR1 |= TIM_CR1_CEN; 								// TIMER2 counter enable
}

void PORT_SETUP(){
	
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; 			// Clock enable for Port C
		GPIOC->CRH |= GPIO_CRH_MODE13_0;    			// Pin 13 output mode
		GPIOC->ODR |= GPIO_ODR_ODR13;       			// LED off ( LED on is "GPIOC->ODR &= (~GPIO_ODR_ODR13);" )
	
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 			// Clock enable for Port A
		GPIOA->CRL &= 0x00;                 			// Port A all pins input mode
		GPIOA->CRL |= 0x00000008;									// Port A pin 0 input pull up/down configuration
		GPIOA->CRL |= GPIO_CRL_MODE1_1;						// Port A pin 1 output mode
		GPIOA->ODR |= GPIO_ODR_ODR1;
}

void INTERRUPT_SETUP(){
		RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;				// Clock enable for pin alternate functions
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA; // Set PA0 as external interrupt
		EXTI->IMR |= EXTI_IMR_MR0;								// Unmask EXTI0 line 0
		EXTI->RTSR |= EXTI_RTSR_TR0;							// EXTI0 rising edge configuration on line 0 set
		EXTI->FTSR = 0x00;												// EXTI0 falling edge configuration on line 0 not set
		NVIC_EnableIRQ(EXTI0_IRQn);								// Enable interrupts on EXTI0
}

void EXTI0_IRQHandler(void){

	EXTI->PR |= EXTI_PR_PR0;										// Pending bit on EXTI0 line 0
	count++;
	
}
