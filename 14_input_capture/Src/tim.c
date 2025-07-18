/*
 * tim.c
 *
 *  Created on: Jul 15, 2025
 *      Author: ssingh
 */

#include "stm32g491xx.h"

#define TIM2EN (1u<<0)
#define TIM3EN (1u<<1)
#define CR1_CEN (1u<<0)
#define HZ_1 (1600 - 1)

#define OCM_0 (1u << 4)
#define OCM_1 (1u << 5)
#define OCM_2 (1u << 6)

#define CC1E (1u << 0)
#define CC1S_0 (1u << 0)
#define CC1S_1 (1u << 1)

#define AF_PA5_0 (1u <<10)
#define AF_PA5_1 (1u <<11)
#define AF_PA6_M_0 (1u <<12)
#define AF_PA6_M_1 (1u <<13)

#define AF1_PA5_0 (1u <<20)
#define AF1_PA5_1 (1u <<21)
#define AF1_PA5_2 (1u <<22)
#define AF1_PA5_3 (1u <<23)

#define AF_PA6_0 (1u <<24)
#define AF_PA6_1 (1u <<25)
#define AF_PA6_2 (1u <<26)
#define AF_PA6_3 (1u <<27)

#define GPIOAEN (1U<<0)

static void pa5_af1_init()
{
	//(1) Enable clock access to GPIOA
	RCC->AHB2ENR |= GPIOAEN;
	//set PA5 to alternate function
	GPIOA->MODER &= ~(AF_PA5_0);
	GPIOA->MODER |= (AF_PA5_1);
	//set PA5 to AF1 i.e. TIM2_CH1
	GPIOA->AFR[0] |= AF1_PA5_0;
	GPIOA->AFR[0] &= ~AF1_PA5_1;
	GPIOA->AFR[0] &= ~AF1_PA5_2;
	GPIOA->AFR[0] &= ~AF1_PA5_3;

}

static void pa6_af2_init()
{
	//(1) Enable clock access to GPIOA
	RCC->AHB2ENR |= GPIOAEN;
	//set PA6 to alternate function
	GPIOA->MODER &= ~(AF_PA6_M_0);
	GPIOA->MODER |= (AF_PA6_M_1);
	//set PA6 to AF1 i.e. TIM2_CH1
	GPIOA->AFR[0] &= ~AF_PA6_0;
	GPIOA->AFR[0] |= AF_PA6_1;
	GPIOA->AFR[0] &= ~AF_PA6_2;
	GPIOA->AFR[0] &= ~AF_PA6_3;

}

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

//timer every msecs milliseconds
void tim2_output_compare(uint32_t msecs)
{
	//Init PA5 to AF1
	pa5_af1_init();
	//Enable clock access ( TIMER2 APB1)
	RCC->APB1ENR1 |= TIM2EN;
	//set prescaler value
	TIM2->PSC = HZ_1; //16 mhz SYSCLK 16,000,000/1600 = 10000
	//set auto reload value
	uint32_t msecs_arr = 10u * msecs;
	TIM2->ARR = (msecs_arr - 1); //10000/10000 = 1 hz

	//set output compare mode
	TIM2->CCMR1 |= OCM_0;
	TIM2->CCMR1 |= OCM_1;
	TIM2->CCMR1 &= ~OCM_2;
	//Enable timer2 ch1 (PA5 i.e. led) in compare mode
	TIM2->CCER |= CC1E;
	//clear counter
	TIM2->CNT = 0;
	//Enable Timer
	TIM2->CR1 |= CR1_CEN;
}

//timer every msecs milliseconds
void tim3_intput_capture()
{
	//Init PA6 to AF2
	pa6_af2_init();
	//Enable clock access ( TIMER2 APB1)
	RCC->APB1ENR1 |= TIM3EN;
	//set prescaler value
	TIM3->PSC = HZ_1; //16 mhz SYSCLK 16,000,000/1600 = 10000
	//set ch1 to capture every edge
	TIM3->CCMR1 |= CC1S_0;
	TIM3->CCMR1 &= ~CC1S_1;
	//set ch1 to capture rising edge
	TIM3->CCER |= CC1E;
	//Enable Tim3
	TIM3->CR1 |= CR1_CEN;
}
