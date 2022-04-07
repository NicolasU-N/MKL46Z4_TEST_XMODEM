/*
 * showDisplay.h
 *
 *  Created on: 5/04/2022
 *      Author: Nicolas
 */

#ifndef SHOWDISPLAY_H_
#define SHOWDISPLAY_H_

#include "Varios.h"
#include "display.h"
#include "Tiempo.h"

#define NORMAL_MODE 0
#define END_DISPLAY	1

void show_data_init();

void show_data();

void set_blink_1hz();

void set_blink_2hz(); //char

void set_normal_mode();


#endif /* SHOWDISPLAY_H_ */

