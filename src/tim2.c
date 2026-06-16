


#include "stm32f334x8.h"
#include "tim2.h"
#include "usart2.h"
#include "led2.h"

void TIM2_init()
{
    RCC->APB1ENR    |= RCC_APB1ENR_TIM2EN;                      // Enable clock for TIM2 EN

    TIM2->DIER      |= TIM_DIER_UIE;                            // Enables Update Interrupt 
    TIM2->PSC       =  7999;                                    // Clock Frequency reduced to every 1ms
    TIM2->ARR       =  999;                                     // Update Event every 1s
    
    NVIC_EnableIRQ(TIM2_IRQn);                                  // Enables interrupt within NVIC
    TIM2->CR1 |= TIM_CR1_CEN;                                   // Enables Counter
}

/* Timer Function (TIM2) */
void TIM2_IRQHandler()
{
    // TODO: Implement state handling
    status_code_t result;

    /* Status Register and Update Interrupt Flag are enabled */
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~(TIM_SR_UIF);          // Clearing the interrupt Flag
        
        g_tick_count++;
        if((g_tick_count % 2) == 0)
        {
            USART2_read();                  // Read every 2 seconds
        }
        if((g_tick_count % 5) == 0)
        {
            LED2_update();
            USART2_string("Tick Update!\r\n");
            USART2_print();
        }
    }
    
    // TODO: Disable unused peripherals.
    // TODO: Wakeup peripheral re-initilisation on timer interrupt.
}
