/**
 * @file startup.c
 * @author L. Nicholson-Andrews (lewisnich01@outlook.com)
 * 
 * @brief Contains the vector table required for mapping memory addresses for symbols and variables
 */

#include <stdint.h>

/**
 * =============================================================================================
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

/* External reference to the Stack Pointer, defined in the Linker Script */
// TODO: Fix the stack pointer reference as it is currently not accepted by compiler
extern uint32_t _stack_ptr;
typedef void (*const vector_table_t)(void);

/* Defining the vector table is stored within the .isr_vector section rather
   Than the default which is bss */
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
    IRQ2_Handler,               /* Interrupt 4 */
    IRQ3_Handler,               /* Interrupt 3 */
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
    // Overwrite current .data values with ones copied from .text


    // Refresh / Wipe the values at .bss

    // Point / Call main function
    main();
}