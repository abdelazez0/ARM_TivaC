#ifndef GPTM_INTERFACE_H_
#define GPTM_INTERFACE_H_

#include "std_types.h"

void GPTM_Init(void);

void TIMER0A_Handler(void);

void GPTM_delay_sec (uint8 delay_Sec);

void GPTM_delay_millisec (uint8 delay_ms);

void WTimer_0_Inputcapture_INIT(void);

#endif
