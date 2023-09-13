/*
 * push_button.c
 *
 *  Created on: Sep 12, 2023
 *      Author: Mohamed Abdelazez
 */
#include "bitwise_operation.h"
#include "std_types.h"
#include "delay.h"
#include "DIO.h"
#include "push_button.h"

void pushButton_init(void)
{
    DIO_init(PUSH_BUTTON_PORT, PUSH_BOTTON_PIN , 0x06);
}

uint8 pushButton_startIsPressed(void)
{
    return DIO_ReadPin(PUSH_BUTTON_PORT, START_BOTTON_PIN);
}

uint8 pushButton_stopIsPressed(void)
{
    return DIO_ReadPin(PUSH_BUTTON_PORT, STOP_BOTTON_PIN);
}

