/**
 * @file    :   status.h
 * 
 * 
 */

#ifndef STATUS_H
#define STATUS_H

typedef enum status_code_e{
    DONE        = 0,
    BUSY        = 1,
    OVERWRITE   = 2,
    ERROR       = 3
} status_code_t;

#endif // STATUS_H