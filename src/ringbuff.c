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


void RingBuff_init(ring_buff_t *Buff)
{
    /* Reset all values within the buffer to 0 or NULL. */
    Buff->head  = 0;
    Buff->tail  = 0;
    Buff->count = 0;
}

/**
 * @brief This function receives the byte from the UART and stores it within the Ring Buffer
 */
status_code_t RingBuff_Push(ring_buff_t *Buff, uint8_t Byte_in)
{
    status_code_t result; 
    /* Check if the ring buffer is full or has available space */ 
    if  (Buff->count == RING_BUFF)
    {
        Buff->tail = (Buff->tail + 1) % RING_BUFF;
        result = OVERWRITE;
    }
    else 
    {
        Buff->count++;
        result = DONE;
    }

    /* First write to buffer */
    Buff->buff[Buff->head] = Byte_in;
    Buff->head = (Buff->head + 1) % RING_BUFF;

    return result;
}

/**
 * @brief This function pushes the byte from the buffer to the necessary program function
 */
status_code_t RingBuff_Pop(ring_buff_t *Buff, uint8_t *Byte_out)
{
    status_code_t result;

    // 1. Read the byte from the buffer to another array
    // 2. Ensure the tail doesn't exceed the heads position
    if (Buff->count == 0)
    {
        // Return nothing since you'd be reading stale data
        result = ERROR;
    }
    else
    {
        *Byte_out         = Buff->buff[Buff->tail]; 
        Buff->tail        = (Buff->tail + 1) % RING_BUFF;
        Buff->count--;
        
        result = DONE;
    }
    return result;
}