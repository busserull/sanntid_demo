#define F_CPU 4197200

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "spi.h"
#include "led_driver.h"
#include "uart.h"

#define STX 0x02
#define ETX 0x03
#define MAGIC_OFFSET 0x05

static uint8_t led_status[25] = {0};

void broadcast_led_status(uint8_t * leds){
	uart_send(STX);

	for(int i = 0; i < 25; i++){
		uart_send(leds[i]);
	}

	uart_send(ETX);
}

int read_toggle_command(){
	char stx_byte = uart_receive();
	if(stx_byte != STX){
		return -1;
	}

	char led_byte_magic_offset = '\0';
	char etx_byte = '\0';

	// Try to read LED number 5 times before aborting
	for(int i = 0; i < 5; i++){
		led_byte_magic_offset = uart_receive();
		if(led_byte_magic_offset != '\0'){
			break;
		}
	}
	if(led_byte_magic_offset == '\0'){
		return -1;
	}

	// Try to read ETX 5 times before aborting
	for(int i = 0; i < 5; i++){
		etx_byte = uart_receive();
		if(etx_byte != '\0'){
			break;
		}
	}
	if(etx_byte != ETX){
		return -1;
	}

	return led_byte_magic_offset - MAGIC_OFFSET;
}

int main(){
	spi_init();
	uart_init();
	led_array_init();

	int led_command;
	while(1){
		led_command = read_toggle_command();

		if(led_command != -1){
			uint8_t x_coord = led_command % 5;
			uint8_t y_coord = led_command / 5;
			led_array_toggle(x_coord, y_coord);
		}

		led_array_get(led_status);
		broadcast_led_status(led_status);

		int leds_on = 0;
		for(int i = 0; i < 25; i++){
			if(led_status[i]){
				leds_on++;
			}
		}

		spi_send(leds_on);
	}

	return 0;
}
