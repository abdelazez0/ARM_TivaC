/* *****************************************************
 * main.c
 *
 *  Created on: Sep 9, 2023
 *      Author: Mohamed Abdelazez
 * ****************************************************/
#include "std_types.h"
#include "bitwise_operation.h"
#include "delay.h"
#include "lcd.h"
#include "dc_motor.h"
#include "Ultrasonic.h"
#include "LDR.h"
#include "internal_temp_sensor.h"
#include "Scheduler.h"
#include "push_button.h"

/* **************************************
 *              Definitions
 * **************************************/


/* ****************************************
 *           Functions Declarations
 * ****************************************/
void Task_ultrasonic(void);
void Task_LCD(void);
void Task_LDR(void);

/* ****************************************
 *           Global variables
 * ****************************************/
volatile uint32 obstacleDistance;
volatile uint16 tempInternalSensor;
volatile uint16 READ_R;
volatile uint16 READ_L;
sint16 readingDifference;
DIR_t carDirection;

/* *************************************
 *             Main Function
 * *************************************/
int main(void)

{
    /* initializations */
    pushButton_init();
    DcMotor_init();
    LCD_init();
    Ultrasonic_INIT();
    LDR_init();
    internalTempSensor_init();
    sheduler_init();

    create_task (Task_LDR, 10);          /* periodicity 10*10ms= 100ms */
    create_task (Task_ultrasonic, 60);   /* periodicity 100*10ms= 1000ms */
    create_task (Task_LCD, 100);         /* periodicity 350*10ms= 350ms */

    /*Scheduler start*/
    tasks_scheduler();

    /*infinity loop*/
    while(1)
    {
        /* won't be reached */
    }
}


/* **********************************************
 *           Functions Definitions
 * **********************************************/

/* Ultrasonic task ~0.9sec */
void Task_ultrasonic(void)
{
    obstacleDistance = Get_Distance();

    if(obstacleDistance > 99)
    {
        obstacleDistance = 99;
    }
    else if(obstacleDistance < 1)
    {
        obstacleDistance = 1;
    }
    else
    {
        /* do nothing */
    }

    if(obstacleDistance < 10)
    {
        DcMotor_rotate(FR_MOTOR, STOP , 0);
        DcMotor_rotate(FL_MOTOR, STOP , 0);

        _delay_ms(20);

        /* move backward */
        DcMotor_rotate(FR_MOTOR, BACKWARD_DIRECTION, BACKWARD_SPEED);
        DcMotor_rotate(FL_MOTOR, BACKWARD_DIRECTION, BACKWARD_SPEED);

        _delay_ms(100);

        DcMotor_rotate(FR_MOTOR, STOP , 0);
        DcMotor_rotate(FL_MOTOR, STOP , 0);

        _delay_ms(10);

        /* Rotate 90 degree */
        DcMotor_rotate(FR_MOTOR, FORWARD_DIRECTION ,  ROTATE_SPEED);
        DcMotor_rotate(FL_MOTOR, BACKWARD_DIRECTION , ROTATE_SPEED);

        _delay_ms(275);

        DcMotor_rotate(FR_MOTOR, STOP , 0);
        DcMotor_rotate(FL_MOTOR, STOP , 0);

        _delay_ms(10);

        /* continue moving forward */
        DcMotor_rotate(FR_MOTOR, FORWARD_DIRECTION , FORWARD_SPEED);
        DcMotor_rotate(FL_MOTOR, FORWARD_DIRECTION , FORWARD_SPEED);
    }
    else
    {
        /* do nothing */
    }
}

/* LCD task  0.3181s*/
void Task_LCD(void)
{
    tempInternalSensor = internalTempSensor_GetReading();

    /* display the distance read by the ultrasonic */
    LCD_displayStringRowColumn(0 , 0 , "D=");
    LCD_writeNumber(obstacleDistance / 10 , 0 , 2);
    LCD_writeNumber(obstacleDistance % 10 , 0 , 3);
    LCD_displayStringRowColumn(0 , 4 , "cm");

    /* display the temperature read by the internal temperature sensor */
    LCD_displayStringRowColumn(0 , 8 , "T=");
    LCD_writeNumber(tempInternalSensor / 10 , 0 , 11);
    LCD_writeNumber(tempInternalSensor % 10 , 0 , 12);
    LCD_displayStringRowColumn(0 , 13 , " C");

    /* display the difference of the 2 LDRs readings */
    LCD_displayStringRowColumn(1 , 0 , "LDR_DIFF=");
    LCD_writeNumber(readingDifference / 10 , 1 , 10);
}

/* LDR task 86us*/
void Task_LDR(void)
{
    LDR_rightReading();
    LDR_leftReading();
    carDirection = LDR_Compare();

    if(carDirection == RIGHT)
    {
        DcMotor_rotate(FR_MOTOR, STOP , 0);
        DcMotor_rotate(FL_MOTOR, FORWARD_DIRECTION , TURN_SPEED);
    }
    else if(carDirection == LEFT)
    {
        DcMotor_rotate(FL_MOTOR, STOP , 0);
        DcMotor_rotate(FR_MOTOR, FORWARD_DIRECTION , TURN_SPEED);
    }
    else
    {
        /* do nothing */
    }

    DcMotor_rotate(FR_MOTOR, FORWARD_DIRECTION , FORWARD_SPEED);
    DcMotor_rotate(FL_MOTOR, FORWARD_DIRECTION , FORWARD_SPEED);
}
