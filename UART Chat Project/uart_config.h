/*
 * uart_config.h
 *
 *  Created on: Sep 2, 2023
 *      Author: Mohamed Abdelazez
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#define TIVA_UART           UART3_BASE
#define TERMINAL_UART       UART0_BASE

void UART_init(void);

void UART_initTerminal(void);

void UART_sendString(const uint8_t *Str, uint32_t uartUsed);

void UART_receiveString(uint8_t *Str, uint32_t uartUsed);


#endif /* UART_CONFIG_H_ */
