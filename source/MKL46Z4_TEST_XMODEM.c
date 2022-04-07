/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    MKL46Z4_TEST_XMODEM.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "pit.h"
//#include "display.h"
#include "showDisplay.h"
#include "uart_ringBuffer.h"

//---------------BUFFER-----------------
ringBuferData_struct *pRingBufferRx;
char flag_xoff;	//1 xoff activated

char rxvalueMNS;
char ch;		// buffer character
//--------------------------------------

//-----------------LCD------------------
ringBuferData_struct *pRingBufferDisplay;
char state_display = NORMAL_MODE;
char character = '-';
//--------------------------------------

//---------------TIMER------------------
Tm_Control c_tiempo;
static Tm_Periodo periodos[NUM_PER];
static Tm_Timeout timeouts[NUM_TO];
static Tm_Pwm pwms[NUM_PWMS];

//char flag_timeout_0 = NO; //
//char flag_timeout_1 = NO; //
char flag_timeout_2 = NO; //

//char flag_timeout_3 = NO; //

static char atender_timer(char atienda);
//-------------------------------------

/*
 * @brief   Application entry point.
 */
int main(void) {

	clock_config();

	lcd_init();
	/* ============ UART0 ================ */
	uart0_init(SystemCoreClock, 2400); //115200

	pit_init_ch0(0x30D37); //0x30D37 -> 8.333ms || 0x124F7 -> 3.125ms || 0x752F-> 1.25ms || 0xB71AFF -> 500ms

	Tm_Inicio(&c_tiempo, periodos, NUM_PER, timeouts, NUM_TO, pwms, NUM_PWMS,
			&atender_timer); //, pwms, NUM_PWMS

	xmodem_init();

	show_data_init();

	//myprintf("Hello World\r\n");
	uart_send_byte(21); //NACK 21

	while (1) {

		if (atender_timer(NO)) {
			Tm_Procese(&c_tiempo);
		}

		if (Tm_Hubo_periodo(&c_tiempo, N_PER_MUX)) { // 120hz multiplexacion y sacar datos de buffer de display
			show_data();
		}
		Tm_Baje_periodo(&c_tiempo, N_PER_MUX);

		//PROCESE XMODEM
		procesar_xmoden();

		//if (ringBuffer_getCount(pRingBufferRx) != 0) {
		//	ringBuffer_getData(pRingBufferRx, &ch);
		//uart_send_string("C=");
		//uart_send_byte(ch);
		//	myprintf("C= %d\r\n", ch); //CO=%d

		/*
		 if (ch == 'a') {
		 set_blink_1hz();
		 } else if (ch == 's') {
		 set_blink_2hz();
		 } else if (ch == 'd') {
		 set_normal_mode();
		 } else if (ch == 'f') {
		 character = '-';
		 show_data();
		 state_display = END_DISPLAY;
		 } else {
		 character = ch;
		 }
		 */

		//uart_send_byte(6);
		//}
		//if (flag_timeout_2 != Tm_Hubo_timeout(&c_tiempo, N_TO_NEW_DATA)) {
		//	uart_send_string("TO ACK\r\n");
		//	uart_send_byte(6);
		//}
		//flag_timeout_2 = Tm_Hubo_timeout(&c_tiempo, N_TO_NEW_DATA);
	}
	return 0;
}

/* Rutina de verificación y atención del HW del timer */
static char atender_timer(char atienda) {
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		if (atienda)
			/* Clear interrupt flag.*/
			PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
		return SI;
	} else {
		return NO;
	}
}
