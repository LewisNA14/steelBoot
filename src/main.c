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
    LED_ON,
    LED_OFF
} led_status_t;


// TODO: LED Blink function
void LED_Blink ()
{
    // Toggle the LED GPIO from OFF to ON

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
    // 1. Enable Clock for GPIOA
    // RCC_AHBENR bit 17 is GPIOAEN
    RCC->AHBENR |= (1 << 17);

    // 2. Set PA5 as Output
    // GPIOA_MODER: Clear bits 11:10 (00), then set bit 10 to 1 (01 = Output)
    GPIOA->MODER &= ~(3 << 10);
    GPIOA->MODER |= (1 << 10);

    while (1) {
        // 3. Toggle PA5
        // GPIOA_ODR bit 5
        GPIOA->ODR ^= (1 << 5);
        
        delay(500000); // Adjust based on clock speed
    }
}
