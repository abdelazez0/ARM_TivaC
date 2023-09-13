/* ************************************************************************************
 * dc_motor.c
 *
 *  Created on: Apr 6, 2023
 *      Author: Mohamed Abdelazez
 * ************************************************************************************/
#include "dc_motor.h"
#include "DIO.h"
#include "PWM.h"

/* ***************************************************************
 *                      Function definition
 * ***************************************************************/

/* motor pins initialization */
void DcMotor_init(void)
{
    DIO_init(MOTORS_PORT , 0x00 , 0x0F);                /* initialize direction pins */

    DcMotor_rotate(FR_MOTOR, FORWARD_DIRECTION , FORWARD_SPEED);
    DcMotor_rotate(FL_MOTOR, FORWARD_DIRECTION , FORWARD_SPEED);

    PWM_INIT();
}

/* set the state of a specific motor */
void DcMotor_rotate(motorPositionType motor, DcMotorStateType state, uint8 speed)
{
    switch(state)
    {
    case FORWARD_DIRECTION:
        /* write high on cw pin and low on acw pin */
        DIO_WritePin(MOTORS_PORT , motor   , LOGIC_HIGH);
        DIO_WritePin(MOTORS_PORT , motor+1 , LOGIC_LOW);
        break;

    case BACKWARD_DIRECTION:
        /* write high on acw pin and low on cw pin */
        DIO_WritePin(MOTORS_PORT , motor   , LOGIC_LOW);
        DIO_WritePin(MOTORS_PORT , motor+1 , LOGIC_HIGH);
        break;

    case STOP:
        /* write low on cw pin and low on acw pin */
        DIO_WritePin(MOTORS_PORT , motor   , LOGIC_LOW);
        DIO_WritePin(MOTORS_PORT , motor+1 , LOGIC_LOW);
        break;
    }

    Duty_Cycle(speed);
}


