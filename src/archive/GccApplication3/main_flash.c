/*
 * GccApplication3.c
 *
 * Created: 10/14/2018 11:23:29 AM
 * Author : johnston
 */ 
#include <avr/io.h>
#include <util/delay.h>
#ifndef F_CPU
#define F_CPU 1000000UL
#endif

int main(void)
{
	
	DDRB |= 0xFE;
	PORTB &= 0x00;
	while(1)
	{
		PORTB |= 0xFF;
		_delay_ms(500);
		PORTB &= 0x00;
		_delay_ms(2000);
	};
return 0;
}

