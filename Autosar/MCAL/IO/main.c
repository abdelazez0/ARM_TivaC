/*
 * main.c
 *
 *  Created on: Oct 7, 2023
 *      Author: Mohamed Abdelazez
 */
#include "Std_Types.h"
#include "Dio.h"
#include "Port.h"
#include "delay.h"

int main(void)
{
    Port_Init(NULL_PTR);

    while(1)
    {
        Dio_WriteChannel(41, STD_HIGH);
        _delay_ms(100);
        Dio_WriteChannel(42, STD_HIGH);
        _delay_ms(100);
        Dio_WriteChannel(43, STD_HIGH);
        _delay_ms(100);
        Dio_WriteChannel(41, STD_LOW);
        _delay_ms(100);
        Dio_WriteChannel(42, STD_LOW);
        _delay_ms(100);
        Dio_WriteChannel(43, STD_LOW);
        _delay_ms(100);
    }
}

