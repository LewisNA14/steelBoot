/**
 * @file main.h
 * @author L. Nicholson-Andrews
 * 
 * @brief Includes interfacing and types for use across the program
 * 
*/
#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdint.h>

/* Type Defines*/
typedef enum status_code_e{
    DONE,       // 0
    BUSY,       // 1
    ERROR       // 2
}status_code_t;

/* Function Prototypes */
__attribute__((noreturn)) void main();

#endif // MAIN_H