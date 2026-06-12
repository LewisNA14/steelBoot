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
#include "led2.c"
#include "ringbuff.c"
#include "tim2.c"
#include "usart2.c"



/* Defines ===============================================================================*/




/* Global Variables ======================================================================*/
volatile uint32_t g_tick_count = 0;


/* Function Prototypes ===================================================================*/
void gpio_set();

/* Defined Types =========================================================================*/



/* Defined Structs ======================================================================*/


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