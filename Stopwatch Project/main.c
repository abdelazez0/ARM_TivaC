/*
 * main.c
 *
 *  Created on: Aug 24, 2023
 *      Author: Mohamed Abdelazez
 */
#include "bitwise_operation.h"
#include "std_types.h"
#include "tm4c123gh6pm.h"
#include "systick.h"
#include "DIO.h"
#include "lcd.h"

uint8 sec_tick = 0;
uint8 min_tick = 0;

int main(void)
{
    DIO_init(PORTF, 0x11 , 0x0E);
    DIO_EnableInterrupt(PORTF, SW_1 , edge , failingLow);
    DIO_EnableInterrupt(PORTF, SW_2 , edge , failingLow);
    LCD_init();
    SYSTICK_init(systemClock);
    SYSTICK_start(16000000);
    SYSTICK_interruptState(enable);

    while(1)
    {
        LCD_writeNumber(min_tick / 10 , 0 , 0);
        LCD_writeNumber(min_tick % 10 , 0 , 1);
        LCD_moveCursor(0 , 2);
        LCD_displayCharacter(':');
        LCD_writeNumber(sec_tick / 10 , 0 , 3);
        LCD_writeNumber(sec_tick % 10 , 0 , 4);
    }
}

void ISR_PORTF_Handler(void)
{
    if(GET_BIT(GPIO_PORTF_RIS_R , SW_1))
    {
        SYSTICK_start(16000000);
        GPIO_PORTF_ICR_R |= (1 << SW_1);
    }
    else if(GET_BIT(GPIO_PORTF_RIS_R , SW_2))
    {
        SYSTICK_stop();
        GPIO_PORTF_ICR_R |= (1 << SW_2);
    }
}

void ISR_SYSTICK_Handler(void)
{
    sec_tick++;

    if(sec_tick == 60)
    {
        sec_tick = 0;
        min_tick++;
    }
}
