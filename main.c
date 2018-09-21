#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include "segment_display.h"

int main(){

	seg_init();

	int counter = 0;

	while(1){
		while(counter < 100){
			seg_clear(SEGMENT_DISPLAY_LEFT);
			seg_clear(SEGMENT_DISPLAY_RIGHT);

			seg_set(SEGMENT_DISPLAY_LEFT, counter / 10);
			seg_set(SEGMENT_DISPLAY_RIGHT, counter % 10);

			counter++;

			_delay_ms(100);
		}

		counter = 0;
	}

	return 0;
}
