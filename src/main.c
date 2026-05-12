/**
 * @file    main.c
 * @author  Lewis Nicholson-Andrews
 * @brief   This is where the main logic of the program is held
 * 
 */

#include <stdio.h>
#include <stdint.h>

#define BUFF        2586
#define UART_CHAN   5
#define LED_PIN     (1U << 5)

/* Different states of the LED */
typedef enum{
    LED_ON, 
    LED_OFF
}led_status_t;

/* LED Blink Function*/
void LED_BLINK()
{
    // LED turns on every 5 seconds for 2 seconds
}

/* Something to handle blinking when pressing button */
void LED_TOGGLE()
{
    // when button is pressed
    // LED is turned on

    // When LED is not pressed
    // LED is turned off
}

/* TODO: include the LED Blink function*/
int main()
{
    printf("Hello World\n");
}

