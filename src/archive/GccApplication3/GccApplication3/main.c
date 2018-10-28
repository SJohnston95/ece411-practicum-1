/*
 * GccApplication3.c
 *
 * Created: 10/14/2018 11:23:29 AM
 * Author : johnston
 */ 

#include <avr/io.h>


int main(void)
{
	int i;
	i = 0;
	 DDRD= 0x1; 
	while (1)
	{
	if (i%10000 == 1)
	{
	PORTD = 0xF;
    /* Replace with your application code */
	}
	else
	{
		PORTD = 0xF;
	}
	}
	return 0;
}

