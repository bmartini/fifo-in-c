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



#if 0

int main(void)
{
	int x;
	clear();

	// increment wr pointer
	printf("[%d, %d]", fifo_ptr_wr, (fifo_ptr_wr%DEPTH));

	for (x = 0; x < 20; x++) {
		fifo_ptr_inc(&fifo_ptr_wr);
		printf(", [%d, %d]", fifo_ptr_wr, (fifo_ptr_wr%DEPTH));
	}
	printf("\n");


	// increment rd pointer
	printf("[%d, %d]", fifo_ptr_rd, (fifo_ptr_rd%DEPTH));
	for (x = 0; x < 20; x++) {
		fifo_ptr_inc(&fifo_ptr_rd);
		printf(", [%d, %d]", fifo_ptr_rd, (fifo_ptr_rd%DEPTH));
	}
	printf("\n");


	// increment rd & wr pointer then clear
	fifo_ptr_inc(&fifo_ptr_wr);
	fifo_ptr_inc(&fifo_ptr_wr);
	fifo_ptr_inc(&fifo_ptr_rd);
	printf("before clear: [%d, %d]\n", fifo_ptr_rd, fifo_ptr_wr);
	clear();
	printf("after clear:  [%d, %d]\n", fifo_ptr_rd, fifo_ptr_wr);


	// increment wr pointer and test empty/full
	printf("empty [%d], full [%d]\n", ((int) is_empty()), ((int) is_full()));
	fifo_ptr_inc(&fifo_ptr_wr);
	printf("empty [%d], full [%d]\n", ((int) is_empty()), ((int) is_full()));
	fifo_ptr_inc(&fifo_ptr_rd);
	printf("empty [%d], full [%d]\n", ((int) is_empty()), ((int) is_full()));

	for (x = 0; x < 20; x++) {
		fifo_ptr_inc(&fifo_ptr_wr);
		printf("empty [%d], full [%d] ", ((int) is_empty()), ((int) is_full()));
		printf("rd, wr: [%d, %d]\n", fifo_ptr_rd, fifo_ptr_wr);
	}
	printf("empty [%d], full [%d]\n", ((int) is_empty()), ((int) is_full()));
	clear();



	// test one push
	uint16_t id = 0x00FA;
	uint8_t data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	uint8_t data_nb = 4;

	printf("before push: empty [%d], full [%d]\n", ((int) is_empty()), ((int) is_full()));
	push(id, &data[0], data_nb);
	printf("after push:  empty [%d], full [%d]\n", ((int) is_empty()), ((int) is_full()));


	// test one pop
	id = 0x0000;
	memset(data, 0, sizeof(data));
	data_nb = 4;

	pop(&id, &data[0], &data_nb);
	printf("after pop:  empty [%d], full [%d]\n", ((int) is_empty()), ((int) is_full()));
	printf("pop values: id [%x], data = {%d, %d, %d, %d, %d, %d, %d, %d}, data_nb = [%d]\n"
			, id
			, data[0]
			, data[1]
			, data[2]
			, data[3]
			, data[4]
			, data[5]
			, data[6]
			, data[7]
			, data_nb
			);



	// test one push
	id = 0x00FB;
	data[0] = 1;
	data[1] = 2;
	data[2] = 3;
	data[3] = 4;
	data[4] = 5;
	data[5] = 6;
	data[6] = 7;
	data[7] = 8;
	data_nb = 8;

	printf("before push: empty [%d], full [%d]\n", ((int) is_empty()), ((int) is_full()));
	push(id, &data[0], data_nb);

	id = 0x00FC;
	data_nb = 4;
	push(id, &data[0], data_nb);
	printf("after push:  empty [%d], full [%d]\n", ((int) is_empty()), ((int) is_full()));




	// test one pop
	id = 0x0000;
	memset(data, 0, sizeof(data));
	data_nb = 8;

	pop(&id, &data[0], &data_nb);
	printf("pop 1 values: id [%x], data = {%d, %d, %d, %d, %d, %d, %d, %d}, data_nb = [%d]\n"
			, id
			, data[0]
			, data[1]
			, data[2]
			, data[3]
			, data[4]
			, data[5]
			, data[6]
			, data[7]
			, data_nb
			);

	memset(data, 0, sizeof(data));

	pop(&id, &data[0], &data_nb);
	printf("pop 2 values: id [%x], data = {%d, %d, %d, %d, %d, %d, %d, %d}, data_nb = [%d]\n"
			, id
			, data[0]
			, data[1]
			, data[2]
			, data[3]
			, data[4]
			, data[5]
			, data[6]
			, data[7]
			, data_nb
			);

	printf("after pop:  empty [%d], full [%d]\n", ((int) is_empty()), ((int) is_full()));


	return 0;
}

#endif
