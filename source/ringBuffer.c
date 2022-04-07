/*
 * ringBuffer.c
 *
 *  Created on: 17/03/2022
 *      Author: Nicolas
 */

#include "ringBuffer.h"

ringBuferData_struct* ringBuffer_init(int32_t size) {
	ringBuferData_struct *rb;

	rb = malloc(sizeof(ringBuferData_struct));
	rb->pBuf = malloc(size);

	if (rb->pBuf == NULL) {
		//myprintf("Initialization failed\r\n");
		//return -1
	}

	rb->indexRead = 0;
	rb->indexWrite = 0;
	rb->count = 0;
	rb->size = size;

	return rb;
}

bool ringBuffer_putData(ringBuferData_struct *pRb, char data) {
	//ringBuferData_struct *rb = pRb;
	bool ret = true;

	pRb->pBuf[pRb->indexWrite] = data;

	pRb->indexWrite++;
	if (pRb->indexWrite >= pRb->size)
		pRb->indexWrite = 0;

	if (pRb->count < pRb->size) {
		pRb->count++;
	} else {
		/* si el buffer está lleno incrementa en uno indexRead
		 * haciendo que se pierda el dato más viejo y devuelve
		 * true para indicar que se estan perdiendo datos */
		pRb->indexRead++;
		if (pRb->indexRead >= pRb->size)
			pRb->indexRead = 0;
		ret = false;
	}

	return ret;
}

bool ringBuffer_getData(ringBuferData_struct *pRb, char *data) {
	//ringBuferData_struct *rb = pRb;
	bool ret = true;

	if (pRb->count) {
		*data = pRb->pBuf[pRb->indexRead];

		pRb->indexRead++;
		if (pRb->indexRead >= pRb->size)
			pRb->indexRead = 0;
		pRb->count--;
	} else {
		ret = false;
	}

	return ret;
}

bool ringBuffer_isFull(ringBuferData_struct *pRb) {
	//ringBuferData_struct *rb = pRb;

	return pRb->count == pRb->size; //rb->size ((rb->size) * 0.75) 48
}

bool ringBuffer_isEmpty(ringBuferData_struct *pRb) {
	//ringBuferData_struct *rb = pRb;

	return pRb->count == 0; //0 ((rb->size) * 0.25)
}

int32_t ringBuffer_getCount(ringBuferData_struct *pRb) {
	//ringBuferData_struct *rb = pRb;
	return pRb->count;
}

void ringBuffer_deInit(ringBuferData_struct *prb) {
	free(pRb);
	pRb = NULL;
}
