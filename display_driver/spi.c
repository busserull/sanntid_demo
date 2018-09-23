#include "spi.h"
#include <avr/io.h>

void spi_init(){
	PRR &= ~(1 << PRSPI);

	// Enable SPI slave mode
	SPCR = (1 << SPE);
}

void spi_read(int * read_out){
	if(SPSR & (1 << SPIF)){
		*read_out = SPDR;
	}
}
