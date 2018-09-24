#include "uart.h"
#include <avr/io.h>

void uart_init(){
	DDRB &= ~(1 << PB2);
	DDRB |= (1 << PB3);

	// 9600 baud (9715.7 actual)
	UBRR1H = 0;
	UBRR1L = 26;

	UCSR1B |= (1 << RXEN1) | (1 << TXEN1);

	UCSR1C |= (1 << URSEL1) | (1 << UCSZ11) | (1 << UCSZ10);
}

void uart_send(char letter){
	while(!(UCSR1A & (1 << UDRE1)));
	UDR1 = letter;
}
