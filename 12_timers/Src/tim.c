/*
 * tim.c
 *
 *  Created on: Jul 15, 2025
 *      Author: ssingh
 */

#include "stm32g491xx.h"

#define TIM2EN (1u<<0)
#define CR1_CEN (1u<<0)
#define HZ_1 (1600 - 1)

//timer per second 1 hz = 1 second
void tim2_1hz_init()
{
	//Enable clock access ( TIMER2 APB1)
	RCC->APB1ENR1 |= TIM2EN;
	//set prescaler value
	TIM2->PSC = HZ_1; //16 mhz SYSCLK 16,000,000/1600 = 10000
	//set auto reload value
	TIM2->ARR = (10000u - 1); //10000/10000 = 1 hz
	//clear counter
	TIM2->CNT = 0;
	//Enable Timer
	TIM2->CR1 |= CR1_CEN;
}

//timer per second 1 hz = 1 second
void tim2_init(uint32_t msecs)
{
	//Enable clock access ( TIMER2 APB1)
	RCC->APB1ENR1 |= TIM2EN;
	//set prescaler value
	TIM2->PSC = HZ_1; //16 mhz SYSCLK 16,000,000/1600 = 10000
	//set auto reload value
	uint32_t msecs_arr = 10u * msecs;
	TIM2->ARR = (msecs_arr - 1); //10000/10000 = 1 hz
	//clear counter
	TIM2->CNT = 0;
	//Enable Timer
	TIM2->CR1 |= CR1_CEN;
}
