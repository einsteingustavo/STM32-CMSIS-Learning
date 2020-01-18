#include "stm32f10x.h"                  					// Device header

void usartSetup (void);
void SendChar (int ch);

int main(){

	usartSetup();
	
	while(1){
		
		SendChar('H');
		SendChar('e');
		SendChar('l');
		SendChar('l');
		SendChar('o');
		SendChar('!');
		SendChar(10);
		
	}
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
