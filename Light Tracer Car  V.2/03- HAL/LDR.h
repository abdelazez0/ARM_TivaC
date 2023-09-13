/*
 * LDR.h
 *
 *  Created on: Sep 10, 2023
 *      Author: Mohamed Abdelazez
 */

#ifndef HAL_LDR_H_
#define HAL_LDR_H_

#define LDR_PORT_USED   PORTE
#define LDR_PINS_USED   0x06
#define RIGHT_LDR_PIN   1
#define LEFT_LDR_PIN    2

typedef enum {
    FWD,
    LEFT,
    RIGHT,
}DIR_t;

void LDR_init(void);

void LDR_rightReading(void);

void LDR_leftReading(void);

DIR_t LDR_Compare(void);

#endif /* HAL_LDR_H_ */
