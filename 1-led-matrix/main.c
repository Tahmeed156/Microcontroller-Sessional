#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char rotating = 0;
signed char column = 0;
signed char rotateIndex = 0;
unsigned char rotateIndexCount = 0;

ISR(INT2_vect) {
	rotating = rotating ^ 0b1;
}

int main(void)
{
	char sym[8] = {
		0b11111111,
		0b00000000,
		0b00000000,
		0b00111111,
		0b00111111,
		0b00111111,
		0b00111111,
		0b11111111,
	};
	
	DDRC = 0b11111111;
	DDRD = 0b11111111;	
	MCUCSR = (1<<JTD); 
	MCUCSR = (1<<JTD);
	GICR = (1 << INT2);
	// MCUCSR = (1 << ISC2);
	MCUCSR = MCUCSR | 0b01000000;
	sei();
	
    while (1) {
		column++;
		if (column > 7) 
			column = 0;
		if (rotating) {
			rotateIndexCount++;
			if (rotateIndexCount > 250) {
				rotateIndexCount = 0;
				rotateIndex++;
				if (rotateIndex > 7) 
					rotateIndex = 0;
			}
		}
		
		PORTC = 1 << ((column + rotateIndex) % 8);
		PORTD = sym[column];
		
		_delay_ms(1);
    }
}

