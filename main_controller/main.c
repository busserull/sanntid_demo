#define F_CPU 4197200

#include <avr/io.h>
#include <util/delay.h>

int main(){
	while(1){
		_delay_ms(100);
	}

	return 0;
}
