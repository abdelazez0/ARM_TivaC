/*
 * Systick.program.c
 *
 *  Created on: Aug 24, 2023
 *      Author: Hossam Mostafa
 */
#include"tm4c123gh6pm.h"
#include"std_types.h"
#include"bitwise_operation.h"
#include"Systick_Interfce.h"


extern uint8 CountR;
extern uint8 CountG;
extern uint8 CountB;

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*SYstick initialization function*/
/*INPUTS: NONE*/
/*OUTPUTS: NONE*/
/*Description: Initializes the SYstick module of the TIVA-C */
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/


void Systick_Init(void)
{
    NVIC_ST_CURRENT_R = 0;

    /* select clk source for systick */
#if (CLK_SRC_SEL == SYS_CLOCK)
    SET_BIT(NVIC_ST_CTRL_R, CLK_SRC);

#elif (CLK_SRC_SEL == PIOSC_4)
    CLR_BIT(NVIC_ST_CTRL_R, CLK_SRC);
#endif

    CLR_BIT(NVIC_ST_CTRL_R,Systick_Intern);             /* disable interrupts initially */
    CLR_BIT(NVIC_ST_CTRL_R,Systick_Enable);             /* disable timer initially */
}
/*function to pulling systick at givin time in ms */
void Systick_SetBusyWait(sint32 mSecs)
{
    CLR_BIT(NVIC_ST_CTRL_R,Systick_Intern);             /* disable interrupt */
    NVIC_ST_RELOAD_R = (mSecs*16*1000)-1;               /* load time into reload register */
    CLR_BIT(NVIC_ST_CTRL_R,Systick_Enable);             /* enable timer */
    while(GET_BIT(NVIC_ST_CTRL_R,Systick_count)==0);   /* poll for the count flag */
    CLR_BIT(NVIC_ST_CTRL_R,Systick_Enable);             /* disable timer */
}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*SYstick interput function*/
/*INPUTS: take no ms you wnt systick to interput on it*/
/*OUTPUTS: NONE*/
/*Description: Initializes the SYstickinterput at giving time of ms module of the TIVA-C */
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
void systick_interput(sint32 mSecs)
{
    SET_BIT(NVIC_ST_CTRL_R,Systick_Intern);             /* Enable interrupt */
    NVIC_ST_RELOAD_R = (mSecs*16*1000)-1;               /* load time into reload register */
    SET_BIT(NVIC_ST_CTRL_R,Systick_Enable);             /* Enable timer */
}
/*function to disable systick*/
void systick_disable(void)
{
    CLR_BIT(NVIC_ST_CTRL_R,Systick_Enable);             /* disable timer initially */
}




