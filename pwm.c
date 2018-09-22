#include "pwm.h"
#include <avr/io.h>

void pwm_init(){
	DDRB |= (1 << PB1);

	// Fast PWM, 50 Hz
	TCCR1A = (1 << COM1A1) | (1 << COM1A0) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);
	ICR1 = 20000;

	OCR1A = 18500;
}

void pwm_set_servo(int percent){
	OCR1A = 20000 - (10 * percent + 1000);
}
