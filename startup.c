/**
 * @file startup.c
 * @author L. Nicholson-Andrews (lewisnich01@outlook.com)
 * 
 * @brief Contains the vector table required for mapping memory addresses for symbols and variables
 */

#include <stdint.h>

/*=============================================================================================*/
/** 
 * @section Externs
 * @brief Contains External References defined in other files (mainly Linker Script)
 */

/* External reference to the Stack Pointer, defined in the Linker Script */
extern uint32_t _stack_ptr;

/* .data Load, Start and End symbols */
extern uint32_t _DATA_LOAD;
extern uint32_t _DATA_START;
extern uint32_t _DATA_END;

/* .bss Start and End Symbols */
extern uint32_t _BSS_START; 
extern uint32_t _BSS_END;


/*=============================================================================================*/

/**
 * Function Prototypes 
 * @brief Contains all the Function Defines for the exceptions
 * 
 * */
extern void main();

void Reset_Handler(void);

/* Currently Unused will call to Default_Handler*/
void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias("Default_Handler")));

/* Default Handler */
void Default_Handler(void); 

/* Interrupts */
void IRQ0_Handler()     __attribute__((weak, alias("Default_Handler")));            /* Interrupt 0 */            
void IRQ1_Handler()     __attribute__((weak, alias("Default_Handler")));            /* Interrupt 1 */
void IRQ2_Handler()     __attribute__((weak, alias("Default_Handler")));            /* Interrupt 2 */
void IRQ3_Handler()     __attribute__((weak, alias("Default_Handler")));            /* Interrupt 3 */
void IRQ4_Handler()     __attribute__((weak, alias("Default_Handler")));            /* Interrupt 4 */
void IRQ5_Handler()     __attribute__((weak, alias("Default_Handler")));            /* Interrupt 5 */
void IRQ6_Handler()     __attribute__((weak, alias("Default_Handler")));            /* Interrupt 6 */
void IRQ7_Handler()     __attribute__((weak, alias("Default_Handler")));            /* Interrupt 7 */
void IRQ8_Handler()     __attribute__((weak, alias("Default_Handler")));            /* Interrupt 8 */
void IRQ9_Handler()     __attribute__((weak, alias("Default_Handler")));            /* Interrupt 9 */
void IRQ10_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 10 */
void IRQ11_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 11 */
void IRQ12_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 12 */
void IRQ13_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 13 */
void IRQ14_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 14 */
void IRQ15_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 15 */
void IRQ16_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 16 */
void IRQ17_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 17 */
void IRQ18_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 18 */
void IRQ19_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 19 */
void IRQ20_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 20 */
void IRQ21_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 21 */
void IRQ22_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 22 */
void IRQ23_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 23 */
void IRQ24_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 24 */
void IRQ25_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 25 */
void IRQ26_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 26 */
void IRQ27_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 27 */

void TIM2_Handler()    __attribute__((weak, alias("Default_Handler")));            /* Interrupt 28 */
    
/*=============================================================================================*/
/**
 * @section Vector Tables
 * @brief Contains the main vector table which holds the Exceptions and their functions
 */

/* Defining the vector table is stored within the .isr_vector section rather
   Than the default which is bss */
typedef void (*const vector_table_t)(void);

__attribute__((section(".isr_vector"), used))
const vector_table_t vector_table[255] = {        
/* Vector Table containing pointers to each relevant memory address */

    /* ARM Cortex-M4 Processor Exceptions*/
    (vector_table_t)(&_stack_ptr),                      /* Initial Stack Pointer */ 
    Reset_Handler,                                      /* Reset Handler */
    NMI_Handler,                                        /* NMI Handler */
    HardFault_Handler,                                  /* Hard Fault Handler */
    MemManage_Handler,                                  /* MPU Fault Handler */
    BusFault_Handler,                                   /* Bus Fault Handler*/
    UsageFault_Handler,                                 /* Usage Fault Handler */
    0,                                                  /* Reserved */
    0,                                                  /* Reserved */
    0,                                                  /* Reserved */
    0,                                                  /* Reserved */
    SVC_Handler,                                        /* SVC Handler */                   
    0,                                                  /* Reserved */
    0,                                                  /* Reserved */
    PendSV_Handler,                                     /* Pend SV Handler */
    SysTick_Handler,                                    /* SysTick Handler*/
    
    /* STM32 Specific Interrupts */
    IRQ0_Handler,                   /* Interrupt 0 */
    IRQ1_Handler,                   /* Interrupt 1 */
    IRQ2_Handler,                   /* Interrupt 2 */
    IRQ3_Handler,                   /* Interrupt 3 */
    IRQ4_Handler,                   /* Interrupt 4 */
    IRQ5_Handler,                   /* Interrupt 5 */
    IRQ6_Handler,                   /* Interrupt 6 */
    IRQ7_Handler,                   /* Interrupt 7 */
    IRQ8_Handler,                   /* Interrupt 8 */
    IRQ9_Handler,                   /* Interrupt 9 */
    IRQ10_Handler,                  /* Interrupt 10 */
    IRQ11_Handler,                  /* Interrupt 11 */
    IRQ12_Handler,                  /* Interrupt 12 */
    IRQ13_Handler,                  /* Interrupt 13 */
    IRQ14_Handler,                  /* Interrupt 14 */
    IRQ15_Handler,                  /* Interrupt 15 */
    IRQ16_Handler,                  /* Interrupt 16 */
    IRQ17_Handler,                  /* Interrupt 17 */
    IRQ18_Handler,                  /* Interrupt 18 */
    IRQ19_Handler,                  /* Interrupt 19 */
    IRQ20_Handler,                  /* Interrupt 20 */
    IRQ21_Handler,                  /* Interrupt 21 */
    IRQ22_Handler,                  /* Interrupt 22 */
    IRQ23_Handler,                  /* Interrupt 23 */
    IRQ24_Handler,                  /* Interrupt 24 */
    IRQ25_Handler,                  /* Interrupt 25 */
    IRQ26_Handler,                  /* Interrupt 26 */
    IRQ27_Handler,                  /* Interrupt 27 */

    TIM2_Handler,                   /* Interrupt 28 */

    // The number of interrupts goes up to IRQ 239 However I don't think we actually need that many
};

/* void SysTick_Handler()
{
    // TODO: write something for handling the Serial Clock / Timer provided by the STM board
} */

void Default_Handler()
{
    while (1)
    {
        // Runs forever
    }
}

void TIM2_Handler()
{
    
}

/* Reset Handler for reinitialising .data values from .text and wiping the .bss values */
void Reset_Handler()
{
    /* List of startaddresses for .data and .bss */
    uint32_t *pData = &_DATA_START;
    uint32_t *pBss  = &_BSS_START;

    /* Section Sizes*/
    uint32_t dataSize   = &_DATA_END - &_DATA_START;
    uint32_t bssSize    = &_BSS_END - &_BSS_START; 

    /* Source Address for .data copy in Flash */
    uint32_t *pSrc = &_DATA_LOAD;

    // Overwrite current .data values with ones copied from .text
    for (uint32_t i = 0; i < dataSize; i++)
    {
        pData[i] = pSrc[i];
    }
 
    // Refresh / Wipe the values at .bss
    for(uint32_t i = 0; i < bssSize; i++)
    {
        pBss[i] = 0;
    }

    // Point / Call main function
    main();
}