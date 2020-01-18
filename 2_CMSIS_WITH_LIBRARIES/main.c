#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "PortCinit.h"
#define LEDON (GPIO_ODR_ODR13)

#define SW1 (1U<<14)

uint32_t SW_INPUT(void);
void LED_ON(uint32_t LED);

int main(){
	
			PortCinit(); // Init port C (PC13 OUTPUT mode, PC14 INPUT mode & OPENDRAIN configuration)
			uint32_t sw_state;
			sw_state = (GPIO_IDR_IDR14);
	
while(1){
	
	if(SW_INPUT()){
			LED_ON(LEDON);
	}
		}
	
	}

uint32_t SW_INPUT(void){
 
	return (GPIOC->IDR & GPIO_IDR_IDR14);
}

void LED_ON(uint32_t LED){
	GPIOC->ODR ^= LED;
}
