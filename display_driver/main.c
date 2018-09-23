#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include "segment_display.h"
#include "pwm.h"
#include "spi.h"

int main(){
	spi_init();
	seg_init();
	pwm_init();

	int leds_on = 0;

	while(1){
		spi_read(&leds_on);

		seg_clear(SEGMENT_DISPLAY_LEFT);
		seg_clear(SEGMENT_DISPLAY_RIGHT);

		seg_set(SEGMENT_DISPLAY_LEFT, leds_on / 10);
		seg_set(SEGMENT_DISPLAY_RIGHT, leds_on % 10);

		// Servo takes position 0 to 100, we have 25 LEDs
		pwm_set_servo(4 * leds_on);
	}

	return 0;
}
