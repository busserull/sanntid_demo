#include "spi.h"
#include <avr/io.h>

void spi_init(){
	// Out: ~SS, MOSI, SCK
	DDRB |= (1 << PB4) | (1 << PB5) | (1 << PB7);

	// SPI Master, 128 prescaler
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (1 << SPR1);

	// Drive ~SS high
	PORTB |= (1 << PB4);
}

void spi_send(uint8_t byte){
	PORTB &= ~(1 << PB4);

	SPDR = byte;
	while(!(SPSR & (1 << SPIF)));

	PORTB |= (1 << PB4);
}
