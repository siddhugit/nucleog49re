/*
 * exti.c
 *
 *  Created on: Jul 17, 2025
 *      Author: ssingh
 */

#include "exti.h"

#define GPIOCEN (1U<<2)
#define PIN13 (1U<<13)
#define BUTTON_USR PIN13

#define SYSCFGEN (1U<<0)

#define EXTI_13_0 (1U<<4)
#define EXTI_13_1 (1U<<5)
#define EXTI_13_2 (1U<<6)
#define EXTI_13_3 (1U<<7)

#define EXTI_IMR13 (1U<<13)

void pc13_exti_init()
{
	//****disable global interrupts
	__disable_irq();
	//Enable clock access to GPIOC
	RCC->AHB2ENR |= GPIOCEN;

	//Set PC13 as input mode
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);


	//Enable clock access to SYSCFG
	//because EXTI is part of SYSCFG module
	RCC->APB2ENR |= SYSCFGEN;

	//Select PORTC for EXTI13
	SYSCFG->EXTICR[3] &= ~EXTI_13_0;
	SYSCFG->EXTICR[3] |= EXTI_13_1;
	SYSCFG->EXTICR[3] &= ~EXTI_13_2;
	SYSCFG->EXTICR[3] &= ~EXTI_13_3;


	//Unmask EXTI13
	EXTI->IMR1 |= EXTI_IMR13;

	//select falling edge trigger
	EXTI->FTSR1 |= EXTI_IMR13;

	//enable EXTI13 line in NVIC
	//this cortex m4 function
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	//****enable global interrupts
	__enable_irq();
}


