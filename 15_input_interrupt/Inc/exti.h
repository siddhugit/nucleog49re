/*
 * exti.h
 *
 *  Created on: Jul 17, 2025
 *      Author: ssingh
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "stm32g491xx.h"

void pc13_exti_init();
#define LINE13 (1u << 13)

#endif /* EXTI_H_ */
