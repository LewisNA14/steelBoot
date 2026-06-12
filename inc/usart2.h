/**
 * @file usart2.h
 * @author L. Nicholson-Andrews
 * @brief This file contains the declaration, states and structs required for USART2.
 */
#ifndef USART2_H
#define USART2_H

/* Defined Types =========================================================================*/

/* typedef enum usart2_status_e{
    CLOSED,
    RX,
    TX,
    DONE,
    USART2_END
} usart2_status_t; */


 /* Function Prototypes */
void USART2_init();
void USART2_write(char c);
void USART2_string(const char* str);
void USART2_read();

#endif // USART2_H