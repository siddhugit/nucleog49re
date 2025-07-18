/*
 * uart.h
 *
 *  Created on: Jun 2, 2025
 *      Author: ssingh
 */

#ifndef UART_H_
#define UART_H_

#include "stm32g491xx.h"

#define SR_RXE (1U<<5)

void uart2_write(char ch);
char uart2_read();
void uart2_rx_tx_init();
void uart2_rx_tx_interrupt_init();

#endif /* UART_H_ */
