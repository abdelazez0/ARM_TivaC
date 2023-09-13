/*
 * push_button.h
 *
 *  Created on: Sep 12, 2023
 *      Author: Mohamed Abdelazez
 */

#ifndef HAL_PUSH_BUTTON_H_
#define HAL_PUSH_BUTTON_H_

#define PUSH_BUTTON_PORT      PORTF
#define PUSH_BOTTON_PIN       0x21
#define START_BOTTON_PIN      SW_1
#define STOP_BOTTON_PIN       SW_2

#define BUTTON_PRESSED        LOGIC_LOW
#define BUTTON_RELEASED       LOGIC_HIGH

void pushButton_init(void);

uint8 pushButton_startIsPressed(void);

uint8 pushButton_stopIsPressed(void);

#endif /* HAL_PUSH_BUTTON_H_ */
