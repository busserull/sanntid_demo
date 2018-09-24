#ifndef LED_DRIVER_H
#define LED_DRIVER_H
#include <stdint.h>

void led_array_init();

void led_array_zero();

void led_array_get(uint8_t *array);

void led_array_set(uint8_t x, uint8_t y, uint8_t value);

void led_grid_write();

#endif
