

#ifndef TIM2_H
#define TIM2_H

/* Includes */
#include <stdint.h>
#include <stdlib.h>

/* Extern Declarations */


/* Global Variables ======================================================================*/
extern volatile uint32_t g_tick_count;


/* Function Prototypes */
void TIM2_init();
void TIM2_IRQHandler();

#endif // TIM2_H