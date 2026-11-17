/**
 * @file    :   bmp280.c
 * 
 * @brief   :   Driver file for the BMP280 Temp / Pressure Sensor
 * 
 * @author  :   Lewis Nicholson-Andrews (lewisnich01@outlook.com)
 * @date    :   02.11.2026
 */

void BMP280_init()
{
    // Enable GPIOC Clock
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    // PC6 / PC8: general purpose output (01), masked writes only
    GPIOC->MODER   &= ~((3U << (6*2)) | (3U << (8*2)));
    GPIOC->MODER   |=  ((1U << (6*2)) | (1U << (8*2)));

    // Open-drain
    GPIOC->OTYPER  |=  (1U << 6) | (1U << 8);

    // Pull-up (01), harmless if your breakout already has external pull-ups
    GPIOC->PUPDR   &= ~((3U << (6*2)) | (3U << (8*2)));
    GPIOC->PUPDR   |=  ((1U << (6*2)) | (1U << (8*2)));
}

void BMP280_read()
{

}