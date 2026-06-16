/**
 * @file usart2.c
 * @author L. Nicholson-Andrews
 * 
 * @brief
 */





#include "stm32f334x8.h"
#include "ringbuff.h"


/* Functions */
void USART2_init(void)
{
    // Tx is Pin PA2 & Rx is Pin PA3
    RCC->APB1ENR    |= RCC_APB1ENR_USART2EN;                        // Enable the USART2 Peripheral at the Reset Clock

    /* GPIO Port Mode Register */
    GPIOA->MODER    &= ~((3U << (2 * 2)) | (3U << (3 * 2)));        // Clearing Tx and Rx Bits

    // Setting Tx and Rx to Alternate Function (hands control of a GPIO pin over to an internal hardware peripheral, UART in this case)
    GPIOA->MODER    |=  ((2U << (2 * 2)) | (2U << (3 * 2)));      

    /* GPIO Alternate Function Low Register */
    GPIOA->AFR[0]   &= ~((0xFU << (2 * 4))  | (0xFU << (3 * 4))); 
    GPIOA->AFR[0]   |=  ((7U << (2 * 4))    | (7U << (3 * 4)));     // Set PA2 (Tx) and PA3 (Rx) to AF7 (USART2) in alternate function low register

    /* USART Control Register 1 */
    USART2->BRR = 69;                                               /* Set baud rate to 115200 with an 8MHz peripheral clock */

    // Enabling Transmit, Receiver, and the USART periph itself
    USART2->CR1 |= USART_CR1_RXNEIE;                /* Enables the Receiver Interrupt */
    USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE );
    USART2->CR1 |= USART_CR1_UE;

    NVIC_EnableIRQ(USART2_IRQn);                                  // Enables interrupt within NVIC
}

/* USART Tx Functions =====================================================================*/

/* Input from software */
void USART2_write(uint8_t c)
{
    status_code_t result;
    result = RingBuff_Push(&txBuff, c);
}

void USART2_string(const char* str_in)
{
    while(*str_in)
    {
        USART2_write(*str_in++);
    }
}

/* Output to Tx Register */
void USART2_print()
{
    status_code_t result;

    uint8_t c_out = 0;
    
    // Pull the character string from the array
    while(txBuff.count != 0)
    {
        while (!(USART2->ISR & USART_ISR_TXE))
        {
            /* Wait until the Transmit Data Register (TXE) empty */
        }
        /* Push the byte into the Tx Ring Buffer */
        result = RingBuff_Pop(&txBuff, &c_out);
        USART2->TDR = (uint8_t)c_out;
    }
    
}

/* USART2 Rx Functions ====================================================================*/
char USART2_read(status_code_t *result, ring_buff_t *rxBuff)
{
    // TODO: use the Rx_Ring_Buff    
    uint8_t rxByte_out = 0;
    char rx_arr[256];
    int i = 0;

    *result = RingBuff_Pop(rxBuff, &rxByte_out);
    if (*result == ERROR)
    {
        /* TODO: Add error handling and functions for such operations */
        // Default_Handler();
    }
    else if ((*result == DONE) || (*result == OVERWRITE))
    {
        while(rxByte_out != '\r')
        {
            rx_arr[i] = rxByte_out;
            i++;
        }
    }
}

/* USART IRQ Handler ==========================================================================*/
void USART2_IRQHandler()
{
    /* Rx Interrupt Service Request */
    while(USART2->ISR & USART_ISR_RXNE)      // Check that the data register is not empty and the usart interrupt is triggered
    {
        // 2. Assign the RDR value to a variable
        uint8_t r = (uint8_t)USART2->RDR;
        // 3. Read the bytes into the Rx Ring Buffer
        RingBuff_Push(&rxBuff, r); 
    } 
}
// TODO: UART / USB Serial Connection Test Function
