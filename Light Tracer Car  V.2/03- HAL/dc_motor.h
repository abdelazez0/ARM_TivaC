/*
 * dc_motor.h
 *
 *  Created on: Apr 6, 2023
 *      Author: Mohamed Abdelazez
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/* *************************************************
 *            Definitions
 * ************************************************/
#define NUMBER_OF_MOTORS     4
#define MOTORS_PORT          PORTD

#define MOTOR_FR_CW_PIN      0
#define MOTOR_FR_ACW_PIN     1

#define MOTOR_FL_CW_PIN      2
#define MOTOR_FL_ACW_PIN     3

#define MOTOR_RR_CW_PIN      4
#define MOTOR_RR_ACW_PIN     5

#define MOTOR_RL_CW_PIN      6
#define MOTOR_RL_ACW_PIN     7

#define ROTATE_SPEED         70
#define FORWARD_SPEED        50
#define BACKWARD_SPEED       70
#define TURN_SPEED           70
#define STOP_SPEED           0

/* ************************************************
 *                      Enums
 * ************************************************/
typedef enum
{
	STOP, FORWARD_DIRECTION, BACKWARD_DIRECTION
}DcMotorStateType;

typedef enum
{
    FR_MOTOR = MOTOR_FR_CW_PIN , FL_MOTOR = MOTOR_FL_CW_PIN , RR_MOTOR = MOTOR_RR_CW_PIN, RL_MOTOR = MOTOR_RL_CW_PIN
}motorPositionType;

/* ***************************************************************
 *                      Function declaration
 * ***************************************************************/
void DcMotor_init(void);

void DcMotor_rotate(motorPositionType motor, DcMotorStateType state, uint8 speed);


#endif /* DC_MOTOR_H_ */
