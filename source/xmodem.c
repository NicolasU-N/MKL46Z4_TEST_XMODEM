/*
 * xmodem.c
 *
 *  Created on: 6/04/2022
 *      Author: Nicolas
 */
#include "xmodem.h"

extern Tm_Control c_tiempo;

extern buffer_struct *pBufferRx;
extern buffer_struct *pBufferDisplay;

extern char state_display;
//extern uint8_t txbuff[];

//----------------- VALIDAR ERRORES ----------------------
char flag_eot = SI;
char flagvalidate = SI;

uint8_t chrx;
uint8_t lastpakectNo = 0;		// idx del ultimo paquete recibido

uint8_t pakectNo = 0;			// idx del paquete
uint8_t lastpakectNoComp = 0;	// idx del paquete complemento a 1

char num_intentos_ACK = 0;
unsigned char countBytes = 0;	// contador bytes recorridos del buffer
unsigned char sum_checksum;		// sumatoria modulo del paqueete
//--------------------------------------------------------

char state_xmodem = RECIBIR;

void xmodem_init() {
	Tm_Inicie_periodo(&c_tiempo, N_PER_MUX, 1); //8.333 ms
	Tm_Inicie_periodo(&c_tiempo, N_PER_SEND_ACK, 120); // 1seg
}

