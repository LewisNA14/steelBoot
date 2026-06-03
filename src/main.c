/**
 * @file    main.c
 * @author  Lewis Nicholson-Andrews
 * @brief   This is where the main logic of the program is held
 * 
 */

/* Includes ==============================================================================*/ 
#include <stdint.h>
#include "stm32f334x8.h"

/* Defined Types =========================================================================*/
typedef enum led_status_e{
    ON,
    OFF,
    LED_ENUM_END
} led_status_t;

/* Functions ============================================================================*/
/* TODO: Creation of a gpio_set function for the calling / handling of all current and future GPIOs*/
/* void gpio_set()
{
    led_status_t LED_Set(pin_no);              // Toggling the LED using BSRR (Bit Set Reset Register).
}
 */
void LED_Set()
{
    static led_status_t led_status = OFF;     // Default value is OFF

    led_status++;
    led_status = led_status % LED_ENUM_END;

    uint8_t bsrr_pos = 5 + (16*led_status);
    
    GPIOA->BSRR = (1U << bsrr_pos);        
    
    // TODO: Toggle the LED Based on a simple Timer
}

// TODO: UART / USB Serial Connection Test Function
// void Serial_Conn

void delay(uint32_t count)
{
    volatile uint32_t i = count;
    while (i-- > 0)
    {
        __asm("nop");
    }
}

/* TODO: Implement Simple Timer using a TIM peripheral */
/* Timer Function (TIM2) */
void timer()
{
    // enable the TIM2 Peripheral
    NVIC_EnableIRQ(TIM2_IRQn);

    // shuts down all un-used peripherals

    // enables mentioned / defined peripherals

    // counts up from 0 to 1 second to enable interrupt to switch LED state
}


/**
 * @brief Main Program Loop
 */
__attribute__((noreturn)) void main() 
{
    led_status_t led_status;

    led_status = OFF;

    /* RCC Peripheral Enabling / Initialisation */
    RCC->AHBENR     |= RCC_AHBENR_GPIOAEN;                      // Enable Clock for GPIOA EN
    RCC->APB1ENR    |= RCC_APB1ENR_TIM2EN;                      // Enable clock for TIM2 EN

    /* GPIOA Initialisation */
    GPIOA->MODER    &= ~(0x3U << GPIO_MODER_MODER5_Pos);       // Clearing GPIOA Pin 5
    GPIOA->MODER    |= GPIO_MODER_MODER5_0;                    // Setting the GPIO to Output Mode

    /* TIM2 Initialisation */
    TIM2->DIER      |= TIM_DIER_UIE;                            // Enables Update Interrupt 
    TIM2->PSC       =  7999;                                    // Clock Frequency reduced to every 1ms
    TIM2->ARR       =  999;                                     // Update Event every 1s


    // Clear the TIM2 Pin 
    // Set the TIM2 with the prescaler

    /* Main Loop */
    while (1)
    {
        delay(8000000);                     // Clock Speed is 8MHz so 5s is 40,000,000 / 5 cycles per loop = 8,000,000
        // gpio_set();          
        LED_Set();               
        delay(8000000);                  
        
    }
}