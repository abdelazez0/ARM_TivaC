/*
 * NVIC.h
 *
 *  Created on: Sep 9, 2023
 *      Author: Mohamed Abdelazez
 */

#ifndef MCAL_NVIC_H_
#define MCAL_NVIC_H_

#include "std_types.h"

void NVIC_enableInterrupt(uint8 interruptNum);

void NVIC_disableInterrupt(uint8 interruptNum);

#endif /* MCAL_NVIC_H_ */
