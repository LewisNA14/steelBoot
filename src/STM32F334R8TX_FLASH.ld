/**
 * @file STM32F334R8TX_FLASH.ld
 * @author Lewis Nicholson-Andrews
 * 
 * @brief This file contains the Memory Addresses for FLASH and SRAM for the linker
 */

/* Memory Areas */
 MEMORY
 {
    FLASH 0x08000000, 
    SRAM  0x20000000
 }

 /* Defining Ouput Sections */
Sections
{
    . = 0x10000;
    .text : { *(.text) }
    . = 0x8000000;
    .bss : { *(.bss); *(.bss.*)}
    .data : { *(.data); (.data.*)}
    .rodata : { *(.rodata); *(.rodata.*)}
}


Main architecture is we want

Memory for FLASH - Loading the firmware onto the device
Memory for the SRAM - the actual executable code for the device

In this instance SRAM is the LED Blink

The part i'm unsure on is what contents need to be in which sections and which order do they
need to be in