/**
 * @file    main.c
 * @author  Lewis Nicholson-Andrews
 * @brief   This is where the main logic of the program is held
 * 
 */

#include <stdint.h>
#include "stm32f334x8.h"

/*========================================================================================*/
/**
 * @section Pin Registers
 */

/*========================================================================================*/

typedef enum{
    LED_OFF,
    LED_ON
} led_status_t;


// TODO: LED Blink function
led_status_t LED_Blink (led_status_t led_status)
{
    // Toggle the LED GPIO from OFF to ON
    if (led_status == LED_OFF)
    {
        GPIOA->ODR |= (1U << 5);       // GPIO_ODR_5
        led_status = LED_ON;
    }
    if (led_status == LED_ON)
    {
        GPIOA->ODR &= ~(1U << 5);       // GPIO_ODR_5
        led_status = LED_OFF;
    }
    
    // Toggle the LED Based on the SysTick Timer
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


__attribute__((noreturn)) void main() 
{
    led_status_t led_status;

    led_status = LED_OFF;

    // 1. Enable Clock for GPIOA EN
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // 2. Clearing GPIOA Pin 5
    GPIOA->MODER &= ~(0x3U << GPIO_MODER_MODER5_Pos);
    
    // 3. Setting the GPIO to Output Mode
    GPIOA->MODER |= GPIO_MODER_MODER5_0;
    while (1)
    {
        delay(8000000);                     // Clock Speed is 8MHz so 5s is 40,000,000 / 5 cycles per loop = 8,000,000
        // 4. Toggling the LED using ODR (Output Data Register).
        led_status = LED_Blink(led_status);
        delay(8000000);                     // Clock Speed is 8MHz so 5s is 40,000,000 / 5 cycles per loop = 8,000,000
        
    }
}
