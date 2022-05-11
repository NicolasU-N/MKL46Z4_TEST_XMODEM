/*
 * ringBuffer.c
 *
 *  Created on: 17/03/2022
 *      Author: Nicolas
 */

#include <buffer.h>

buffer_struct* buffer_init(int32_t size) {
	buffer_struct *rb;

	rb = (buffer_struct*) malloc(sizeof(buffer_struct));
	rb->pBuf = (uint8_t*) malloc(size);

	//if (rb->pBuf == NULL) {
	//myprintf("Initialization failed\r\n");
	//return -1
	//}

	rb->count = rb->indexRead = rb->indexWrite = 0;
	rb->size = size;

	return rb;
}

char buffer_add(buffer_struct *pRb, uint8_t data) {
	/*
	 //buffer_struct *rb = pRb;
	 char ret = true;

	 pRb->pBuf[pRb->indexWrite] = data;

	 pRb->indexWrite++;
	 if (pRb->indexWrite >= pRb->size)
	 pRb->indexWrite = 0;

	 if (pRb->count < pRb->size) {
	 pRb->count++;
	 } else {
	 //si el buffer está lleno incrementa en uno indexRead
	 //haciendo que se pierda el dato más viejo y devuelve
	 //true para indicar que se estan perdiendo datos
	 pRb->indexRead++;
	 if (pRb->indexRead >= pRb->size)
	 pRb->indexRead = 0;
	 ret = false;
	 }

	 return ret;
	 */
	if (pRb->count < pRb->size) {
		pRb->pBuf[pRb->indexWrite] = data;
		(pRb->indexWrite)++;
		__disable_irq();
		(pRb->count)++;
		__enable_irq();
		if (pRb->indexWrite >= pRb->size)
			pRb->indexWrite = 0;
		return SI;
	} else {
		return NO;
	}
}

char buffer_get_data(buffer_struct *pRb, uint8_t *dp) {
	/*
	 char ret = true;

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
	 */

	if (pRb->count) {
		*dp = pRb->pBuf[pRb->indexRead];
		__disable_irq();
		--(pRb->count);
		__enable_irq();
		++(pRb->indexRead);
		if (pRb->indexRead >= pRb->size)
			pRb->indexRead = 0;
		return SI;
	} else {
		return NO;
	}
}

char buffer_peek(buffer_struct *pRb, uint8_t *dp, int32_t index) {
	if (index >= buffer_get_count(pRb)) {
		/* No items at index */
		return NO;
	} else {
		*dp = pRb->pBuf[index];
		return SI;
	}
}

int32_t buffer_get_count(buffer_struct *pRb) {
	return pRb->count;
}

/*
 char ringBuffer_isFull(buffer_struct *pRb) {
 //buffer_struct *rb = pRb;

 return pRb->count == pRb->size; //rb->size ((rb->size) * 0.75) 48
 }

 char ringBuffer_isEmpty(buffer_struct *pRb) {
 //buffer_struct *rb = pRb;

 return pRb->count == 0; //0 ((rb->size) * 0.25)
 }
 */

void buffer_reset(buffer_struct *pRb) {
	pRb->count = pRb->indexRead = pRb->indexWrite = 0;
}

void buffer_deInit(buffer_struct *pRb) {
	free(pRb);
	pRb = NULL;
}