void procesar_xmoden() {
	switch (state_xmodem) {
	case RECIBIR:

		if (buffer_is_empty(pBufferRx)) {
			if (Tm_Hubo_periodo(&c_tiempo, N_PER_SEND_ACK)) { // 1seg envia NAK o ACK
				Tm_Baje_periodo(&c_tiempo, N_PER_SEND_ACK);
				if (flag_eot) { //Se termino la transmision
					uart_send_byte(NAK);

				} else { // No ha finalizado la transmision

					switch (num_intentos_ACK) {
					case 2:
						state_display=END_DISPLAY;
						set_blink_1hz();
						myprintf_uart1("BLINK1-%d\r\n", num_intentos_ACK);
						//Tm_Inicie_timeout(&c_tiempo, N_TO_2HZ, 2400); //20 SEG //iniciar to
						break;
					case 20:
						state_display=END_DISPLAY;
						set_blink_2hz();
						myprintf_uart1("BLINK2-%d\r\n", num_intentos_ACK);
						break;
					}

					if (!flagvalidate) {
						uart_send_byte(NAK);
					} else {
						myprintf_uart1("ACK %d\r\n", num_intentos_ACK);
						//set_normal_mode();
						uart_send_byte(ACK);

					}

					if (num_intentos_ACK < 22)
						num_intentos_ACK++;

				}
			}
		}

		//if (buffer_get_count(pBufferRx) >= 150) { //empezar a validar
		if (buffer_is_full(pBufferRx)) {
			/* DEBUG BUFFER
			 uart_send_byte(CAN);
			 uart_send_byte(CAN);
			 uart_send_byte(CAN);
			 uart_send_byte(CAN);

			 myprintf("\r\n");

			 while (buffer_get_data(pBufferRx, &chrx)) //&& pBufferRx->count >= 1
			 {
			 //uart_send_byte(&chtx, 1);
			 //PRINTF("%d\r\n", chtx);
			 myprintf(" %d\r\n", chrx);
			 }
			 */
			//txbuff = "BUFF FULL\r\n";
			//UART_WriteBlocking(DEMO_UART, txbuff, sizeof(txbuff) - 1);
			//uint8_t *txbf = (uint8_t*) "BF FULL\r\n";
			//UART_WriteBlocking(DEMO_UART, txbf, strlen((char*) txbf));
			//-------
			/*
			 myprintf_uart1("BF FULL %d\r\n", pakectNo);
			 */
//------------------- degub display
			state_display = NORMAL_MODE;
			//myprintf("BF FULL\r\n");

			state_xmodem = VALIDAR;
			flagvalidate = SI;
			//reset contador intentos NAK
			sum_checksum = num_intentos_ACK = 0;//pakectNo = lastpakectNo = lastpakectNoComp
			flag_eot = NO; //bandera para validar que se termino la transmision
		} else {
			//Si no esta lleno valide que el primer caracter sea un EOT sino es un paquete incompleto
			if (buffer_is_empty(pBufferDisplay)) {
				buffer_peek(pBufferRx, &chrx, 0);
				//PRINTF("\r\nVALIDAR %d\r\n", chrx);
				//myprintf("\r\nVALIDAR %d\r\n", chrx);
				//myprintf_uart1("\r\n %d\r\n", chrx);

				if (chrx == 4 || chrx == 24) { // validar si el primer caracter es EOT O CAN
					myprintf_uart1("EOT %d\r\n", chrx);
					uart_send_byte(ACK);
					//uart_send_byte(ACK);
					//uart_send_byte(ACK);
					buffer_reset(pBufferRx);			//reset buffer
					chrx = 0;
					state_xmodem = RECIBIR;

					state_display = STBY;

					flag_eot = SI;
					flagvalidate = SI;
					sum_checksum = pakectNo = lastpakectNoComp = lastpakectNo =
							num_intentos_ACK = 0;
					//break;
				}

			}

		}

		break;
	case VALIDAR:
		//--------------------------------------- VALIDAR INICIO DE PAQUETE
		/*
		 buffer_peek(pBufferRx, &chrx, 0);
		 //PRINTF("\r\nVALIDAR %d\r\n", chrx);
		 //myprintf("\r\nVALIDAR %d\r\n", chrx);
		 myprintf_uart1("\r\nVALIDAR %d\r\n", chrx);

		 if (chrx == 4 || chrx == 24) { // validar si el primer caracter es EOT O CAN
		 myprintf_uart1("\r\nEOT%d\r\n", chrx);
		 uart_send_byte(ACK);
		 uart_send_byte(ACK);
		 uart_send_byte(ACK);
		 state_xmodem = RECIBIR;
		 state_display = STBY;
		 flag_eot = SI;
		 flagvalidate = SI;
		 sum_checksum = pakectNo = lastpakectNoComp = lastpakectNo =
		 num_intentos_ACK = 0;
		 break;
		 }
		 */

		//---------------------------------------
		//--------------------------------------- VALIDAR SECUENCIA
		buffer_peek(pBufferRx, &pakectNo, 1);
		buffer_peek(pBufferRx, &lastpakectNoComp, 2);

		/*
		 myprintf_uart1("\r\nVAL PKTN %d - ", pakectNo);
		 myprintf_uart1("VAL LPKTN %d\r\n", lastpakectNoComp);
		 */

		if ((pakectNo == lastpakectNo + 1)
				&& (lastpakectNoComp == 255 - pakectNo)) { // en secuencia Y valida complemento

			lastpakectNo = pakectNo; // Actualizar pakectNo
			flag_eot = NO;
			flagvalidate = SI;
			//myprintf("\r\nPAQUETE OK %d\r\n", chrx);
			//PRINTF("\r\nPAQUETE OK %d\r\n", chrx);

		} else if (pakectNo == lastpakectNo) { //Validar duplicado
			lastpakectNo = pakectNo; // Actualizar pakectNo
			flag_eot = NO;
			flagvalidate = SI; //ENVIAR ACK
			buffer_reset(pBufferRx);			//reset buffer
			//CAMBIAR ESTADO
			state_xmodem = RECIBIR;
			break;

			//myprintf("\r\nPAQUETE REPETIDO %d\r\n", chrx);
		} else { //fuera de secuencia

			//myprintf("\r\nERROR PCK=%d COMP=%d\r\n", pakectNo,
			//		lastpakectNoComp);
			flag_eot = NO;
			flagvalidate = NO;
			//num_intentos_ACK++;
			sum_checksum = pakectNo = 0;

			buffer_reset(pBufferRx);			//reset buffer
			//uart_send_byte(NAK); // Enviar NAK y resetear banderas
			state_xmodem = RECIBIR;
			break;
		}
		//---------------------------------------
		//--------------------------------------- VALIDAR CHECKSUM
		//validar checksum
		//Leer los datos del buffer rx,copiarlos en buffer checksum y sumar cada dato y calcular el %256 en sum_checksum con while

		chrx = 0;
		for (int i = 3; i < BUFF_SIZE_RX - 1; i++) {
			buffer_peek(pBufferRx, &chrx, i);
			sum_checksum += chrx; // sumatoria
		}

		//obtener checksum en chrx
		buffer_peek(pBufferRx, &chrx, BUFF_SIZE_RX - 1);
		if (chrx == sum_checksum % 256) { // Si coincide el checksum

		//myprintf("SCHEK = %d CHS = %d\r\n", sum_checksum,sum_checksum % 256);
		//PRINTF("SCHEK = %d CHS = %d\r\n", sum_checksum, sum_checksum % 256);

			/*
			 myprintf_uart1("SCHEK=%d CHS=%d\r\n", sum_checksum,
			 sum_checksum % 256);
			 */

			flag_eot = NO;
			flagvalidate = SI;
			state_xmodem = MOSTRAR;
			buffer_get_data(pBufferRx, &chrx);
			buffer_get_data(pBufferRx, &chrx);
			buffer_get_data(pBufferRx, &chrx); // Omitir header del paquete
		} else {
			//myprintf("\r\nERR CSP=%d CSC=%d\r\n", chrx, sum_checksum % 256);
			flag_eot = NO;
			flagvalidate = NO;
			buffer_reset(pBufferRx);		//reset buffer
			sum_checksum = pakectNo = chrx = 0;
			// Enviar NAK, resetear banderas y cambiar a estado recibir
			state_xmodem = RECIBIR;
			//break;
		}

		break;
	case MOSTRAR:
		//copiar buffer de rx en display

		if (buffer_available(pBufferDisplay)) { // hay espacio disponible en el buffer del display
			// copiar al buffer del display
			if (buffer_get_data(pBufferRx, &chrx)
					&& buffer_get_count(pBufferRx) >= 1) {
				//myprintf_uart1("CRX=%d-", chrx);
				buffer_add(pBufferDisplay, chrx);
			} else {
				//myprintf_uart1("BFRXFREE\r\n");
				buffer_reset(pBufferRx);			//reset buffer
				sum_checksum = num_intentos_ACK = 0; //pakectNo =
				state_xmodem = RECIBIR;
				flag_eot = NO;
				flagvalidate = SI;
			}
		}

		break;
		//case ERROR:

		//	break;
	}

}
