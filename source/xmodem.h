/*
 * xmodem.h
 *
 *  Created on: 6/04/2022
 *      Author: Nicolas
 */

#ifndef XMODEM_H_
#define XMODEM_H_

#include "Tiempo.h"

#define SOH  1
#define EOT  4
#define ACK  6
#define NAK  21
#define CAN  24
//#define CTRLZ 0x1A

#define RECIBIR	1
#define VALIDAR	2
#define MOSTRAR	3
#define ERROR	4

#define ERROR_RX_TO	0
#define ERROR_TX_TO	0

void xmodem_init();

void procesar_xmoden();




#endif /* XMODEM_H_ */