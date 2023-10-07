/*
 * Port.c
 *
 *  Created on: Oct 7, 2023
 *      Author: Mohamed Abdelazez
 */
#include "Std_Types.h"
#include "bitwise_operation.h"
#include "tm4c123gh6pm.h"
#include "Port.h"

void Port_Init (const Port_ConfigType* ConfigPtr)
{
    SET_BIT(SYSCTL_RCGCGPIO_R,PORTF);                   /* Activate PORT clock */
    while(GET_BIT(SYSCTL_RCGCGPIO_R,PORTF) == 0);       /* Check if PORT clock is activated */
    GPIO_PORTF_LOCK_R = 0x4C4F434B;                     /* Unlock PORTF pins */
    GPIO_PORTF_DIR_R = 0x0E;                            /* set output pins direction */
    GPIO_PORTF_CR_R = 0x0E;;                            /* Enable changes on PORTF used pins */
    GPIO_PORTF_DEN_R = 0x0E;                            /* Digital Enable PORTF used pins */
}

void Port_SetPinDirection (Port_PinType Pin, Port_PinDirectionType Direction)
{

}

void Port_SetPinMode (Port_PinType Pin, Port_PinModeType Mode)
{

}
