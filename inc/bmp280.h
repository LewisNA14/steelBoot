/**
 * @file    :   bmp280.h
 * 
 * @author  :   Lewis Nicholson-Andrews (lewisnich01@outlook.com)
 * @date    :   02.11.2026
 */

#ifndef BMP280_H_
#define BMP280_H_
/*========Include========*/
#include <stdint.h>


/*========Defines========*/
#define TEMP_XLSB   0xFC
#define TEMP_LSB    0xFB
#define TEMP_MSB    0xFA

#define PRESS_XLSB  0xF9
#define PRESS_LSB   0XF8
#define PRESS_MSB   0xF7

#define BM280_CONFIG        0xF5
#define BMP280_CTRL_MEAS    0xF4
#define BMP280_STATUS       0xF3
#define BMP280_RESET        0xE0
#define BMP280_ID           0xD0


/*========Function Prototypes=========*/
void bmp280_init(void);

void bmp280_read(void);

void bmp280_reset(void);
void bmp280_get_status(void);





#endif /*BMP280_H_*/