/*
 * xmodem.c
 *
 *  Created on: 6/04/2022
 *      Author: Nicolas
 */
#include "xmodem.h"

extern Tm_Control c_tiempo;

extern ringBuferData_struct *pRingBufferRx;
extern ringBuferData_struct *pRingBufferVChecksum;
extern ringBuferData_struct *pRingBufferDisplay;

char flag_eot = SI;
char flagvalidate = SI;

//char flag_timeout_0 = NO;
//----------------- VALIDAR ERRORES ----------------------
char chrx;
char lastpakectNo = 0;		// idx del ultimo paquete recibido

char pakectNo = 0;			// idx del paquete
char lastpakectNoComp = 0;	// idx del paquete complemento a 1

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
		if (flag_eot) { //Se termino la transmision

			if (Tm_Hubo_periodo(&c_tiempo, N_PER_SEND_ACK)
					&& ringBuffer_isEmpty(pRingBufferRx)) { // 1seg envia NAK
				uart_send_byte(NAK);
			}
			Tm_Baje_periodo(&c_tiempo, N_PER_SEND_ACK);

		} else { // No ha finalizado la transmision

			if (ringBuffer_isEmpty(pRingBufferRx)) { // si esta vacio o si el paquete no es valido //|| !flagvalidate
				switch (num_intentos_ACK) {
				case 10:
					set_blink_1hz();
					break;
				case 20:
					set_blink_2hz();
					break;
				default:
					if (Tm_Hubo_periodo(&c_tiempo, N_PER_SEND_ACK)) {

						if (!flagvalidate) {
							myprintf("\r\nSE ENVIA NAK\r\n");
							uart_send_byte(NAK);
						} else {
							uart_send_byte(ACK);
						}

						if (num_intentos_ACK < 22)
							num_intentos_ACK++;
					}
					Tm_Baje_periodo(&c_tiempo, N_PER_SEND_ACK);
					break;
				}
			}
		}

		if (ringBuffer_isFull(pRingBufferRx)) { //empezar a validar
			myprintf("\r\nBF LLENO\r\n");
			state_xmodem = VALIDAR;
			flagvalidate = SI;
			countBytes = sum_checksum = pakectNo = lastpakectNoComp =
					lastpakectNo = num_intentos_ACK = 0;
			flag_eot = NO; //bandera para validar que se termino la transmision
			num_intentos_ACK = 0; //reset contador intentos NAK
		}
		break;
	case VALIDAR:
		//--------------------------------------- VALIDAR INICIO DE PAQUETE
		ringBuffer_getData(pRingBufferRx, &chrx);
		myprintf("\r\nINTO VALIDAR %d\r\n", chrx);
		if (chrx == 4 || chrx == 24) { // validar si el primer caracter es EOT O CAN
			state_xmodem = RECIBIR;
			uart_send_byte(ACK); // Enviar ACK y resetear banderas
			flag_eot = SI;
			flagvalidate = SI;
			countBytes = sum_checksum = pakectNo = lastpakectNoComp =
					lastpakectNo = num_intentos_ACK = 0;
		}
		//---------------------------------------
		//--------------------------------------- VALIDAR SECUENCIA
		ringBuffer_getData(pRingBufferRx, &pakectNo);
		myprintf("\r\nINTO VALIDAR SEC %d\r\n", chrx);
		if (pakectNo == lastpakectNo + 1) { // Validar secuencia duplicado o fuera de secuencia
			pRingBufferVChecksum = ringBuffer_init(BUFF_SIZE_DIS); // Buffer donde copiamos los datos del checksum
			lastpakectNo = pakectNo; // Actualizar pakectNo
			flag_eot = NO;
			flagvalidate = SI;
			myprintf("\r\nPAQUETE OK %d\r\n", chrx);
		} else {
			myprintf("\r\nERROR EN LA SECUENCIA %d\r\n", pakectNo);
			flag_eot = NO;
			flagvalidate = NO;
			countBytes = sum_checksum = pakectNo = lastpakectNoComp =
					lastpakectNo = num_intentos_ACK = 0;
			ringBuffer_deInit(pRingBufferRx); //reset buffer
			pRingBufferRx = ringBuffer_init(BUFF_SIZE_RX);
			uart_send_byte(NAK); // Enviar NAK y resetear banderas
			state_xmodem = RECIBIR;
		}
		//---------------------------------------
		//--------------------------------------- VALIDAR CHECKSUM
		//validar checksum
		//Leer los datos del buffer rx,copiarlos en buffer checksum y sumar cada dato y calcular el %256 en sum_checksum con while

		while (ringBuffer_getCount(pRingBufferRx) != 1) { // recorre 128 bytes
			ringBuffer_getData(pRingBufferRx, &chrx);
			ringBuffer_putData(pRingBufferVChecksum, &chrx);
			sum_checksum = sum_checksum + chrx;
		}
		//obtener checksum en chrx
		ringBuffer_getData(pRingBufferRx, &chrx);
		if (chrx != (sum_checksum % 256)) { // si no coincide el checksum
			// enviar NAK y cambiar a estado recibir
			flag_eot = NO;
			flagvalidate = NO;
			countBytes = sum_checksum = pakectNo = lastpakectNoComp =
					lastpakectNo = num_intentos_ACK = 0;
			ringBuffer_deInit(pRingBufferRx); //reset buffer
			pRingBufferRx = ringBuffer_init(BUFF_SIZE_RX);
			uart_send_byte(NAK); // Enviar NAK y resetear banderas
			state_xmodem = RECIBIR;
		} else {
			flag_eot = NO;
			flagvalidate = SI;
			//state_xmodem = MOSTRAR;
			if (ringBuffer_isEmpty(pRingBufferDisplay)) { // Se valida que el buffer del display este vacio
				while (ringBuffer_getCount(pRingBufferVChecksum) != 0) {
					ringBuffer_getData(pRingBufferVChecksum, &chrx);
					ringBuffer_putData(pRingBufferDisplay, &chrx);
				}
				state_xmodem = RECIBIR;
			}
		}
		//---------------------------------------
		/*
		 switch (countBytes) {
		 case 0:

		 break;
		 case 1:

		 break;
		 case 2:

		 break;
		 }
		 if (++countBytes > 2 && flagvalidate) {
		 //cambiar estado (copiar al buffer display) , no hay error
		 countBytes=0;
		 state_xmodem = MOSTRAR;

		 } else if (++countBytes > 2 && !flagvalidate) {
		 //enviar nack, hay un error
		 countBytes=0;
		 state_xmodem = RECIBIR;
		 }
		 */
		break;
	case MOSTRAR:
		//copiar buffer de rx en display

		//else{ // Hay datos en el buffer de display
		//}
		break;
	case ERROR:

		break;
	}

}
