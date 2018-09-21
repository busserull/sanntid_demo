#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

int main(){
	DDRC |= (1 << PC5);
	PORTC |= (1 << PC5);

	while(1){
		PORTC &= ~(1 << PC5);
		_delay_ms(100);
		PORTC |= (1 << PC5);
		_delay_ms(100);
	}

	return 0;
}
