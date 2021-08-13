#define F_CPU 1000000
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "lcd.h"


int main(void) 
{
	float voltage;
	int result;
	char voltage_arr[15];
	DDRB = 0xFF;
	DDRD = 0xFF;
	DDRC = 0xFF;
	ADMUX = 0b00000111; // 4.5, Right, ADC7
	ADCSRA = 0b10000110; // 64
	Lcd4_Init();
	
	while(1)
	{
		// start conversion, loop until end
		ADCSRA |= (1 << ADSC);
		while (ADCSRA & (1 << ADSC)) {;}
		
		// voltage calculation from ADC output
		result = 0;
		result |= (ADCL);
		result |= (ADCH << 8);
		voltage = (result * 4.5) / 1024;
		
		// display in LCD
		dtostrf(voltage, 3, 2, voltage_arr);
		Lcd4_Set_Cursor(1, 1);
		Lcd4_Write_String("Voltage: ");
		Lcd4_Write_String(voltage_arr);
	}
}

