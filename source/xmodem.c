/*
 * xmodem.c
 *
 *  Created on: 6/04/2022
 *      Author: Nicolas
 */
#include "xmodem.h"

extern ringBuferData_struct *pRingBufferRx;
extern Tm_Control c_tiempo;

ringBuferData_struct *pRingBufferVChecksum;

char flag_eot = SI;
char flagvalidate = SI;

//char flag_timeout_0 = NO; //

//----------------- VALIDAR ERRORES ----------------------

char chrx;
char lastpakectNo = 0;		// idx del ultimo paquete recibido

char pakectNo = 0;			// idx del paquete
char lastpakectNoComp = 0;	// idx del paquete complemento a 1

char num_intentos_ACK = 0;
unsigned char countBytes = 0; 		// contador bytes recorridos del buffer
unsigned char sum_checksum;	// sumatoria modulo del paqueete
//--------------------------------------------------------

char state_xmodem = RECIBIR;

void xmodem_init() {
	Tm_Inicie_periodo(&c_tiempo, N_PER_MUX, 1); //8.333 ms
	Tm_Inicie_periodo(&c_tiempo, N_PER_SEND_ACK, 120); // 1seg
}

void procesar_xmoden() {

	//if (flag_timeout_0 != Tm_Hubo_timeout(&c_tiempo, N_TO_NEW_DATA)) {
	//	uart_send_string("TO ACK\r\n");
	//	uart_send_byte(6);
	//}
	//flag_timeout_0 = Tm_Hubo_timeout(&c_tiempo, N_TO_NEW_DATA);

	switch (state_xmodem) {
	case RECIBIR:

		if (flag_eot) { //Se termino la transmision

			if (Tm_Hubo_periodo(&c_tiempo, N_PER_SEND_ACK)
					&& ringBuffer_isEmpty(pRingBufferRx)) { // 1seg envia NAK
				uart_send_byte(NAK);
			}
			Tm_Baje_periodo(&c_tiempo, N_PER_SEND_ACK);

			if (ringBuffer_isFull(pRingBufferRx)) { //empezar a validar
				state_xmodem = VALIDAR;
				flag_eot = NO; //bandera para validar que se termino la transmision
				num_intentos_ACK = 0; //reset contador intentos ACK
			}

		} else { // No ha finalizado la transmision

			if (ringBuffer_isEmpty(pRingBufferRx)) { // si esta vacio o si el paquete no es valido //|| !flagvalidate
				if (!flag_eot && num_intentos_ACK == 10) { // Receive timeout errors
				//state_xmodem = ERROR;
					set_blink_1hz();
				} else if (!flag_eot && num_intentos_ACK == 20) {
					//state_xmodem = ERROR;
					set_blink_2hz();
				} else {
					if (Tm_Hubo_periodo(&c_tiempo, N_PER_SEND_ACK)) {

						if (!flagvalidate) {
							uart_send_byte(NAK);
						} else {
							uart_send_byte(ACK);
						}

						if (num_intentos_ACK < 22)
							num_intentos_ACK++;
					}
					Tm_Baje_periodo(&c_tiempo, N_PER_SEND_ACK);
				}
			}

			if (ringBuffer_isFull(pRingBufferRx)) { //empezar a validar
				state_xmodem = VALIDAR;
				flagvalidate = SI;
				countBytes = sum_checksum = pakectNo = lastpakectNoComp =
						lastpakectNo = num_intentos_ACK = 0;
				flag_eot = NO; //bandera para validar que se termino la transmision
				num_intentos_ACK = 0; //reset contador intentos NAK
			}
		}

		break;
	case VALIDAR:
		ringBuffer_getData(pRingBufferRx, &chrx);
		switch (countBytes) {
		case 0:
			if (chrx == 4 || chrx == 24) { // validar si el primer caracter es EOT O CAN
				state_xmodem = RECIBIR;
				uart_send_byte(ACK); // Enviar ACK y resetear banderas
				flag_eot = SI;
				flagvalidate = SI;
				countBytes = sum_checksum = pakectNo = lastpakectNoComp =
						lastpakectNo = num_intentos_ACK = 0;
			}
			break;
		case 1:
			pakectNo = chrx;
			if (pakectNo == lastpakectNo + 1) { // Validar secuencia
				pRingBufferVChecksum =  ringBuffer_init(BUFF_SIZE_DIS); // Buffer donde copiamos los datos del checksum
				lastpakectNo = pakectNo; // Actualizar pakectNo
				flagvalidate = SI;
			} else {
				flag_eot = NO;
				flagvalidate = NO;
				countBytes = sum_checksum = pakectNo = lastpakectNoComp =
						lastpakectNo = num_intentos_ACK = 0;
				ringBuffer_deInit(pRingBufferRx); //reset buffer
				pRingBufferRx = ringBuffer_init(BUFF_SIZE_RX);
				uart_send_byte(NAK); // Enviar NAK y resetear banderas
				state_xmodem = RECIBIR;
			}
			break;
		case 2:
			//validar checksum
			//Leer los datos del buffer rx,copiarlos en buffer checksum y sumar cada dato y calcular el %256 en sum_checksum con while
			//

			break;
		}

		if (++countBytes > 2 && flagvalidate) {
			//cambiar estado (copiar al buffer display) , no hay error

		} else if (++countBytes > 2 && !flagvalidate) {
			//enviar nack, hay un error
		}

		break;
	case MOSTRAR:
		//copiar buffer de rx en display

		break;
	case ERROR:

		break;
	}

}
