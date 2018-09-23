#define F_CPU 4197200

#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"

int main(){
	spi_init();

	int screen_counter = 0;

	while(1){
		spi_send(screen_counter);

		screen_counter++;
		if(screen_counter > 25){
			screen_counter = 0;
		}

		_delay_ms(10);
	}

	return 0;
}
