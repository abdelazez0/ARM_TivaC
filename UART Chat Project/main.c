/*
 * main.c
 *
 *  Created on: Sep 2, 2023
 *      Author: Mohamed Abdelazez
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "uart_config.h"

#define ARRAY_SIZE   200
#define RECEIVER_ECU

/* Main function */
int main(void)
{
    uint8_t dataString[ARRAY_SIZE];

    UART_init();
    UART_initTerminal();

#ifdef SENDER_ECU
    UART_sendString("Start Typing ...#" , TERMINAL_UART);
    UARTCharPut(TERMINAL_UART , '\r');
    UARTCharPut(TERMINAL_UART , '\n');
#endif

#ifdef RECEIVER_ECU
    UART_sendString("Waiting for message ...#" , TERMINAL_UART);
    UARTCharPut(TERMINAL_UART , '\r');
    UARTCharPut(TERMINAL_UART , '\n');
#endif

    /* infinity loop */
    while(1)
    {

#ifdef SENDER_ECU
        UART_receiveString(dataString, TERMINAL_UART);
        UARTCharPut(TERMINAL_UART , '\r');
        UARTCharPut(TERMINAL_UART , '\n');
        UART_sendString(dataString, TIVA_UART);

        UART_receiveString(dataString, TIVA_UART);
        UART_sendString(dataString, TERMINAL_UART);
        UARTCharPut(TERMINAL_UART , '\r');
        UARTCharPut(TERMINAL_UART , '\n');
#endif

#ifdef RECEIVER_ECU
        UART_receiveString(dataString, TIVA_UART);
        UART_sendString(dataString, TERMINAL_UART);
        UARTCharPut(TERMINAL_UART , '\r');
        UARTCharPut(TERMINAL_UART , '\n');

        UART_receiveString(dataString, TERMINAL_UART);
        UARTCharPut(TERMINAL_UART , '\r');
        UARTCharPut(TERMINAL_UART , '\n');
        UART_sendString(dataString, TIVA_UART);
#endif
    }
}

