/*
 * adc.c
 *
 *  Created on: Jun 2, 2025
 *      Author: ssingh
 */
#include "stm32g491xx.h"

#define GPIOAEN (1U<<0)
#define PIN1 (1U<<1)
#define ADC12EN (1U<<13)
#define ADC_CH2 (1U << 7)
#define ADC_CH1 (1U << 6)
#define CR_ADEN (1U<<0)
#define CR_ADSTART (1U<<2)
#define  ISR_ADRDY (1U<<0)
#define ISR_EOC (1U<<2)
//(1) Enable clock access to GPIOA
//RCC->AHB2ENR |= GPIOAEN;

//PA1 ADC12_IN2
//RCC_AHB2ENR ADC12 EN bit 13
//RCC->AHB2ENR |= ADC12EN;

//ADC_SQR1
//first and only channel = 2 ( 10 in binary)


void pa1_adc_init()
{
	//(1) Enable clock access to GPIOA
	RCC->AHB2ENR |= GPIOAEN;
	//(2)set PA1 to analog mode
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	// (3)Enable ADC12 clock
	RCC->AHB2ENR |= ADC12EN;

	/*Configure ADC parameters*/
	//(1)conversion channel start
	ADC1->SQR1 = ADC_CH2;
	//(2)conversion channel length
	ADC1->SQR1 &= ~(1U<<0);
	ADC1->SQR1 &= ~(1U<<1);
	ADC1->SQR1 &= ~(1U<<2);
	ADC1->SQR1 &= ~(1U<<3);

	//Enable ADC1
	ADC1->CR = CR_ADEN;
}

void adc1_start_conversion()
{
	ADC1->CR |= CR_ADSTART;
	ADC1->ISR |= ISR_ADRDY;
}
//EOC_SLV
uint32_t adc1_read_data()
{
	while(!(ADC1->ISR & ISR_EOC)){}
	return ADC1->DR;
}
