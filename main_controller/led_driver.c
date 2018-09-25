#include "led_driver.h"
#include <avr/io.h>

//PORTA
#define LED_00 (1 << PA5)
#define LED_01 (1 << PA6)
#define LED_02 (1 << PA7)
#define LED_10 (1 << PA0)
#define LED_11 (1 << PA1)
#define LED_12 (1 << PA2)
#define LED_20 (1 << PA3)
#define LED_21 (1 << PA4)
//PORTB
#define LED_43 (1 << PB1)
#define LED_44 (1 << PB0)
//PORTC
#define LED_22 (1 << PC0)
#define LED_30 (1 << PC1)
#define LED_31 (1 << PC2)
#define LED_32 (1 << PC3)
#define LED_40 (1 << PC4)
#define LED_41 (1 << PC5)
#define LED_42 (1 << PC6)
//PORTD
#define LED_03 (1 << PD7)
#define LED_04 (1 << PD6)
#define LED_13 (1 << PD5)
#define LED_14 (1 << PD4)
#define LED_23 (1 << PD3)
#define LED_24 (1 << PD2)
#define LED_33 (1 << PD1)
#define LED_34 (1 << PD0)

static uint8_t led_array[5][5] = {0};

void led_array_init(){
	DDRA |= 0xff;
	DDRB |= (1 << PB0) | (1 << PB1);
	DDRC |= 0xff;
	DDRD |= 0xff;
}

void led_array_zero(){
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			led_array[i][j] = 0;
		}
	}
}

void led_array_get(uint8_t *array){
	for (int i = 0; i < 25; ++i)
	{
		array[i] = !(led_array[i%5][i/5]);
	}
}

void led_array_set(uint8_t x, uint8_t y, uint8_t value){
	if(x < 5 && x >= 0 && y < 5 && y >= 0){
		led_array[x][y] = 1 && value;
	}
	led_grid_write();
}

void led_grid_write(){
	PORTA = led_array[0][0]*LED_00 +
			led_array[0][1]*LED_01 +
			led_array[0][2]*LED_02 +
			led_array[1][0]*LED_10 +
			led_array[1][1]*LED_11 +
			led_array[1][2]*LED_12 +
			led_array[2][0]*LED_20 +
			led_array[2][1]*LED_21;
	PORTB &= 0b11111100 +
			 led_array[4][3]*LED_43 +
			 led_array[4][4]*LED_44;
	PORTB |= led_array[4][3]*LED_43 +
			 led_array[4][4]*LED_44;
	PORTC = led_array[2][2]*LED_22 +
			led_array[3][0]*LED_30 +
			led_array[3][1]*LED_31 +
			led_array[3][2]*LED_32 +
			led_array[4][0]*LED_40 +
			led_array[4][1]*LED_41 +
			led_array[4][2]*LED_42;
	PORTD = led_array[0][3]*LED_03 +
			led_array[0][4]*LED_04 +
			led_array[1][3]*LED_13 +
			led_array[1][4]*LED_14 +
			led_array[2][3]*LED_23 +
			led_array[2][4]*LED_24 +
			led_array[3][3]*LED_33 +
			led_array[3][4]*LED_34;
}















