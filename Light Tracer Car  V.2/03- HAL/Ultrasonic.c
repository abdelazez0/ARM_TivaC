/*
 * Ultrasonoc.c
 *
 *  Created on: Sep 9, 2023
 *      Author: HOSSAM
 */
#include"tm4c123gh6pm.h"
#include"std_types.h"
#include"bitwise_operation.h"
#include"delay.h"
#include"DIO.h"
#include"GPTM_Interface.h"
#include "Ultrasonic.h"
#include <math.h>

volatile uint32 Rise, Fall,Difference;                  /*to get rising and falling,Difference between them*/

float32 Distance,Period = 0U;

/*private function for triger the ultra sonic used in Ultasoic.c only*/
void Triger(void);


/* *************************************************
 *             Function Definition
 * ************************************************/


/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*ULTRASONIC initialization function*/
/*INPUTS: NONE*/
/*OUTPUTS: NONE*/
/*Description: Initializes the GPIO PIN C5 for trigeer  C4 For timerInput cptaure*/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
void Ultrasonic_INIT(void)
{
    DIO_init(PORTC, PIN_4, PIN_5);            /*INialize PIN4 as input for ECO and PIN5 as output for Trigerr*/
    WTimer_0_Inputcapture_INIT();             /*WIdeTImer0 INIT for input capture */
}


/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*TRIGER  function*/
/*INPUTS: NONE*/
/*OUTPUTS: NONE*/
/*Description: fUNCTION THAT GIVE PLUSE FOR 10US THEN MAKE IT LOW TO TRIGEER ULRASONIC*/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
void Triger(void)
{ /* Make the pulse for triggering the sound wave */
    DIO_WritePin(PORTC, GPIO_PIN_5, LOGIC_LOW);
    _delay_us(2);
    DIO_WritePin(PORTC, GPIO_PIN_5, LOGIC_HIGH);
    _delay_us(10);
    DIO_WritePin(PORTC, GPIO_PIN_5, LOGIC_LOW);
}


/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*GETDISTANCE  function*/
/*INPUTS: NONE*/
/*OUTPUTS: UINT32 DISTANCE*/
/*Description: fUNCTION RETURN DISTANCE MEASURE BY ULTRASONIC USING PULLING METHOD*/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
uint32 Get_Distance(void)
{
    Triger();
    while(!GET_BIT(WTIMER0_RIS_R,2));
    SET_BIT(WTIMER0_ICR_R,2);               /*clear intereput flag of capture mode*/
    Rise = WTIMER0_TAR_R;
    while(!GET_BIT(WTIMER0_RIS_R,2));
    Fall = WTIMER0_TAR_R;
    SET_BIT(WTIMER0_ICR_R,2);              /*clear intereput flag of capture mode*/
    Difference = abs(Rise - Fall);         /*to get abs diffrance*/
    Period = Difference / 16000000.0;      /*divided by clcok to get time*/
    Distance = (Period * 34000U) / 2U;     /*distance=time*speed but distance we get is whne go and return so divided it by 2*/
    return Distance;
}

