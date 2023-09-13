/*
 * Schedular.c
 *
 *  Created on: Sep 10, 2023
 *      Author: eme
 */


#include "Scheduler.h"
#include "push_button.h"
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "Systick_Interfce.h"
#include "std_types.h"
#include "DIO.h"

uint16 Priority =0;
uint8 CountR=0;
uint8 CountG=0;
uint8 CountB=0;
uint8 flagR=0;
uint8 flagG=0;
uint8 flagB=0;
uint8 OFF=0;
uint8 off_flag=0;


// Define the base addresses of the timers
#define TIMER0_BASE 0x40030000  // Replace with the actual base address for Timer0
#define TIMER1_BASE 0x40031000  // Replace with the actual base address for Timer1

// Timer0 registers (example)
volatile uint32 *TIMER0_CTL = (uint32 *)(TIMER0_BASE + 0x00);
volatile uint32 *TIMER0_TAILR = (uint32 *)(TIMER0_BASE + 0x28);
volatile uint32 *TIMER0_ICR = (uint32 *)(TIMER0_BASE + 0x24);

// Timer1 registers (example)
volatile uint32 *TIMER1_CTL = (uint32 *)(TIMER1_BASE + 0x00);
volatile uint32 *TIMER1_TAILR = (uint32 *)(TIMER1_BASE + 0x28);
volatile uint32 *TIMER1_ICR = (uint32 *)(TIMER1_BASE + 0x24);

void sheduler_init(void)
{
    Systick_Init();
    systick_interput(10);
}


void create_task (void (*TaskFunction)(), uint32 periodicity ) {
    TASKS[Priority].Periodicity = periodicity;
    TASKS[Priority].TaskFunction = TaskFunction;
    Priority++;
}

void tasks_scheduler(void) {
    // Loop through tasks
    //uint32_t i;
    while (1)
    { /*if start button is pressed  it inilaize systick*/
        if(pushButton_startIsPressed() == BUTTON_PRESSED)
        {
            Systick_Init();
            systick_interput(10);
        }
        /*if stop button is pressed  it disable systick*/
        else if(pushButton_stopIsPressed() == BUTTON_PRESSED)
        {
            CLR_BIT(NVIC_ST_CTRL_R,Systick_Enable); ;
        }
        else
        {

        }

        if (flagR)
        {
            TASKS[0].TaskFunction();
            CountR=0;
            flagR=0;
        }
        if (flagG)
        {
            TASKS[1].TaskFunction();
            CountG=0;
            flagG=0;
        }
        if (flagB)
        {
            TASKS[2].TaskFunction();
            CountB=0;
            flagB=0;
        }
        if (off_flag)
        {
            systick_disable();
        }


    }
}

void Systick_Handler (void)
{
    CountR++;
    CountG++;
    CountB++;
    OFF++;
    if (CountR >=TASKS[0].Periodicity)
        flagR=1;
    if (CountG >=TASKS[1].Periodicity)
        flagG=1;
    if (CountB >=TASKS[2].Periodicity)
        flagB=1;
    /*if it become 1 min it make off flag that disable systick*/
    if(OFF >= 6000)
    {
        off_flag = 1;
    }
}
