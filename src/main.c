/**
 * @file    main.c
 * @author  Lewis Nicholson-Andrews
 * @brief   This is where the main logic of the program is held
 * 
 */

/* Includes ==============================================================================*/ 
#include <stdint.h>
#include "stm32f334x8.h"

/* Global Variables ======================================================================*/
volatile uint32_t g_tick_count = 0;

/* Function Prototypes ===================================================================*/
void gpio_set();


void LED2_init();
void LED2_update();

void USART2_init();
void USART2_Tx();
void USART2_Rx();

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
/* Functions ============================================================================*/
/* TODO: Creation of a gpio_set function for the calling / handling of all current and future GPIOs*/
/* void gpio_set()
{
    LED2_init();        TIM2->SR &= ~(TIM_SR_UIF);       // Clearing the interrupt Flag

}
 */

void LED2_init()
{
    /* GPIOA Initialisation */
    GPIOA->MODER    &= ~(0x3U << GPIO_MODER_MODER5_Pos);        // Clearing GPIOA Pin 5
    GPIOA->MODER    |= GPIO_MODER_MODER5_0;                     // Setting the GPIO to Output Mode
}

void USART2_init()
{
    // Tx is Pin PA2
    // Rx is Pin PA3
    RCC->APB1ENR    |= RCC_APB1ENR_USART2EN;                    // Enable the USART2 Peripheral at the Reset Clock

    // Enabling Tx and Rx on GPIOA
    GPIO->MODER     &= ~(3U << GPIO_MODER_MODER2_Pos)           // Clearing Tx Bits
    GPIO->MODER     &= ~(3U << GPIO_MODER_MODER3_Pos)           // Clearing Rx Bits

    GPIOA->MODER    |= GPIO_MODER_MODER2_0;                     // Setting Tx Pin 
    GPIOA->MODER    |= GPIO_MODER_MODER3_0;                     // Setting Rx Pin 

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
        }
    }
    
    // TODO: Disable unused peripherals.
    // TODO: Wakeup peripheral re-initilisation on timer interrupt.
}


/**
 * @brief Main Program Loop
 */
__attribute__((noreturn)) void main() 
{
    /* RCC Peripheral Enabling / Initialisation */
    RCC->AHBENR     |= RCC_AHBENR_GPIOAEN;                      // Enable Clock for GPIOA EN

    LED2_init();
    TIM2_init();
    
    /* Main Loop */
    while (1)
    {
        // TODO: Implement Low Power Mode (LPWM).
        __WFI();// Runs forever
    }
}