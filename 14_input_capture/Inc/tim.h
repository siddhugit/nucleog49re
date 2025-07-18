/*
 * tim.h
 *
 *  Created on: Jul 15, 2025
 *      Author: ssingh
 */

#ifndef TIM_H_
#define TIM_H_

void tim2_1hz_init();
void tim2_init(uint32_t msecs);
void tim2_output_compare(uint32_t msecs);
void tim3_intput_capture();

#define SR_UIF (1u << 0)
#define SR_CCIF (1u << 1)

#endif /* TIM_H_ */
