#ifndef SPI_H
#define SPI_H
#include <stdint.h>

void spi_init();

void spi_send(uint8_t byte);

#endif
