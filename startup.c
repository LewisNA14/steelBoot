/**
 * @file startup.c
 * @author L. Nicholson-Andrews (lewisnich01@outlook.com)
 * 
 * @brief Contains the vector table required for mapping memory addresses for symbols and variables
 */

#include <stdint.h>

/* External reference to the Stack Pointer, defined in the Linker Script */
extern uint32_t _stack_ptr;

/* Defining the vector table is stored within the .isr_vector section rather
   Than the default which is bss */
int __attribute__((section(".isr_vector"))) = {

}
// Vector Table containing pointers to each relevant memory address
void (*isr_vector_table[255]) = {
    // Vector & Offset
    initial_sp_val,                        /* Initial Stack Pointer */ 
    Reset_Handler,                         /* Reset Handler */
    NMI_Handler,                           /* NMI Handler */
    HardFault_Handler,                     /* Hard Fault Handler */
    MemManage_Handler,                     /* MPU Fault Handler */
    BusFault_Handler,                      /* Bus Fault Handler*/
    UsageFault_Handler,                    /* Usage Fault Handler */
    0,                                      /* Reserved */
    0,                                      /* Reserved */
    0,                                      /* Reserved */
    0,                                      /* Reserved */
    SVC_Handler,                           /* SVC Handler */                   
    0,                                      /* Reserved */
    0,                                      /* Reserved */
    PendSV_Handler,                        /* Pend SV Handler */
    sysTick_Handler,                       /* SysTick Handler*/

    /* Interrupts */
    IRQ0_Hand,               /* Interrupt 0 */
    IRQ1_Hand,               /* Interrupt 1 */
    IRQ2_Hand,               /* Interrupt 4 */
    IRQ3_Hand,               /* Interrupt 3 */
}


/* Reset Handler for reinitialising .data values from .text and wiping the .bss values */
void Reset_Handler()
{
    // Overwrite current .data values with ones copied from .text


    // Refresh / Wipe the values at .bss

    // Point / Call main function
    main()
}