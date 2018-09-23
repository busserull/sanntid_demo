#define F_CPU 4197200

#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"
#include "led_driver.h"

int main(){
	spi_init();

	led_array_init();
	led_array_zero();

	int screen_counter = 0;

	while(1){
		spi_send(screen_counter);

		screen_counter++;
		if(screen_counter > 25){
			screen_counter = 0;
		}

		led_array_set(screen_counter / 5, screen_counter % 5, 1);
		led_grid_write();

		_delay_ms(100);
	}

	return 0;
}
