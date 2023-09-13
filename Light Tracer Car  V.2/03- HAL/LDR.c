/*
 * LDR.c
 *
 *  Created on: Sep 10, 2023
 *      Author: Mohamed Abdelazez
 */
#include "std_types.h"
#include "tm4c123gh6pm.h"
#include "LDR.h"
#include "delay.h"
#include "bitwise_operation.h"
#include "adc.h"
#include "DIO.h"

/* Extern variables */
extern uint16 READ_R;
extern uint16 READ_L;
extern sint16 readingDifference;


void LDR_init(void)
{
    DIO_ADCPinInit(LDR_PORT_USED , RIGHT_LDR_PIN);
    DIO_ADCPinInit(LDR_PORT_USED , LEFT_LDR_PIN);
    ADC0_initLDR();
}


void LDR_rightReading(void)
{
    READ_R = ADC0_rightLDRAnalogReading();
}

void LDR_leftReading(void)
{
    READ_L = ADC0_leftLDRAnalogReading();
}

DIR_t LDR_Compare(void)
{
    readingDifference = READ_R - READ_L;
    DIR_t ret;

    if (readingDifference <= 200 && readingDifference >= -200)
    {
        ret= FWD;
    }
    else if (readingDifference < 0)
    {
        ret= RIGHT;
    }
    else
    {
        ret = LEFT;
    }
    return ret;
}
