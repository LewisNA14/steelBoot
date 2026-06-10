/**
 * @file    main.c
 * @author  Lewis Nicholson-Andrews
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

typedef enum usart2_status_e{
    CLOSED,
    RX,
    TX,
    USART2_END
} usart2_status_t;

/* Defined Structs ======================================================================*/
typedef struct Rx_ring_buff_s{
    int rx_buff[RING_BUFF];
    int rx_head;
    int rx_tail;
    int rx_size;
}Rx_ring_buff_t;

typedef struct Tx_ring_buff_s{
    int Tx_Buff[RING_BUFF];
    int tx_head;
    int tx_tail;
    int tx_size;
}Tx_ring_buff_t;

/* Functions ============================================================================*/
/* TODO: Creation of a gpio_set function for the calling / handling of all current and future GPIOs*/
/* void gpio_set()
{
    LED2_init();        TIM2->SR &= ~(TIM_SR_UIF);       // Clearing the interrupt Flag

}
 */

void RingBuff_init(Tx_ring_buff_t *txBuff, Rx_ring_buff_t *rxBuff)
{
    // 1. Reset all values within the buffer to 0 or NULL.
    txBuff->tx_head = 0;
    txBuff->tx_tail = 0;
    txBuff->tx_size = 0;

    rxBuff->rx_head = 0;
    rxBuff->rx_tail = 0;
    rxBuff->rx_size = 0;
}

void RxBuff_Check()
{
    // 1. Check the buffer is empty
    // 2. If it's empty return a state or value to indicate as such
}

void RxBuff_Update()
{
    // 1. Check the value is valid of which you want to instert
    // 2. If ok then insert the value into the RxBuff 
    // 3. Update the head of the ring buffer to reflect the increased no of values
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

/* USART2 Rx Functions */
char USART2_read()
{
    int i = 0;
    char read_buff[256];
    while(!(USART2->ISR & USART_ISR_RXNE))
    {
        /* Wait for data to be read as channel is empty */
    }
    do
    {
        read_buff[i] = USART2->RDR;
        i++;
    }
    while(read_buff[i-1] != '\r' && read_buff[i-1] != '\n');
    // TODO: instead of read buff use the Rx_Ring_Buff    
}


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
 *      if (USART_CR1_TXEIE)
 *      {
 *          USART2_write("Transmit Data Register is empty!");
 *      }
 * }
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
    
    /* Main Loop */
    while (1)
    {
        // TODO: Implement Low Power Mode (LPWM).
        __WFI();// Runs forever
    }
}