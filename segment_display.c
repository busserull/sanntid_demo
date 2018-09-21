#include "segment_display.h"
#include <avr/io.h>

#define SET_L_A (PORTD &= ~(1 << PD3))
#define CLEAR_L_A (PORTD |= (1 << PD3))
#define SET_L_B (PORTD &= ~(1 << PD2))
#define CLEAR_L_B (PORTD |= (1 << PD2))
#define SET_L_C (PORTD &= ~(1 << PD6))
#define CLEAR_L_C (PORTD |= (1 << PD6))
#define SET_L_D (PORTD &= ~(1 << PD7))
#define CLEAR_L_D (PORTD |= (1 << PD7))
#define SET_L_E (PORTC &= ~(1 << PC0))
#define CLEAR_L_E (PORTC |= (1 << PC0))
#define SET_L_F (PORTD &= ~(1 << PD4))
#define CLEAR_L_F (PORTD |= (1 << PD4))
#define SET_L_G (PORTD &= ~(1 << PD5))
#define CLEAR_L_G (PORTD |= (1 << PD5))

#define SET_R_A (PORTC &= ~(1 << PC1))
#define CLEAR_R_A (PORTC |= (1 << PC1))
#define SET_R_B (PORTC &= ~(1 << PC2))
#define CLEAR_R_B (PORTC |= (1 << PC2))
#define SET_R_C (PORTC &= ~(1 << PC5))
#define CLEAR_R_C (PORTC |= (1 << PC5))
#define SET_R_D (PORTC &= ~(1 << PC4))
#define CLEAR_R_D (PORTC |= (1 << PC4))
#define SET_R_E (PORTC &= ~(1 << PC3))
#define CLEAR_R_E (PORTC |= (1 << PC3))
#define SET_R_F (PORTD &= ~(1 << PD0))
#define CLEAR_R_F (PORTD |= (1 << PD0))
#define SET_R_G (PORTD &= ~(1 << PD1))
#define CLEAR_R_G (PORTD |= (1 << PD1))


void seg_init(){
	DDRC |=
		(1 << PC0) |
		(1 << PC1) |
		(1 << PC2) |
		(1 << PC3) |
		(1 << PC4) |
		(1 << PC5);
	DDRD |=
		(1 << PD0) |
		(1 << PD1) |
		(1 << PD2) |
		(1 << PD3) |
		(1 << PD4) |
		(1 << PD5) |
		(1 << PD6) |
		(1 << PD7);

	// All segments start off
	PORTC |=
		(1 << PC0) |
		(1 << PC1) |
		(1 << PC2) |
		(1 << PC3) |
		(1 << PC4) |
		(1 << PC5);
	PORTD |=
		(1 << PD0) |
		(1 << PD1) |
		(1 << PD2) |
		(1 << PD3) |
		(1 << PD4) |
		(1 << PD5) |
		(1 << PD6) |
		(1 << PD7);
}

void seg_set(int display, int number){
	switch(display){
		case 0:
			switch(number){
				case 0:
					SET_L_A;
					SET_L_B;
					SET_L_C;
					SET_L_D;
					SET_L_E;
					SET_L_F;
					break;
				case 1:
					SET_L_B;
					SET_L_C;
					break;
				case 2:
					SET_L_A;
					SET_L_B;
					SET_L_D;
					SET_L_E;
					SET_L_G;
					break;
				case 3:
					SET_L_A;
					SET_L_B;
					SET_L_C;
					SET_L_D;
					SET_L_G;
					break;
				case 4:
					SET_L_B;
					SET_L_C;
					SET_L_F;
					SET_L_G;
					break;
				case 5:
					SET_L_A;
					SET_L_C;
					SET_L_D;
					SET_L_F;
					SET_L_G;
					break;
				case 6:
					SET_L_A;
					SET_L_C;
					SET_L_D;
					SET_L_E;
					SET_L_F;
					SET_L_G;
					break;
				case 7:
					SET_L_A;
					SET_L_B;
					SET_L_C;
					break;
				case 8:
					SET_L_A;
					SET_L_B;
					SET_L_C;
					SET_L_D;
					SET_L_E;
					SET_L_F;
					SET_L_G;
					break;
				case 9:
					SET_L_A;
					SET_L_B;
					SET_L_C;
					SET_L_F;
					SET_L_G;
					break;
				default:
					break;
			}
			break;
		case 1:
			switch(number){
				case 0:
					SET_R_A;
					SET_R_B;
					SET_R_C;
					SET_R_D;
					SET_R_E;
					SET_R_F;
					break;
				case 1:
					SET_R_B;
					SET_R_C;
					break;
				case 2:
					SET_R_A;
					SET_R_B;
					SET_R_D;
					SET_R_E;
					SET_R_G;
					break;
				case 3:
					SET_R_A;
					SET_R_B;
					SET_R_C;
					SET_R_D;
					SET_R_G;
					break;
				case 4:
					SET_R_B;
					SET_R_C;
					SET_R_F;
					SET_R_G;
					break;
				case 5:
					SET_R_A;
					SET_R_C;
					SET_R_D;
					SET_R_F;
					SET_R_G;
					break;
				case 6:
					SET_R_A;
					SET_R_C;
					SET_R_D;
					SET_R_E;
					SET_R_F;
					SET_R_G;
					break;
				case 7:
					SET_R_A;
					SET_R_B;
					SET_R_C;
					break;
				case 8:
					SET_R_A;
					SET_R_B;
					SET_R_C;
					SET_R_D;
					SET_R_E;
					SET_R_F;
					SET_R_G;
					break;
				case 9:
					SET_R_A;
					SET_R_B;
					SET_R_C;
					SET_R_F;
					SET_R_G;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void seg_clear(int display){
	switch(display){
		case 0:
			CLEAR_L_A;
			CLEAR_L_B;
			CLEAR_L_C;
			CLEAR_L_D;
			CLEAR_L_E;
			CLEAR_L_F;
			CLEAR_L_G;
			break;
		case 1:
			CLEAR_R_A;
			CLEAR_R_B;
			CLEAR_R_C;
			CLEAR_R_D;
			CLEAR_R_E;
			CLEAR_R_F;
			CLEAR_R_G;
			break;
		default:
			break;
	}
}
