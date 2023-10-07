/*
 * Port.h
 *
 *  Created on: Oct 7, 2023
 *      Author: Mohamed Abdelazez
 */

#ifndef PORT_H_
#define PORT_H_


#define PORTA      0
#define PORTB      1
#define PORTC      2
#define PORTD      3
#define PORTE      4
#define PORTF      5

typedef uint8 Port_PinType;
typedef uint8 Port_PinModeType;

typedef enum {
    PORT_PIN_IN = 0x00, PORT_PIN_OUT = 0x01
}Port_PinDirectionType;

typedef struct {

}Port_ConfigType;

void Port_Init (const Port_ConfigType* ConfigPtr);
void Port_SetPinDirection (Port_PinType Pin, Port_PinDirectionType Direction);
void Port_SetPinMode (Port_PinType Pin, Port_PinModeType Mode);

#endif /* PORT_H_ */
