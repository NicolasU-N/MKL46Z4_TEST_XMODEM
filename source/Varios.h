/* Definiciones generales */
#ifndef VARIOS_H_
#define VARIOS_H_

/* Valores booleanos */
#define SI	1
#define NO	0

/* TIMERS */
#define NUM_PER		2
#define NUM_TO		0
#define NUM_PWMS	3

#define N_PER_MUX		0 // 120Hz
#define N_PER_SEND_ACK	1 //1Hz

#define N_TO_2HZ			0
//#define N_TO_LOW_INTENSITY			1
//#define N_TO_NEW_DATA				2
//#define N_TO_ACT_LOW_INTENSITY		3

#define N_PWM_S1		0
#define N_PWM_S2		1
#define N_PWM_S3		2

/* XON - XOFF*/
#define XON		0x11//0x11
#define XOFF	0x13//0x13

/* BUFFER SIZE */
#define BUFF_SIZE_RX	132//133
#define BUFF_SIZE_DIS	128//133

#endif

