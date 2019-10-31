#ifndef FIFO_H
#define FIFO_H

#ifdef __cplusplus
extern "C" {
#endif


void clear();

bool is_empty();

bool is_full();

int push(uint16_t id, uint8_t *data, uint8_t data_nb);

int pop(uint16_t *id, uint8_t *data, uint8_t *data_nb);



#ifdef __cplusplus
}
#endif
#endif	/* FIFO_H */
