#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRC = 0b11000111;
	DDRA = 0b00000000;
	unsigned char inc = 0b1;
	unsigned char count = 0;
	PORTC = PORTC | (inc << 2);
	
	while (1) 
	{
		unsigned char in = PINA;
		in = in ^ 0b11;
		
		if (in & 0b1) {
			(inc & 0b1)? count++: count--;
			if (count == 16) count = 0;
			else if (count == -1) count = 15;
			
			unsigned char setBit = 0;
			setBit = setBit | (count & 0b00001100);
			setBit = setBit << 4;
			setBit = setBit | (inc << 2);
			setBit = setBit | (count & 0b00000011);
			
			PORTC = setBit;
			_delay_ms(500);
		}
		if (in & 0b10) {
			inc = inc ^ 0b1;
			PORTC = PORTC ^ 0b100;
			_delay_ms(500);
		}
	}
}

