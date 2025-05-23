#include <stdio.h>
#include <stdint.h>
#include "stm32g491xx.h"


#define GPIOAEN (1U<<0)
#define PIN5 (1U<<5)
#define LED_USR PIN5

int main()
{
	//(1) Enable clock access to GPIOA
	RCC->AHB2ENR |= GPIOAEN;

	//(2) Set PA5 as output mode
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);



	//(3) forever loop
	for(;;){
		//(4) toggle output register
		GPIOA->BSRR |= (LED_USR);
		//(5) cause delay
		for(int i = 0;i<1000000;++i){
		}
		GPIOA->BSRR |= (LED_USR<<16);
		for(int i = 0;i<2000000;++i){
		}
	}
}
