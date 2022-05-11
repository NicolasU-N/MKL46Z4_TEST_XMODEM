/*
 * show_display.c
 *
 *  Created on: 5/04/2022
 *      Author: Nicolas
 */
#include "showDisplay.h"

extern Tm_Control c_tiempo;
extern buffer_struct *pBufferDisplay;

char state_display;
uint8_t character;

extern char flag_eot;

void show_data_init() {
	// Initialize display
	display_init();
	state_display = STBY;
	Tm_Inicie_periodo(&c_tiempo, N_PER_MUX, 1); //8.333 ms = 120hz
	pBufferDisplay = buffer_init(BUFF_SIZE_DIS); // 32 64 200
}

void show_data() {
	switch (state_display) {
	case NORMAL_MODE:
		if (!buffer_is_empty(pBufferDisplay)) { // si hay datos en el buffer
			buffer_get_data(pBufferDisplay, &character);
			myprintf_uart1(" %d\r\n", character); //CO=%d
			// BAJAR PERIODO 2HZ
			// STATE NORMAL
		}
		display_scan(character);
		break;
	case STBY:
		set_display_stby();
		break;
	}
}

void set_blink_1hz() {
	show_data();
	state_display = END_DISPLAY;
	Tm_Inicie_pwm(&c_tiempo, N_PWM_S1, 120, 60, COM_1_PIN); //1 Hz 1000ms
	Tm_Inicie_pwm(&c_tiempo, N_PWM_S2, 120, 60, COM_2_PIN); //1 Hz 1000ms
	Tm_Inicie_pwm(&c_tiempo, N_PWM_S3, 120, 60, COM_3_PIN); //1 Hz 1000ms
}

void set_blink_2hz() {
	show_data();
	state_display = END_DISPLAY;
	Tm_Inicie_pwm(&c_tiempo, N_PWM_S1, 60, 30, COM_1_PIN); //1 Hz 1000ms
	Tm_Inicie_pwm(&c_tiempo, N_PWM_S2, 60, 30, COM_2_PIN); //1 Hz 1000ms
	Tm_Inicie_pwm(&c_tiempo, N_PWM_S3, 60, 30, COM_3_PIN); //1 Hz 1000ms
}

void set_normal_mode() {
	show_data();
	state_display = NORMAL_MODE;
	Tm_Inicie_pwm(&c_tiempo, N_PWM_S1, 120, 119, COM_1_PIN); //1 Hz 1000ms
	Tm_Inicie_pwm(&c_tiempo, N_PWM_S2, 120, 119, COM_2_PIN); //1 Hz 1000ms
	Tm_Inicie_pwm(&c_tiempo, N_PWM_S3, 120, 119, COM_3_PIN); //1 Hz 1000ms
}
