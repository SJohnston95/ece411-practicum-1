/*
 * GccApplication3.c
 *
 * Created: 10/14/2018 11:23:29 AM
 * Author : johnston
 */ 

#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <util/delay.h>
#include <avr/interrupt.h>
char input();
char output(char sensorValues);
//void ISR(void SPI_STC_vect);

/*
void ISR(SPI_STC_vect)
{
int	Int_Check = SPSR & (1>>SPIF);
if (Int_Check > 1)
{
	
	_delay_ms(100);
	PORTB |= 0b10;
	_delay_ms(100);
	PORTB &= ~(0b10);
	SPSR|=(1>>SPIF);
}

};
*/
	
	
int main()
{
	unsigned short sensorValues = 0;
	DDRB |= (1<<5)|(1<<3)|(1<<2)|(1<<1);  //This enables port 5, port 3 and port 2
	PORTB &= ~(0b100);
	SPCR = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(0<<SPR0)|(0<<SPR1)|(1<<DORD);  //Configuration in SPCR register	
	ADMUX = (0<<REFS1)|(1<<REFS0);
	ADCSRA |= (1<<ADPS1);

	
	while (1)
	{	
		sensorValues = input();
		
		output(sensorValues); //sends the sensorValue measurement into "output"
		
		
	
	
	
	}
return 0;
};

char input()
{
int n = 0;
char sensorValue;
	ADMUX = (ADMUX & 0xF8);
	ADCSRA |= (1<<ADSC); //1111 enables ADC, ADC conversion, Auto Trigger and an interrupt flag to check if the conversion is finished
	//1100 enables ADC, auto trigger and places the values furthest towards the LSB rather than towards the MSB
	while (ADCSRA & (1<<ADSC));
	
	sensorValue = ADCL;
	sensorValue = sensorValue*4;
	return sensorValue;
}



char output(char sensorValue)
{
/*
I am sending the first half of the data first in little endian mode, then I send the second half in the same mode. 

*/
	char data = 0;
	PORTB &= ~(0b100); //Sets SS to 0, which turns on chip enable on the DAC
	data = sensorValue & 0x00FF;
	SPDR = data;
	while(!(SPSR & (1<<SPIF))); //wait until SPSR has finished
	

	data = sensorValue & 0xFF00; //Top half of the 16 bit value
//	data = data >> 8;
	data = 0b00001111 & data;
	data = 0b00110000;
		SPDR = data;//Sends data to the output register
		while(!(SPSR & (1<<SPIF) )); //wait until SPSR has finished
	PORTB |= 0b100; //Sets SS to 1, which turns off chip enable on the DAC
	
	return 0;
};





