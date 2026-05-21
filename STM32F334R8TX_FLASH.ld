/**
 * @file STM32F334R8TX_FLASH.ld
 * @author Lewis Nicholson-Andrews
 * 
 * @brief This file contains the Memory Addresses for FLASH and SRAM for the linker
 */

_stack_ptr      = ORIGIN(SRAM) + LENGTH(SRAM);  /* Top of RAM */
_min_heap_size  = 0x200;                        /* 0.5KB heap */
_min_stack_size = 0x400;                        /* 1KB stack */

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
    /* The startup code into "FLASH" ROM type Memory */
    /* Vector Table */
    .isr_vector : 
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))    /* Find the attribute section from the C code */
        . = ALIGN(4);
    } > FLASH

    /* Executable Code */
    .text : ALIGN (4)
    {
        *(.text*)               /* Program Code */
        *(.rodata*)             /* Read-only data */
        . = ALIGN(4);           /* Aligns the data to be 4 bytes long */
    } > FLASH

    /* Initialised Data */
    _DATA_LOAD = LOADADDR(.data);
    .data : ALIGN(4)
    {
        _DATA_START = .;
        *(.data*)   
        . = ALIGN(4);
        _DATA_END = .;  
    } > SRAM AT > FLASH

    /* Uninitialised Data */
    .bss : ALIGN (4)
    {
        _BSS_START = .;
        *(.bss*)        
        . = ALIGN(4);
        _BSS_END = .;
    } > SRAM
}

/* Main architecture:
    Memory is split as follows:
    Flash   - 64KB
    SRAM    - 12KB

    All data is aligned and padded to 4 bytes long (32-bits) as the STM32 Nucleo F334R8 uses a 32-bit arm chip

    Flash Contains the following:
    - isr vector Table
    - .text     -> Program Code
    - .rodata   -> Read-Only data (is immutable)
    - .data     -> Initialised variables

    SRAM Contains the following:
    - .data     -> Intialised Variables
    - .bss      -> Uninitialised Variables
*/