#include <stdio.h>
#include <stdint.h>
#include <string.h>


#define MAX 10

struct fifo_packet {
	uint16_t id;
	uint8_t  data[8];
	uint8_t  data_nb;
};


struct fifo_packet fifo[MAX];
int fifo_ptr_rd = 0;
int fifo_ptr_wr = 0;


void fifo_ptr_inc(int *index) {
	(*index)++;

	if (*index >= (2*MAX)) {
		*index = 0;
	}
}

int is_empty() {
	return (fifo_ptr_rd == fifo_ptr_wr);
}

int is_full() {
	return ((fifo_ptr_rd != fifo_ptr_wr) && ((fifo_ptr_rd%MAX) == (fifo_ptr_wr%MAX)));
}

void clear() {
	fifo_ptr_rd = 0;
	fifo_ptr_wr = 0;
}

int push(uint16_t id, uint8_t *data, uint8_t data_nb) {
	if (is_full()) {
		return 0;
	}

	int index = (fifo_ptr_wr%MAX);

	fifo[index].id = id;
	memcpy(fifo[index].data, data, data_nb);
	fifo[index].data_nb = data_nb;

	fifo_ptr_inc(&fifo_ptr_wr);

	return 1;
}

int pop(uint16_t *id, uint8_t *data, uint8_t *data_nb) {
	if (is_empty()) {
		return 0;
	}

	int index = (fifo_ptr_rd%MAX);

	*id = fifo[index].id;
	*data_nb = fifo[index].data_nb;
	memcpy(data, fifo[index].data, *data_nb);

	fifo_ptr_inc(&fifo_ptr_rd);

	return 1;
}




int main(void)
{
	clear();

	// increment wr pointer
	printf("[%d, %d]", fifo_ptr_wr, (fifo_ptr_wr%MAX));
	for (int x = 0; x < 20; x++) {
		fifo_ptr_inc(&fifo_ptr_wr);
		printf(", [%d, %d]", fifo_ptr_wr, (fifo_ptr_wr%MAX));
	}
	printf("\n");


	// increment rd pointer
	printf("[%d, %d]", fifo_ptr_rd, (fifo_ptr_rd%MAX));
	for (int x = 0; x < 20; x++) {
		fifo_ptr_inc(&fifo_ptr_rd);
		printf(", [%d, %d]", fifo_ptr_rd, (fifo_ptr_rd%MAX));
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
	printf("empty [%d], full [%d]\n", is_empty(), is_full());
	fifo_ptr_inc(&fifo_ptr_wr);
	printf("empty [%d], full [%d]\n", is_empty(), is_full());
	fifo_ptr_inc(&fifo_ptr_rd);
	printf("empty [%d], full [%d]\n", is_empty(), is_full());

	for (int x = 0; x < 20; x++) {
		fifo_ptr_inc(&fifo_ptr_wr);
		printf("empty [%d], full [%d] ", is_empty(), is_full());
		printf("rd, wr: [%d, %d]\n", fifo_ptr_rd, fifo_ptr_wr);
	}
	printf("empty [%d], full [%d]\n", is_empty(), is_full());
	clear();



	// test one push
	uint16_t id = 0x00FA;
	uint8_t data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	uint8_t data_nb = 4;

	printf("before push: empty [%d], full [%d]\n", is_empty(), is_full());
	push(id, &data[0], data_nb);
	printf("after push:  empty [%d], full [%d]\n", is_empty(), is_full());


	// test one pop
	id = 0x0000;
	memset(data, 0, sizeof(data));
	data_nb = 4;

	pop(&id, &data[0], &data_nb);
	printf("after pop:  empty [%d], full [%d]\n", is_empty(), is_full());
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

	printf("before push: empty [%d], full [%d]\n", is_empty(), is_full());
	push(id, &data[0], data_nb);

	id = 0x00FC;
	data_nb = 4;
	push(id, &data[0], data_nb);
	printf("after push:  empty [%d], full [%d]\n", is_empty(), is_full());




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

	printf("after pop:  empty [%d], full [%d]\n", is_empty(), is_full());


	return 0;
}
