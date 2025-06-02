#include <stdio.h>
#include <stdint.h>
#include "stm32g491xx.h"

//USART2 is connected to APB1
//PA2 - USART2_TX AF7
//PA3 - USART2_RX AF7

#define USART2EN (1U<<17)
#define CR1_TE (1U<<3)
#define CR1_UE (1U<<0)
#define SR_TXE (1U<<7)
//#define BUTTON_USR PIN13

#define GPIOAEN (1U<<0)
#define PIN5 (1U<<5)
#define LED_USR PIN5

#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define UART_BAUDRATE 115200

uint16_t compute_uart_bd(uint32_t periph_clk,uint32_t baud_rate)
{
	return ((periph_clk + (baud_rate/2U))/baud_rate);
}

void uart_set_baud_rate(USART_TypeDef* usartx,uint32_t periph_clk,uint32_t baud_rate)
{
	usartx->BRR = compute_uart_bd(periph_clk, baud_rate);
}

void uart2_write(char ch)
{
	//(1) Make sure tx data register is empty
	while(!(USART2->ISR & SR_TXE)){}
	//(1) write 8 bit to tx data register
	USART2->TDR = (ch & 0xFF);
}

void uart2_tx_init()
{
	/*Configure uart_tx gpio pin (GPIOA Pin 2)*/
	//(1) Enable GPIOA clock
	RCC->AHB2ENR |= GPIOAEN;
	//(2) set PA2 to alternate function mode
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);
	//(3) set GPIO A Pin 2 to AF07 (modify bits 8,9,10,11  value: 0111)
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	/*Configure uart module*/
	//(1) Enable uart2 clock (APB1)
	RCC->APB1ENR1 |= USART2EN;
	//(2) configure baud rate
	uart_set_baud_rate(USART2,APB1_CLK,UART_BAUDRATE);
	//(3) enable transmit
	USART2->CR1 = CR1_TE;
	//(4) enable uart
	USART2->CR1 |= CR1_UE;

}

void write_delay(char ch)
{
	uart2_write(ch);
	for(int i = 0;i<500000;++i){
	}
}
int main()
{
	uart2_tx_init();
	while(1){
		for(char i = 0; i < 26;++i){
			write_delay('A' + i);
		}
		write_delay('\n');
		write_delay('\r');
	}
}
