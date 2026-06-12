/**
 * @file ringbuff.h
 * @author L. Nicholson-Andrews
 * 
 * @brief Holds the interfaces for the Ring Buffer
*/
#ifndef RINGBUFF_H
#define RINGBUFF_H

/* Includes */
#include <stdlib.h>
#include <stdint.h>

/* Defines */
#define RING_BUFF 256

/* Type Defines */
typedef struct ring_buff_s{
    uint8_t buff[RING_BUFF];
    int head;
    int tail;
    int count;
}ring_buff_t;

/* Function Prototypes */
void RingBuff_init(ring_buff_t *txBuff, ring_buff_t *rxBuff);

void RingBuff_Push();
void RingBuff_Pop();

#endif // RINGBUFF_H