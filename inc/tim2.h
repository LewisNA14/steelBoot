

#ifndef TIM2_H
#define TIM2_H

/* Includes */
#include <stdint.h>
#include <stdlib.h>

/* Extern Declarations */
extern uint32t_t g_tick_count;

/* Global Variables ======================================================================*/
volatile uint32_t g_tick_count = 0;

/* Function Prototypes */
void TIM2_init();
void TIM2_IRQHandler();

#endif // TIM2_H