/*
 * uart_ringBuffer.h
 *
 *  Created on: 17/03/2022
 *      Author: Nicolas
 */

#ifndef UART_RING_BUFFER_H_
#define UART_RING_BUFFER_H_

#include "stdint.h"
#include <stdarg.h>
#include <math.h>

#include "Tiempo.h"
#include "ringBuffer.h"
#include "KL46z.h"
#include "Varios.h"


void clock_config();

void uart0_init(unsigned int uart0clk, unsigned int baud_rate);

void uart_send_byte(char data_input);

void uart_send_string(char *str_data);

char uart_receive_byte();

void UART0_IRQHandler();

void myprintf(char*, ...);

#endif /* UART_RING_BUFFER_H_ */
