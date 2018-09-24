#define F_CPU 4197200

#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"
#include "led_driver.h"
#include "uart.h"

int main(){
	spi_init();
	uart_init();

	led_array_init();
	led_array_zero();

	int screen_counter = 0;
	int setting = 1;

	while(1){
		spi_send(screen_counter);

		if(screen_counter > 25){
			screen_counter = 0;
			setting = !setting;
		}
		uart_send(uart_receive())
		led_array_set(screen_counter / 5, screen_counter % 5, setting);
		led_grid_write();

		screen_counter++;
		_delay_ms(100);
	}

	return 0;
}
