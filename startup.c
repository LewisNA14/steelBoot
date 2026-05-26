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
void sysTick_Handler(void)      __attribute__((weak, alias("Default_Handler")));

/* Default Handler */
void Default_Handler(void); 

/* Interrupts */
void IRQ0_Handler()  __attribute__((weak, alias("Default_Handler")));            /* Interrupt 0 */            
void IRQ1_Handler()  __attribute__((weak, alias("Default_Handler")));            /* Interrupt 1 */
void IRQ2_Handler()  __attribute__((weak, alias("Default_Handler")));            /* Interrupt 2 */
void IRQ3_Handler()  __attribute__((weak, alias("Default_Handler")));            /* Interrupt 3 */
    
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
    sysTick_Handler,                                    /* SysTick Handler*/

    /* Interrupts */
    IRQ0_Handler,               /* Interrupt 0 */
    IRQ1_Handler,               /* Interrupt 1 */
    IRQ2_Handler,               /* Interrupt 2 */
    IRQ3_Handler,               /* Interrupt 3 */

    // The number of interrupts goes up to IRQ 239 However I don't think we actually need that many
};

void Default_Handler()
{
    while (1)
    {
        // Runs forever
    }
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