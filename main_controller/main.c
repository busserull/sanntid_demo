#define F_CPU 4197200

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "spi.h"
#include "led_driver.h"
#include "uart.h"

#define STX 0x02
#define ETX 0x03

static uint8_t led_status[25] = {0};

void broadcast_led_status(uint8_t * leds){
	uart_send(STX);

	for(int i = 0; i < 25; i++){
		uart_send(leds[i]);
	}

	uart_send(ETX);
}

int main(){
	spi_init();
	uart_init();

	led_array_init();
	led_array_zero();

	int screen_counter = 0;
	int setting = 1;

	int segment_left;
	int segment_right;

	while(1){
		led_array_get(led_status);
		broadcast_led_status(led_status);

		spi_send(screen_counter);

		if(screen_counter > 25){
			screen_counter = 0;
			setting = !setting;
		}

		segment_left = screen_counter / 5;
		segment_right = screen_counter % 5;
		led_array_set(segment_left, segment_right, setting);

		led_grid_write();

		screen_counter++;
		_delay_ms(100);
	}

	return 0;
}
