#include "stm32f10x.h"                  // Device header
#include "delay.h"

#define LED (1U<<13)

void Timer2_OneShot(int mdelay);

void Timer2_Periodic(int mdelay);

void PortC_Pin13_Init(void);

int j;

int main(){
	
	
	PortC_Pin13_Init();
	
	while(1){
	
		GPIOC->ODR ^= GPIO_ODR_ODR13;
		Timer2_Periodic(1000);
		
	}
	
}

void PortC_Pin13_Init(void){

	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= GPIO_CRH_MODE13_0;
	GPIOC->ODR |= GPIO_ODR_ODR13;
}

void Timer2_OneShot(int mdelay){

	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // TIMER2 clock enabled
	TIM2->CR1 = 0x00U; // Reset TIMER2 Control Register 1
	TIM2->CR2 = 0x00U; // Reset TIMER2 Control Register 2
	TIM2->CR1 |= TIM_CR1_OPM; // TIMER2 One-Pulse mode
	TIM2->CR1 |= TIM_CR1_ARPE; //TIMER2 auto reload preload enable
	TIM2->DIER |= TIM_DIER_UIE; // TIMER2 enable update interrupt
	TIM2->PSC = 24000; // TIMER2 prescale set
	TIM2->ARR |= 3 *mdelay-1; // TIMER2 start counting set 
	TIM2->CR1 |= TIM_CR1_CEN; // TIMER2 counter enable
	
	while((TIM2->SR & TIM_SR_UIF)==0x00); // Wait for timeout(update interrupt) flag to set
}

void Timer2_Periodic(int mdelay){
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // TIMER2 clock enabled
	TIM2->CR1 = 0x00U; // Reset TIMER2 Control Register 1
	TIM2->CR2 = 0x00U; // Reset TIMER2 Control Register 2
	TIM2->CR1 |= TIM_CR1_ARPE; //TIMER2 auto reload preload enable
	TIM2->DIER |= TIM_DIER_UIE; // TIMER2 enable update interrupt
	TIM2->PSC = 24000 -1; // TIMER2 prescale set
	TIM2->ARR = 3 -1; // TIMER2 start counting set
	TIM2->SR  = 0x00U;	// TIMER2 Status Register reset
	TIM2->CR1 |= TIM_CR1_CEN; // TIMER2 counter enable
	
	for(j=0; j<(mdelay); j++)
	{	
		while((TIM2->SR & TIM_SR_UIF)==0x00); // Wait for timeout(update interrupt) flag to set
		TIM2->SR = 0x00U;
	}
}
