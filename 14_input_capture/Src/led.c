/*
 * led.c
 *
 *  Created on: Jun 2, 2025
 *      Author: ssingh
 */
#include "stm32g491xx.h"

#define GPIOAEN (1U<<0)
#define PIN5 (1U<<5)
#define LED_USR PIN5

void led_usr_init()
{
	//(1) Enable clock access to GPIOA
	RCC->AHB2ENR |= GPIOAEN;

	//(2) Set PA5 as output mode
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
}

void do_led_usr_on()
{
	GPIOA->ODR |= (LED_USR);
}

void do_led_usr_off()
{
	GPIOA->ODR &= ~(LED_USR);
}


