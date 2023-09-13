/*
 * NVIC.c
 *
 *  Created on: Sep 9, 2023
 *      Author: Mohamed Abdelazez
 */

#include "bitwise_operation.h"
#include "std_types.h"
#include "NVIC.h"
#include "tm4c123gh6pm.h"

void NVIC_enableInterrupt(uint8 interruptNum)
{
    interruptNum -= 16;

    if (interruptNum <= 31)
    {
        SET_BIT(NVIC_EN0_R , interruptNum);
    }
    else if (interruptNum <= 63)
    {
        interruptNum %= 32;
        SET_BIT(NVIC_EN1_R , interruptNum);
    }
    else if (interruptNum <= 95)
    {
        interruptNum %= 32;
        SET_BIT(NVIC_EN2_R , interruptNum);
    }
    else if (interruptNum <= 127)
    {
        interruptNum %= 32;
        SET_BIT(NVIC_EN3_R , interruptNum);
    }
    else if (interruptNum <= 138)
    {
        interruptNum %= 32;
        SET_BIT(NVIC_EN4_R , interruptNum);
    }
    else
    {
        /* Do nothing */
    }
}

void NVIC_disableInterrupt(uint8 interruptNum)
{
    interruptNum -= 16;

    if (interruptNum <= 31)
    {
        SET_BIT(NVIC_DIS0_R , interruptNum);
    }
    else if (interruptNum <= 63)
    {
        interruptNum %= 32;
        SET_BIT(NVIC_DIS1_R , interruptNum);
    }
    else if (interruptNum <= 95)
    {
        interruptNum %= 32;
        SET_BIT(NVIC_DIS2_R , interruptNum);
    }
    else if (interruptNum <= 127)
    {
        interruptNum %= 32;
        SET_BIT(NVIC_DIS3_R , interruptNum);
    }
    else if (interruptNum <= 138)
    {
        interruptNum %= 32;
        SET_BIT(NVIC_DIS4_R , interruptNum);
    }
    else
    {
        /* Do nothing */
    }
}
