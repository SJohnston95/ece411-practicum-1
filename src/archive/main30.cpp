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
	char sensorValues = 0;
	DDRB |= (1<<5)|(1<<3)|(1<<2)|(1<<1);  //This enables port 5, port 3 and port 2
	PORTB &= ~(0b100);
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPOL)|(1<<CPHA)|(1<<SPR0);  //Configuration in SPCR register	

	
	
	while (1)
	{	
		PORTB &= ~(0b100); //Sets SS to 1, which turns off chip enable on the DAC
		sensorValues = input();
		output(sensorValues); //sends the sensorValue measurement into "output"
		PORTB |= 0b100; //Sets SS to 1, which turns off chip enable on the DAC	
			
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
		while(!(SPSR & (1<<SPIF) )); //wait until SPSR has finished
	SPDR = sensorValue; //Sends data to the output register
	
	
	return 0;
};





