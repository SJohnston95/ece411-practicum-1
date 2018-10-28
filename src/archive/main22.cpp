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
char input();
char output(char sensorValues);



	
	
int main()
{
	char sensorValues = 0;
	DDRB= (1<<5)|(1<<3)|(1<<1);  //This enables port 5, port 3 and port 2
	SPCR = 0b01110000;  //Configuration in SPCR register
	SPSR |= 0b00000000; //Configuration in SPSR register. Both are for SPI inputs.
	//PORTB &= ~(0b100);
	int data2;
	data2 = 0b10101010;
	

	
	
	while (1)
	{	
		sensorValues = input();
		output(data2); //sends the sensorValue measurement into "output"
		
//		PORTB |= 0b100; //Sets SS to 1, which turns off chip enable on the DAC	
			
	}

return 0;
};

char input()
{
int n = 0;
char sensorValue;
	ADCSRA |= 0b11000000; //1111 enables ADC, ADC conversion, Auto Trigger and an interrupt flag to check if the conversion is finished
	//1100 enables ADC, auto trigger and places the values furthest towards the LSB rather than towards the MSB
	while (n<1)
	{
		if ((ADCSRA & (1 << 4)) > 0) //Checks if the interrupt flag is 1, which will indicate that the data is ready to be read
		{
		sensorValue = ADC;
		sensorValue = sensorValue << 2;
		n = 1;
		}
		
	}
	return sensorValue;
}



char output(char sensorValue)
{
	
	char data = 0;
	data = sensorValue & 0xFF00; //Top half of the 16 bit value
	data = data >> 8;
	data = 0b00001111 & data;
	data = 0b00110000 | data;
	SPDR = data;//Sends data to the output register
	data = sensorValue & 0x00FF;
	_delay_ms(.5);
	SPDR = data; //Sends data to the output register
	
	
	
	return 0;
};