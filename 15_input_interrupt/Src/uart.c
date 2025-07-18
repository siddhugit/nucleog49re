/*
 * uart.c
 *
 *  Created on: Jun 2, 2025
 *      Author: ssingh
 */

#include "stm32g491xx.h"
#include "uart.h"

#define USART2EN (1U<<17)
#define CR1_TE (1U<<3)
#define CR1_RE (1U<<2)
#define CR1_UE (1U<<0)
#define SR_TXE (1U<<7)
#define SR_RXE (1U<<5)

#define GPIOAEN (1U<<0)

#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define UART_BAUDRATE 115200

static uint16_t compute_uart_bd(uint32_t periph_clk,uint32_t baud_rate)
{
	return ((periph_clk + (baud_rate/2U))/baud_rate);
}

static void uart_set_baud_rate(USART_TypeDef* usartx,uint32_t periph_clk,uint32_t baud_rate)
{
	usartx->BRR = compute_uart_bd(periph_clk, baud_rate);
}

int __io_putchar(char ch)
{
	uart2_write(ch);
	return ch;
}

void uart2_write(char ch)
{
	//(1) Make sure tx data register is empty
	while(!(USART2->ISR & SR_TXE)){}
	//(2) write 8 bit to tx data register
	USART2->TDR = (ch & 0xFF);
}

char uart2_read()
{
	//(1) Make sure rx data register is ready to be read
	while(!(USART2->ISR & SR_RXE)){}
	//(2) read 8 bit to rx data register
	volatile char data = (USART2->RDR & 0xFF);
	return data;
}

void uart2_rx_tx_init()
{
	/*Configure uart_tx gpio pin (GPIOA Pin 2)*/
	//(1) Enable GPIOA clock
	RCC->AHB2ENR |= GPIOAEN;
	//(2) set PA2 to alternate function mode for tx
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);
	//(3) set PA3 to alternate function mode for rx
	GPIOA->MODER &= ~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	//(4) set GPIO A Pin 2 to AF07 (modify bits 8,9,10,11  value: 0111)
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);
	//(5) set GPIO A Pin 3 to AF07 (modify bits 12,13,14,15  value: 0111)
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);

	/*Configure uart module*/
	//(1) Enable uart2 clock (APB1)
	RCC->APB1ENR1 |= USART2EN;
	//(2) configure baud rate
	uart_set_baud_rate(USART2,APB1_CLK,UART_BAUDRATE);
	//(3) enable transmit
	USART2->CR1 = (CR1_TE | CR1_RE);
	//(4) enable uart
	USART2->CR1 |= CR1_UE;
}


