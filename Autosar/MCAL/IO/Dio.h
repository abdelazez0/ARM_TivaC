/*
 * Dio.h
 *
 *  Created on: Oct 7, 2023
 *      Author: Mohamed Abdelazez
 */

#ifndef DIO_H_
#define DIO_H_


#define PORTA      0
#define PORTB      1
#define PORTC      2
#define PORTD      3
#define PORTE      4
#define PORTF      5

typedef uint8 Dio_ChannelType;
typedef uint8 Dio_PortType;
typedef uint8 Dio_ChannelGroupType;
typedef uint8 Dio_LevelType;
typedef uint8 Dio_PortLevelType;

void Dio_WriteChannel (Dio_ChannelType ChannelId, Dio_LevelType Level);
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId);
void Dio_WritePort (Dio_PortType PortId, Dio_PortLevelType Level);
Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId);

#endif /* DIO_H_ */
