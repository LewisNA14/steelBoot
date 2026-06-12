/**
 * @file ringbuff.c
 * @author L. Nicholson-Andrews
 * 
 * @brief
 */

/* Includes */
#include "ringbuff.h"
#include "main.h"
#include "stm32f334x8.h"

/* Defines */


void RingBuff_init(ring_buff_t *txBuff, ring_buff_t *rxBuff)
{
    /* Reset all values within the buffer to 0 or NULL. */
    txBuff->head  = 0;
    txBuff->tail  = 0;
    txBuff->count = 0;

    rxBuff->head  = 0;
    rxBuff->tail  = 0;
    rxBuff->count = 0;
}

/**
 * @brief This function receives the byte from the UART and stores it within the Ring Buffer
 */
status_code_t RingBuff_Push(uint8_t rxByte_in)
{
    status_code_t Buff;
    
    /* First write to buffer */
    Buff->buff[Buff->head] = rxByte_in;
    Buff->head = (Buff->head + 1) % RING_BUFF;
    
    /* Check if the ring buffer is full or has available space */ 
    if  (Buff->count == RING_BUFF)
    {
        Buff->tail = (Buff->tail + 1) % RING_BUFF;
    }
    else 
    {
        Buff->count++;
    }
    return DONE;
}

/**
 * @brief This function pushes the byte from the buffer to the necessary program function
 */
status_code_t RingBuff_Pop(ring_buff_t *Buff, uint8_t *rxByte_out)
{
    status_code_t stat;
    // 1. Read the byte from the buffer to another array
    // 2. Ensure the tail doesn't exceed the heads position
    if (Buff->tail == Buff->head)
    {
        // Return nothing since you'd be reading stale data
        return ERROR;
    }
    else
    {
        *Byte_out         = Buff->buff[Buff->tail]; 
        Buff->tail        = (Buff->tail + 1) % RING_BUFF;
        Buff->count--;
    }
    return DONE;
}