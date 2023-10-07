/*
 * Dio.c
 *
 *  Created on: Oct 7, 2023
 *      Author: Mohamed Abdelazez
 */
#include "Std_Types.h"
#include "bitwise_operation.h"
#include "tm4c123gh6pm.h"
#include "Dio.h"

void Dio_WriteChannel (Dio_ChannelType ChannelId, Dio_LevelType Level)
{
    uint8 port = ChannelId / 8;
    uint8 pin  = ChannelId % 8;

    if(Level == STD_HIGH)
    {
        switch(port)
        {
        case (PORTA):
                                SET_BIT(GPIO_PORTA_DATA_R,pin);
        break;
        case (PORTB):
                                SET_BIT(GPIO_PORTB_DATA_R,pin);
        break;
        case (PORTC):
                                SET_BIT(GPIO_PORTC_DATA_R,pin);
        break;
        case (PORTD):
                                SET_BIT(GPIO_PORTD_DATA_R,pin);
        break;
        case (PORTE):
                                SET_BIT(GPIO_PORTE_DATA_R,pin);
        break;
        case (PORTF):
                                SET_BIT(GPIO_PORTF_DATA_R,pin);
        break;

        default:
            break;
        }
    }
    else if(Level == STD_LOW)
    {
        switch(port)
        {
        case (PORTA):
                                CLR_BIT(GPIO_PORTA_DATA_R,pin);
        break;
        case (PORTB):
                                CLR_BIT(GPIO_PORTB_DATA_R,pin);
        break;
        case (PORTC):
                                CLR_BIT(GPIO_PORTC_DATA_R,pin);
        break;
        case (PORTD):
                                CLR_BIT(GPIO_PORTD_DATA_R,pin);
        break;
        case (PORTE):
                                CLR_BIT(GPIO_PORTE_DATA_R,pin);
        break;
        case (PORTF):
                                CLR_BIT(GPIO_PORTF_DATA_R,pin);
        break;
        default:
            break;
        }
    }
    else
    {
        /* do nothing */
    }

}

Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId)
{
    Dio_LevelType value;
    uint8 port = ChannelId / 8;
    uint8 pin  = ChannelId % 8;

    switch(port)
    {
    case (PORTA):
                                    value = GET_BIT(GPIO_PORTA_DATA_R,pin);
    break;
    case (PORTB):
                                    value = GET_BIT(GPIO_PORTB_DATA_R,pin);
    break;
    case (PORTC):
                                    value = GET_BIT(GPIO_PORTC_DATA_R,pin);
    break;
    case (PORTD):
                                    value = GET_BIT(GPIO_PORTD_DATA_R,pin);
    break;
    case (PORTE):
                                    value = GET_BIT(GPIO_PORTE_DATA_R,pin);
    break;
    case (PORTF):
                                    value = GET_BIT(GPIO_PORTF_DATA_R,pin);
    break;
    default:
        break;
    }

    return value;
}

void Dio_WritePort (Dio_PortType PortId, Dio_PortLevelType Level)
{
    switch(PortId)
    {
    case (PORTA):
                                   GPIO_PORTA_DATA_R = Level;
    break;
    case (PORTB):
                                   GPIO_PORTB_DATA_R = Level;
    break;
    case (PORTC):
                                   GPIO_PORTC_DATA_R = Level;
    break;
    case (PORTD):
                                   GPIO_PORTD_DATA_R = Level;
    break;
    case (PORTE):
                                   GPIO_PORTE_DATA_R = Level;
    break;
    case (PORTF):
                                   GPIO_PORTF_DATA_R = Level;
    break;
    default:
    break;
    }
}

Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId)
{
    Dio_PortLevelType value;

    switch(PortId)
    {
    case (PORTA):
                                value = GPIO_PORTA_DATA_R;
    break;
    case (PORTB):
                                value = GPIO_PORTB_DATA_R;
    break;
    case (PORTC):
                                value = GPIO_PORTC_DATA_R;
    break;
    case (PORTD):
                                value = GPIO_PORTD_DATA_R;
    break;
    case (PORTE):
                                value = GPIO_PORTE_DATA_R;
    break;
    case (PORTF):
                                value = GPIO_PORTF_DATA_R;
    break;
    default:
    break;
    }

    return value;
}


