/*
 * systick.c
 *
 *  Created on: Aug 24, 2023
 *      Author: Mohamed Abdelazez
 */
/* count down 24 bit timer - default 16MHz*/

#include "bitwise_operation.h"
#include "std_types.h"
#include "tm4c123gh6pm.h"
#include "systick.h"


void SYSTICK_init(clockSource source)
{
    if(source == systemClock)
    {
        SET_BIT(NVIC_ST_CTRL_R , 2);
    }
    else if(source == PIOSC)
    {
        CLR_BIT(NVIC_ST_CTRL_R , 2);
    }
    else
    {
        /* Do nothing */
    }
}

void SYSTICK_interruptState(interruptState state)
{
    if(state == enable)
    {
        SET_BIT(NVIC_ST_CTRL_R , 1);
    }
    else if(state == disable)
    {
        CLR_BIT(NVIC_ST_CTRL_R , 1);
    }
    else
    {
        /* Do nothing */
    }
}

uint8 SYSTICK_readCountFlag(void)
{
    return GET_BIT(NVIC_ST_CTRL_R , 16);
}

void SYSTICK_start(uint32 preloadValue)
{
    NVIC_ST_RELOAD_R  = preloadValue - 1;
    NVIC_ST_CURRENT_R = 0;
    SET_BIT(NVIC_ST_CTRL_R , 0);
}

void SYSTICK_stop(void)
{
    CLR_BIT(NVIC_ST_CTRL_R , 0);
}

void SYSTICK_busyWait(uint16 time)
{
    SYSTICK_start(time * 16 * 1000);
    while(SYSTICK_readCountFlag() == 0);
    SYSTICK_stop();
}
