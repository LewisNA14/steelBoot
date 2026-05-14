/**
 * @file STM32F334R8TX_FLASH.ld
 * @author Lewis Nicholson-Andrews
 * 
 * @brief This file contains the Memory Addresses for FLASH and SRAM for the linker
 */

_estack = ORIGIN(SRAM) + LENGTH(SRAM); /* Top of RAM */
_min_heap_size  = 0x400;        /* 1KB heap */
_min_stack_size = 0x800;        /* 2KB stack */

ENTRY(Reset_Handler)

/* Memory Areas */
 MEMORY
 {
    FLASH(rx)   : ORIGIN   = 0x08000000,    LENGTH = 64K
    SRAM(rwx)   : ORIGIN   = 0x20000000,    LENGTH = 12K
 }

 /* Defining Ouput Sections */
SECTIONS
{
    /* Executable Code */
    .text : ALIGN (4)
    {
        /* Vector Table */
        KEEP(*(.isr_vector))    /* Find the attribute section from the C code */
        *(.text*)               /* Program Code */
        *(.text)                /* All other code */
        *(.rodata*)             /* Read-only data */
        . = ALIGN(4);           /* Aligns the data to be 4 bytes long */
    } > FLASH

    /* Initialised Data */
    .data : ALIGN(4)
    {
        *(.data*)       
        . = ALIGN(4)
    } > SRAM AT > FLASH

    /* Uninitialised Data */
    .bss : ALIGN (4)
    {
        *(.bss*)        
        . = ALIGN(4)
    } > SRAM
}

/* Input Section for Vector Table .vector0

/* Main architecture is we want

Memory for FLASH - Loading the firmware onto the device
Memory for the SRAM - the actual executable code for the device

In this instance FLASH holds the executable code for LED Blink 

Having a look SRAM just contains volatile memory so most of the key executables and variables will be held in
FLASH. 

Now i've included a vector table*/