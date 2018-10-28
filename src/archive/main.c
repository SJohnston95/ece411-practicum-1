/*
 * GccApplication3.c
 *
 * Created: 10/14/2018 11:23:29 AM
 * Author : johnston
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 4000000UL
int main(void)
{
	DDRC= 0xFF;
	while(1)
	{
		PORTC = 0xFF;
		_delay_ms(1000);
		PORTC = 0x00;
		_delay_ms(1000);
	}
	return 0;

}

