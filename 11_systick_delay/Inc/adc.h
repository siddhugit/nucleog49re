/*
 * adc.h
 *
 *  Created on: Jun 2, 2025
 *      Author: ssingh
 */

#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>

void pa1_adc_init();
void adc1_start_conversion();
uint32_t adc1_read_data();

#endif /* ADC_H_ */
