/*
 * GccApplication3.c
 *
 * Created: 10/14/2018 11:23:29 AM
 * Author : johnston
 */ 

#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	int sensorValue = 0;
	char data = 0;
	int n = 0;
	int baud;
	ADMUX  |= 0b01100000;
	UCSR0C |= 0b11000000; //Page 260 (USART control and status register 0C on the atmel datasheet)
	UBRR0 =0;
	//XCK0_DDR |= (1<<XCK0);
	UCSR0B = (1 <<RXEN0)|(1<<TXEN0);
	baud = 60000; //Clock cycle divided by 2
	UBRR0= 0;
	DDRB = DDRB | 0b110;
	PORTB &= ~(0b100);
	while (1)
	{
		
		
		ADCSRA |= 0b11100000; //1111 enables ADC, ADC conversion, Auto Trigger and an interrupt flag to check if the conversion is finished
		
			while (n < 1)
			{	 //Checks ADCSRA, which is the status and command register
				if ((ADCSRA & (1 << 4)) > 0) //Checks if the interrupt flag is 1, which will indicate that the data is ready to be read
					{
					sensorValue = ADCH;
					sensorValue = sensorValue << 4;
					n = 1;
						_delay_ms(100);
						PORTB |= 0b10;
						_delay_ms(100);
						PORTB &= ~(0b10);
					}		
			}
			n = 0;
		PORTB = PORTB & ~(0x100); //Sets SS to 0, which t urns on chip enable on DAC
		data = sensorValue & 0xFF00; //Top half of the 16 bit value
		sensorValue = sensorValue >> 8;
		data = 0b00001111 & data;
		data = 0b00110000 | data;			
		UDR0 = data;
		//Spi.transfer(data);
		data = sensorValue & 0x00FF;
		//Spi.transfer(data);
		PORTB = PORTB | 0x100; //Sets SS to 1, which turns off chip enable on the DAC
		
	
	}

return 0;
}