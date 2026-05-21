/**
 * @file startup.c
 * @author L. Nicholson-Andrews (lewisnich01@outlook.com)
 * 
 * @brief Contains the vector table required for mapping memory addresses for symbols and variables
 */

#include <stdint.h>

 /* External reference to the Stack Pointer, defined in your Linker Script */
extern uint32_t _stack_ptr;

/* Prototype for the Reset Handler */
void Reset_Handler(void);

/* The Vector Table */
__attribute__((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = 
{
    (void (*)(void))(&_stack_ptr),  // 1. Initial Stack Pointer
    Reset_Handler,                  // 2. Reset Handler (Vector 1)
    // You can add more (NMI, HardFault, etc.) later. 
    // For now, just these two are enough to satisfy the hardware.
};

/* The Reset Handler: The entry point of your program */
void Reset_Handler(void) 
{
    // 1. Copy .data section from Flash to RAM (if you have initialized variables)
    // 2. Zero-fill the .bss section (if you have global variables)
    // 3. Call main()
    
    // For now, just jump to main
    extern int main(void);
    main();

    // Catch if main ever returns
    while(1);
}