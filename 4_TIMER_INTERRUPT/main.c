#include "stm32f10x.h"                  // Device header

#define FLAG_NONE 0x00U
#define FLAG_TOGGLE_LED TIM_SR_UIF

volatile uint32_t flags = FLAG_NONE;

void Timer2_Setup(void);

void TIM2_IRQHandler(void);

int main(){

	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= GPIO_CRH_MODE13_0;
	GPIOC->ODR |= GPIO_ODR_ODR13;
	Timer2_Setup();
	
	while(1){
			if(flags==FLAG_TOGGLE_LED){
				GPIOC->ODR ^= GPIO_ODR_ODR13;
				flags = FLAG_NONE;
			}
	}
	
}

void Timer2_Setup(void){
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // TIMER2 clock enabled
	TIM2->CR1 = 0x00U; // Reset TIMER2 Control Register 1
	TIM2->CR2 = 0x00U; // Reset TIMER2 Control Register 2
	TIM2->CR1 |= TIM_CR1_ARPE; //TIMER2 auto reload preload enable
	TIM2->DIER |= TIM_DIER_UIE; // TIMER2 enable update interrupt
	TIM2->PSC = 24000 -1; // TIMER2 prescaler set
	TIM2->ARR = 600 -1; // TIMER2 start counting set
	TIM2->SR  = 0x00U;	// TIMER2 Status Register reset
	NVIC_EnableIRQ(TIM2_IRQn); // Activate TIMER2 interrupt requests
	TIM2->CR1 |= TIM_CR1_CEN; // TIMER2 counter enable
}

void TIM2_IRQHandler(void){
	
	flags = FLAG_TOGGLE_LED;
	TIM2->SR = 0x00U;
}
