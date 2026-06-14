/**
 * @file led2.h
 * @author L. Nicholson-Andrews
 * 
 * @brief Holds the Interfaces for the LED2 Peripheral.
 */
#ifndef LED2_H
#define LED2_H

#include <stdlib.h>
#include <stdint.h>

#include "main.h"

/* Defined Types =========================================================================*/
typedef enum led2_status_e{
    ON,
    OFF,
    LED2_ENUM_END
} led2_status_t;

/* Function Prototypes */
void LED2_init();
void LED2_update();

#endif // LED2_H