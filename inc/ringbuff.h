/**
 * @file ringbuff.h
 * @author L. Nicholson-Andrews
 * 
 * @brief Holds the interfaces for the Ring Buffer
*/
#ifndef RINGBUFF_H
#define RINGBUFF_H

/* Includes */

/* Standard Library */
#include <stdlib.h>
#include <stdint.h>


#include "main.h"

/* Defines */
#define RING_BUFF 256

/* Type Defines */
typedef struct ring_buff_s{
    uint8_t buff[RING_BUFF];
    int head;
    int tail;
    int count;
}ring_buff_t;

/* Declarations */
extern ring_buff_t txBuff;
extern ring_buff_t rxBuff;

/* Function Prototypes */
void RingBuff_init(ring_buff_t *Buff);

status_code_t RingBuff_Push(ring_buff_t *Buff, uint8_t Byte_in);
status_code_t RingBuff_Pop(ring_buff_t *Buff, uint8_t *Byte_out);

#endif // RINGBUFF_H