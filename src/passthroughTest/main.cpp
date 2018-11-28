//==============================================================================
//Main: passthroughTest
//Author: Jordan Bergmann
//
//Description: Attempts to test straight passthrough of audio, starting as an
//  analog signal into an ATMEGA48A or ATMEGA328P ADC pin, which converts the
//  signal to digital and sends it via SPI to an external MCP4921 DAC.
//
//  Written expecting compilation in Atmel Studio, for an AVR Dragon, for
//  an ATMEGA48A or ATMEGA328P.
//==============================================================================

void main() {

	//Variables:
	unsigned char sensorValue; //Converted analog value.

	//Initialize settings.
	setup();

	//Repeatedly read from the ADC and write the output to DAC.
	while(true){
		sensorValue = input();
		output(sensorValue);
	}

}

//==============================================================================
//Function: setup
//Description: Initiaizes chip settings.
//
//Return(void): N/A
//==============================================================================
void setup() {

	//Enable port 5, port 3 and port 2
	DDRB |= (1<<5)|(1<<3)|(1<<2)|(1<<1);
	PORTB &= ~(0b100);

	//Configure registers. ?NEEDS EXPLANATION FOR EACH?
	SPCR = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(0<<SPR0)|(0<<SPR1)|(1<<DORD);
	ADMUX = (1<<REFS1)|(1<<REFS0)|(1<<ADLAR);
	ADCSRA |= (1<<ADEN)|(1<<ADPS1);

}

//==============================================================================
//Function: input
//Description: Takes analog input from outside, converts it to digital.
//
//Return(char): Top 8 bits of converted analog input.
//==============================================================================
unsigned char input() {

	//Variables:
	unsigned char sensorValue;

	//Do ?SOMETHING?
	ADMUX = (ADMUX & 0xF8);
	ADCSRA |= (1<<ADSC);
	//?USEFUL COMMENTS?
	//1111 enables ADC, ADC conversion, Auto Trigger and an interrupt flag to check if the conversion is finished
	//1100 enables ADC, auto trigger and places the values furthest towards the LSB rather than towards the MSB
	
	//Wait for ?SOMETHING?
	while (ADCSRA & (1<<ADSC)) {
		//NOP
	}
	
	sensorValue = ADCH; //Reads only the high 8 bits (losing 2 bits of accuracy)

	return sensorValue;

}

//==============================================================================
//Function: output
//Description: Sends eight bit converted analog values to external DAC (MCP4921)
//	using SPI.
//
//Argument list:
//	(char)sensorValue: Digital value to send to DAC for output.
//
//Return(void): N/A
//==============================================================================
void output(unsigned char sensorValue) {

	//I am sending the first half of the data first in little endian mode,
	//	then I send the second half in the same mode.

	//Variables:
	unsigned char sensorValueTop;
	unsigned char sensorValueBottom;
	unsigned char data;

	//Separate eight bit signal into two values for the input registers.
	sensorValueTop = (sensorValue & 0xF0) >> 4;
	sensorValueBottom = (sensorValue & 0x0F) << 3 ;
	
	PORTB &= ~(0b100); //Sets SS to 0, which turns on chip enable on the DAC
	SPDR = sensorValueBottom;

	//wait until SPSR has finished
	while(!(SPSR & (1<<SPIF))){
		//NOP
	};
	
	//Sends data to the output register
	SPDR = 0b00100000 | sensorValueTop; //Upper 4 are config bits.

	//wait until ?SPSR? has finished
	while(!(SPSR & (1<<SPIF))) {
		//NOP
	}

	//Set SS to 1, which turns off chip enable on the DAC
	PORTB |= 0b100;
	
	return;

}