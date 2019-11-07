#include <stdint.h>
#include <stdbool.h>
#include "fifo.h"

#include <stdio.h>
#include <string.h>


#define DEPTH 10

struct fifo_packet {
	uint16_t id;
	uint8_t  data[8];
	uint8_t  data_nb;
};


static struct fifo_packet fifo[DEPTH];
static int fifo_ptr_rd = 0;
static int fifo_ptr_wr = 0;


static void fifo_ptr_inc(int *index) {
	(*index)++;

	if (*index >= (2*DEPTH)) {
		*index = 0;
	}
}

bool is_empty() {
	return (fifo_ptr_rd == fifo_ptr_wr);
}

bool is_full() {
	return ((fifo_ptr_rd != fifo_ptr_wr) && ((fifo_ptr_rd%DEPTH) == (fifo_ptr_wr%DEPTH)));
}

void clear() {
	fifo_ptr_rd = 0;
	fifo_ptr_wr = 0;
}

int push(uint16_t id, uint8_t *data, uint8_t data_nb) {
	if (is_full()) {
		return 0;
	}

	int index = (fifo_ptr_wr%DEPTH);

	fifo[index].id = id;
	memmove(fifo[index].data, data, data_nb);
	fifo[index].data_nb = data_nb;

	fifo_ptr_inc(&fifo_ptr_wr);

	return 1;
}

int pop(uint16_t *id, uint8_t *data, uint8_t *data_nb) {
	if (is_empty()) {
		return 0;
	}

	int index = (fifo_ptr_rd%DEPTH);

	*id = fifo[index].id;
	*data_nb = fifo[index].data_nb;
	memmove(data, fifo[index].data, *data_nb);

	fifo_ptr_inc(&fifo_ptr_rd);

	return 1;
}
