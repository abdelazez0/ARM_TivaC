 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Mohamed Abdelazez
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT_ID                PORTE
#define KEYPAD_FIRST_ROW_PIN_ID           1

#define KEYPAD_COL_PORT_ID                PORTC
#define KEYPAD_FIRST_COL_PIN_ID           4
#define KEYPAD_PORT_STS_R                 GPIO_PORTC_RIS_R

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH

#define POLLING_KEYPAD

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void KEYPAD_init(void);
/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
