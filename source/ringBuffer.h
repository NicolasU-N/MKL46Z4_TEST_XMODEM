/*
 * ringBuffer.h
 *
 *  Created on: 17/03/2022
 *      Author: Nicolas
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"

typedef struct {
	int32_t indexRead;
	int32_t indexWrite;
	int32_t count;
	int32_t size;
	uint8_t *pBuf;
} ringBuferData_struct;

/** @brief inicializa buffer circular
 **
 ** @param size tamaño del buffer
 **
 ** @return puntero a buffer circular, NULL si no se pudo crear
 **/
ringBuferData_struct* ringBuffer_init(int32_t size);

/** @brief pone nuevo dato en el buffer circular
 ** si el buffer esta lleno se pisa el dato más antiguo
 ** y se avanza el puntero de lectura
 **
 ** @param[out] pRb puntero al buffer circular
 ** @param[in] data dato a colocar en el buffer
 **
 ** @return true si se pudo poner el dato correctamente
 **         false si se puso y se piso un dato antiguo
 **/
bool ringBuffer_putData(ringBuferData_struct *pRb, char data);

/** @brief devuelve dato más antiguo del buffer
 **
 ** @param[out] pRb puntero al buffer circular
 ** @param[in] data puntero a donde guardar el dato
 **
 ** @return true si se extrajo el dato del buffer
 **         false si no había datos en el buffer
 **/
bool ringBuffer_getData(ringBuferData_struct *pRb, char *data);

bool ringBuffer_isFull(ringBuferData_struct *pRb);

bool ringBuffer_isEmpty(ringBuferData_struct *pRb);

int32_t ringBuffer_getCount(ringBuferData_struct *pRb);

/** @brief libera de memoria buffer circular
 **
 ** @param pRb puntero al buffer circular
 **
 **/
void ringBuffer_deInit(ringBuferData_struct *pRb);

#endif /* RING_BUFFER_H_ */
