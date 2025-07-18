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

#define SR_UIF (1u << 0)

#endif /* TIM_H_ */
