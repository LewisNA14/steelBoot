/**
 * @file    main.c
 * @author  Lewis Nicholson-Andrews
 * @brief   This is where the main logic of the program is held
 * 
 */

volatile int x = 5;      // Global, volatile, initialised
volatile int y = 6;      // Global, volatile, initialised

__attribute__((noreturn)) void main() 
{
    while(1) 
    {
        x++;             // Compiler must respect 'x' because it's volatile
    }
}

/* This is for testing as it ensures that the .data end point address is moved due to the compiler having
   to respect the volatile variables. */