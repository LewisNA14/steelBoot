/**
 * @file    main.c
 * @brief   This is where the main logic of the program is held
 * 
 */

/* Includes ==============================================================================*/ 
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stm32f334x8.h"

/* Defines ===============================================================================*/
#define RING_BUFF 128



/* Global Variables ======================================================================*/
volatile uint32_t g_tick_count = 0;


/* Function Prototypes ===================================================================*/
void gpio_set();

void LED2_init();
void LED2_update();

void RingBuff_init(Tx_ring_buff_t *txBuff, Rx_ring_buff_t *rxBuff);

void RxBuff_Check();
void RxBuff_Push();
void RxBuff_Pop();

void TxBuff_Check();
void TxBuff_Push();
void TxBuff_Pop();

void USART2_init();
void USART2_write(char c);
void USART2_string(const char* str);
void USART2_read();

void TIM2_init();
void TIM2_IRQHandler();

/* Defined Types =========================================================================*/
typedef enum led2_status_e{
    ON,
    OFF,
    LED2_ENUM_END
} led2_status_t;

/* typedef enum usart2_status_e{
    CLOSED,
    RX,
    TX,
    DONE,
    USART2_END
} usart2_status_t; */

typedef enum status_codes_e{
    DONE,       // 0
    BUSY,       // 1
    ERROR       // 2
}status_codes_t;

/* Defined Structs ======================================================================*/
typedef struct ring_buff_s{
    uint8_t buff[RING_BUFF]
    int head;
    int tail;
    int count;
}ring_buff_t;

/* Functions ============================================================================*/
/* TODO: Creation of a gpio_set function for the calling / handling of all current and future GPIOs*/
/* void gpio_set()
{
    LED2_init();        TIM2->SR &= ~(TIM_SR_UIF);       // Clearing the interrupt Flag

}
 */

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
void RingBuff_Push(ring_buff_t *Buff, uint8_t rxByte_in)
{
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

void TxBuff_Check()
{

}

void TxBuff_Push()
{

}

void TxBuff_Pop()
{

}


void LED2_init()
{
    /* GPIOA Initialisation */
    GPIOA->MODER    &= ~(0x3U << GPIO_MODER_MODER5_Pos);        // Clearing GPIOA Pin 5
    GPIOA->MODER    |= GPIO_MODER_MODER5_0;                     // Setting the GPIO to Output Mode
}

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

/* LED Functions ===============================================================================*/

void LED2_update()
{
    static led2_status_t led2_status = OFF;
    
    led2_status++;
    led2_status = led2_status % LED2_ENUM_END;   // Finds the remainder between current status / 2 

    uint8_t bsrr_pos = 5 + (16*led2_status);
    
    GPIOA->BSRR = (1U << bsrr_pos);        
}

// TODO: UART / USB Serial Connection Test Function

void TIM2_init()
{
    RCC->APB1ENR    |= RCC_APB1ENR_TIM2EN;                      // Enable clock for TIM2 EN

    TIM2->DIER      |= TIM_DIER_UIE;                            // Enables Update Interrupt 
    TIM2->PSC       =  7999;                                    // Clock Frequency reduced to every 1ms
    TIM2->ARR       =  999;                                     // Update Event every 1s
    
    NVIC_EnableIRQ(TIM2_IRQn);                                  // Enables interrupt within NVIC
    TIM2->CR1 |= TIM_CR1_CEN;                                   // Enables Counter
}

/* Timer Function (TIM2) */
void TIM2_IRQHandler()
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~(TIM_SR_UIF);       // Clearing the interrupt Flag
        
        g_tick_count++;
        if((g_tick_count % 5) == 0)
        {
            LED2_update();
            USART2_string("Tick Update!\r\n");
        }
    }
    
    // TODO: Disable unused peripherals.
    // TODO: Wakeup peripheral re-initilisation on timer interrupt.
}

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

/**
 * @brief Main Program Loop
 */
__attribute__((noreturn)) void main() 
{
    /* RCC Peripheral Enabling / Initialisation */
    RCC->AHBENR     |= RCC_AHBENR_GPIOAEN;                      // Enable Clock for GPIOA EN

    LED2_init();
    TIM2_init();
    USART2_init();
    RingBuff_init();
    
    /* Main Loop */
    while (1)
    {
        // TODO: Implement Low Power Mode (LPWM).
        __WFI();// Runs forever
    }
}