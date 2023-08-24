/*
 * systick.h
 *
 *  Created on: Aug 24, 2023
 *      Author: Mohamed Abdelazez
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "std_types.h"

typedef enum {
    systemClock , PIOSC
}clockSource;

typedef enum {
    disable , enable
}interruptState;

void SYSTICK_init(clockSource source);

void SYSTICK_interruptState(interruptState state);

uint8 SYSTICK_readCountFlag(void);

void SYSTICK_start(uint32 preloadValue);

void SYSTICK_busyWait(uint16 time);

void SYSTICK_stop(void);

#endif /* SYSTICK_H_ */
