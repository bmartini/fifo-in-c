#include <stdint.h>
#include <stdbool.h>
#include "fifo.h"

#include <stdio.h>
#include <string.h>



int main(void)
{
	clear();


	// test one push
	uint16_t id = 0x00FA;
	uint8_t data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	uint8_t data_nb = 4;

	printf("before push: empty [%d], full [%d]\n", ((int) is_empty()), ((int) is_full()));
	if (push(id, &data[0], data_nb) == 0) {
		printf("ERROR: push failed\n");
	}
	printf("after push:  empty [%d], full [%d]\n", ((int) is_empty()), ((int) is_full()));


	// test one pop
	id = 0x0000;
	memset(data, 0, sizeof(data));
	data_nb = 4;

	if (pop(&id, &data[0], &data_nb) == 0) {
		printf("ERROR: pop failed\n");
	}
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
	if (push(id, &data[0], data_nb) == 0) {
		printf("ERROR: push failed\n");
	}

	id = 0x00FC;
	data_nb = 4;
	if (push(id, &data[0], data_nb) == 0) {
		printf("ERROR: push failed\n");
	}
	printf("after push:  empty [%d], full [%d]\n", ((int) is_empty()), ((int) is_full()));




	// test one pop
	id = 0x0000;
	memset(data, 0, sizeof(data));
	data_nb = 8;

	if (pop(&id, &data[0], &data_nb) == 0) {
		printf("ERROR: pop failed\n");
	}
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

	if (pop(&id, &data[0], &data_nb) == 0) {
		printf("ERROR: pop failed\n");
	}
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
