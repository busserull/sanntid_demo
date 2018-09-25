#ifndef LED_DRIVER_H
#define LED_DRIVER_H
#include <stdint.h>

void led_array_init();

void led_array_get(uint8_t * array);

void led_array_toggle(uint8_t x, uint8_t y);

#endif
