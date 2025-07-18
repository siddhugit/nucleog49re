#include <stdio.h>
#include <stdint.h>
#include "stm32g491xx.h"
#include "uart.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"


#define GPIOAEN (1U<<0)
#define PIN5 (1U<<5)
#define LED_USR PIN5

void led_init()
{
	//(1) Enable clock access to GPIOA
	RCC->AHB2ENR |= GPIOAEN;

	//(2) Set PA5 as output mode
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
}

void toggle_led()
{
	GPIOA->ODR ^= (LED_USR);
}

void myext13_handler()
{
	printf("EXTI15_10_IRQHandler EXTI13 happened...\r\n");
	toggle_led();
}

void EXTI15_10_IRQHandler()
{
	printf("EXTI15_10_IRQHandler called...\r\n");
	//check LINE13 i.e. EXTI13 happened
	if((EXTI->PR1 & LINE13))
	{
		//clear PR flag
		EXTI->PR1 |= LINE13;
		//do something
		myext13_handler();
	}
}

int timestamp = 0;
int main()
{
	led_init();
	uart2_rx_tx_init();
	pc13_exti_init();
	while(1)
	{



	}
}
