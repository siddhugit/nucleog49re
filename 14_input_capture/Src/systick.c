/*
 * systick.c
 *
 *  Created on: Jun 6, 2025
 *      Author: ssingh
 */

#include "stm32g491xx.h"

#define CYCLES_PER_MILLI_SEC 16000
#define SYSTICK_CLK_ENABLE (1U << 0)
#define SYSTICK_CLK_SOURCE (1U << 2)
#define SYSTICK_COUNT_FLAG (1U << 16)


void systick_ms_delay(int ms)
{
	//(1)Reload with number of clock cycles per millisecond
	SysTick->LOAD = CYCLES_PER_MILLI_SEC;
	//(2) Clear current value register
	SysTick->VAL = 0;
	//(3) Enable systick and select internal clock as source
	SysTick->CTRL = (SYSTICK_CLK_ENABLE | SYSTICK_CLK_SOURCE);

	for(int i = 0; i < ms; ++i)
	{
		//loop per millisecond
		while(!(SysTick->CTRL & SYSTICK_COUNT_FLAG)){}
	}

	//disable clock
	SysTick->CTRL = 0;
}


