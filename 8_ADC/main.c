#include "stm32f10x.h"                  						// Device header
#include <string.h>
#include <stdio.h>

void ADC_Init(void);
void usartSetup (void);
void SendChar(int ch);

uint8_t aux=0;
uint32_t value;
char str[50];

int main(){

	usartSetup();																			// Setup the USART comunication
	ADC_Init();																				// Init and setup ADC1
	
	while(1){
		
		while((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC);		// Wait for the end of conversion
		
		value = ADC1->DR;
		sprintf(str,"VALOR= %d\n",value);
		while(str[aux]!='\0'){
            SendChar(str[aux]);
            aux++;
            }
		aux = 0;
	}
	
}

void ADC_Init(void){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL = 0x00;
	
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC1->CR1 = 0x00;																	//
	ADC1->CR2 = 0x00;																	//
	ADC1->SMPR1 = 0x00;																//
	ADC1->SMPR2 = 0x00;																//
	ADC1->SQR1  = 0x00;																//
	ADC1->SQR2  = 0x00;																//
	ADC1->SQR3  = 0x00;													      // Reset all ADC1 configuration registers
	
	ADC1->CR2 |= ADC_CR2_ADON;												// ADC1_ON for the first time for power-up
	
	ADC1->CR2 |= ADC_CR2_CONT;												// ADC1 continuous conversion set
	RCC->CFGR |= RCC_CFGR_ADCPRE_0;										// ADC1 prescaler set (in this case: PCCLK/4)
	ADC1->SQR1  |= ADC_SQR1_L;												// ADC1 regular channels all set
	ADC1->SMPR2 = ADC_SMPR2_SMP0_0;										// ADC1 channel 0 (PA0) choosed
	
	ADC1->CR2 |= ADC_CR2_ADON;												// ADC1_ON for the second time to start converting
}

void usartSetup (void) {
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;             // Enable clock for GPIOA
  GPIOA->CRH   |= (0x0BUL  << 4);                 // Tx (PA9) alt. out push-pull
  GPIOA->CRH   |= (0x04UL  << 8);                 // Rx (PA10) in floating
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;           // Enable clock for USART1
  USART1->BRR  = 72000000L/9600;   					      // Set baudrate (SystemClock/DesiredBaudrate)
  USART1->CR1 |= (USART_CR1_RE | USART_CR1_TE);  	// RX, TX enable
  USART1->CR1 |= USART_CR1_UE;                    // USART enable
  }

void SendChar (int ch)  {
  while (!(USART1->SR & USART_SR_TXE));
  USART1->DR = (ch & 0xFF);
  return;
}
