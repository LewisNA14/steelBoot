





#include "stm32f334x8.h"


/* Functions */
void USART2_init()
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
    USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE );
    USART2->CR1 |= USART_CR1_UE;
}

/* USART Tx Functions =====================================================================*/
void USART2_write(char c)
{
    while(!(USART2->ISR & USART_ISR_TXE))
    {
        /* Wait until the Transmit Data Register is empty (TXE) */
    }
    USART2->TDR = (uint8_t)c;    
}

void USART2_string(const char* str)
{
    while(*str)
    {
        USART2_write(*str++);
    }
    while (!(USART2->ISR & USART_ISR_TC)) 
    {
        // Block until the final bit (stop bit) has cleared the shift register
    }
    // TODO: Implememnt the Tx Ring Buffer.
}

/* USART2 Rx Functions ====================================================================*/
char USART2_read()
{
    // TODO: use the Rx_Ring_Buff    
    uint8_t rxByte_out = 0;
    char rx_arr[256];
    int i = 0;

    stat = RxBuff_Pop();

    if (stat == ERROR)
    {
        Default_Handler();
    }
    else if (stat == DONE)
    {
        while(rxByte_out != '\r')
        {
            rx_arr[i] = rxByte_out;
            i++;
        }
    }
}

/* USART IRQ Handlers ==========================================================================*/
void USART_RX_ISR()
{

}

void USART_TX_ISR()
{

}

// TODO: UART / USB Serial Connection Test Function


/**
 * 
 * void USART2_IRQHandler()
 * {
 *      char* string; 
 *      if (USART_CR1_TXEIE)
 *      {
 *          TxBuff_Push(txByte);
 *          string = TxBuff_Pop();
 *          USART2_write("Transmit Data Register is empty!");
 *      }
 *      if (USART_CR1_RXENIE)
 *      {
 *          RxBuff_Push(rxByte);
 *      }
 */
