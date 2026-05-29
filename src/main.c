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
// #define BUTTON1

#define volatile LED2 0x40020000

/*========================================================================================*/

typedef enum{
    LED_ON,
    LED_OFF
} led_status_t;


// TODO: LED Blink function
void LED_Blink ()
{
    // Toggle the LED GPIO from OFF to ON
    LEd

    // Toggle the LED Based on the SysTick Timer
}

// TODO: UART / USB Serial Connection Test Function
void serial_conn()
{
    /* Using the ST-Link Digital Port tests communication between the
       Dev Kit and the PC */
}

__attribute__((noreturn)) void main() 
{
    while(1) 
    {
        // LED_Blink();
        if (LED_ON)
        {

        }

        // serial_conn();
    }
}
