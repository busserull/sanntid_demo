#ifndef LED_DRIVER_H
#define LED_DRIVER_H



void zero_led_array(void);
uint32_t get_led_array(void);
void update_led(uint8_t x, uint8_t y, uint8_t value);
void refresh_led_array(void);

#endif