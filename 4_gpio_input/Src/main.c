#include <stdio.h>
#include <stdint.h>
#include "stm32g491xx.h"

//user manual says user button(blue one) is connected to PC13

#define GPIOCEN (1U<<2)
#define PIN13 (1U<<13)
#define BUTTON_USR PIN13

#define GPIOAEN (1U<<0)
#define PIN5 (1U<<5)
#define LED_USR PIN5

int main()
{
	//(1) Enable clock access to GPIOA
	RCC->AHB2ENR |= GPIOAEN;
	//(2) Enable clock access to GPIOC
	RCC->AHB2ENR |= GPIOCEN;

	//(3) Set PA5 as output mode
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	//(4) Set PC13 as input mode
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);



	//(5) forever loop
	for(;;){
		//(6) read input if button is pressed
		if(GPIOC->IDR & BUTTON_USR){
			//turn led on
			GPIOA->BSRR = (LED_USR);
		}
		else{
			//turn led off
			GPIOA->BSRR = (LED_USR << 16);
		}
	}
}
