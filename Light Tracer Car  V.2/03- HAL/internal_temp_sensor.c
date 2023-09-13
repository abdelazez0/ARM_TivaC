/*****************************************************************************
 * internal_temp_sensor.c
 *
 *  Created on: Aug 31, 2023
 *      Author: Mohamed Abdelazez
 *
 * *****************************************************************************/
#include "std_types.h"
#include "bitwise_operation.h"
#include "delay.h"
#include "DIO.h"
#include "internal_temp_sensor.h"
#include "adc.h"


void internalTempSensor_init(void)
{
    ADC0_initTempSensor();
}


uint16 internalTempSensor_GetReading(void)
{
    uint16 TempValueC;
    uint16 analogReading;

    analogReading = ADC0_TempSensorAnalogReading();
    TempValueC    = 147.5 - ((75 * 3.3 * analogReading) / 4096);  /* calculate temperature in C */
    _delay_ms(100);                                               /* delay on the example */

    return TempValueC;
}


