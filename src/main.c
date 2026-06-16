/**
 * @file    main.c
 * @brief   This is where the main logic of the program is held
 * 
 */

/* Includes ==============================================================================*/ 

/* Standard Library*/
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/* CMSIS Header File */
#include "stm32f334x8.h"

/* Peripheral Files */
#include "led2.h"
#include "ringbuff.h"
#include "tim2.h"
#include "usart2.h"

/* Defines ===============================================================================*/


/* Global Variables ======================================================================*/
volatile uint32_t g_tick_count;

ring_buff_t rxBuff;
ring_buff_t txBuff;

/* Functions ============================================================================*/
/* TODO: Creation of a gpio_set function for the calling / handling of all current and future GPIOs*/
/* void gpio_set()
{
    LED2_init();        TIM2->SR &= ~(TIM_SR_UIF);       // Clearing the interrupt Flag
}
*/

/**
 * @brief Main Program Loop
 */
__attribute__((noreturn)) void main() 
{
    /* RCC Peripheral Enabling / Initialisation */
    RCC->AHBENR     |= RCC_AHBENR_GPIOAEN;              // Enable Clock for GPIOA EN

    LED2_init();
    TIM2_init();
    USART2_init();
    
    RingBuff_init(&txBuff);
    RingBuff_init(&rxBuff);

    /* Main Loop */
    while (1)
    {
        // TODO: Implement Low Power Mode (LPWM).
        __WFI();// Runs forever
    }
}