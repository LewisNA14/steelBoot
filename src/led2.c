/**
 * @file led2.c
 * @author L. Nicholson-Andrews
 * 
 * @brief
 */

/* Includes */

/* CMSIS Package Header File */
#include "stm32f334x8.h"


#include "led2.h"

/* Functions */
void LED2_init()
{
    /* GPIOA Initialisation */
    GPIOA->MODER    &= ~(0x3U << GPIO_MODER_MODER5_Pos);        // Clearing GPIOA Pin 5
    GPIOA->MODER    |= GPIO_MODER_MODER5_0;                     // Setting the GPIO to Output Mode
}

void LED2_update()
{
    static led2_status_t led2_status = OFF;
    
    led2_status++;
    led2_status = led2_status % LED2_ENUM_END;   // Finds the remainder between current status / 2 

    uint8_t bsrr_pos = 5 + (16*led2_status);
    
    GPIOA->BSRR = (1U << bsrr_pos);        
}