/*
 * audioIO.cpp
 *
 */ 

#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <util/delay.h>
#include <avr/interrupt.h>

//=== Prototypes ========
char input();
int out2DAC(uint16_t data);
void adc_init();
uint16_t adc_read();
void SPI_init();

int main()
{	
	unsigned short sensorValues = 0;
	//This sets pins 1 and 2 on port B as outputs
    DDRB |= (1<<2)|(1<<1);  
	
    PORTB &= 0b100;
	
    SPI_init();
    adc_init();
	
    while (1)
    {	
        sensorValues = adc_read();
        out2DAC(sensorValues); //sends the sensorValue measurement into "output"
    }

    return 0;
};

void SPI_init()
{
	// Set MOSI and SCK as output
	DDRB |= (1<<5)|(1<<3);
	
	// Configuring the SPI control register bits:
	// 6: SPE0 - write 1 to enable SPI
	// 5: DORD0 - 1 to transmit LSB first, 0 to transmit MSB first
	// 4: MSTR0 - 1 to set MCU as master
	// 3: CPOL0 - 1 to set SCK high when idle
	// 2: CPHA0 - clock phase --> 0 for leading eadge to sample, trailing to setup
	// 1:0 SPR0 - clock rate select --> 00 for oscillator freqency /4
	SPCR = (1<<SPE)|(0<<DORD)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(0<<SPR1)|(0<<SPR0);
	
	return;
}

// Initialize ADC by setting voltage reference, enabling, and 
// setting the prescaler to 128. 
void adc_init()
{
    // AREF, internal Vref turned off by setting bits 7:6 to zero
    ADMUX &= ~((1<<REFS0)|(1<<REFS1));

    // ADC Enable and prescaler of 128
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

// Reads ADC0
uint16_t adc_read()
{
    // Clear bits 3:0 to select channel 0 on ADC --> ADC0
    ADMUX = (ADMUX & 0xF8); 

    // start single convertion by writing '1' to ADSC
    // bit 6 for ADC Start Conversion
    ADCSRA = (1 << ADSC);

    // wait for conversion to complete
    // ADSC becomes '0' automatically after conversion is complete
    while(ADCSRA & (1<<ADSC));
    return (ADC);
}

// SPI communication as specified in page 227 of data sheet.
// Master initiates communication by pulling SS of desired slave low.
// Then both slave and master prepare data in their respective registers.
// Then Master generates required clock pulses on SCK to interchange data.
//
// DAC expects 16 bit words when writing: 
// 4 config bits followed by 12 bits of data
//
int out2DAC(uint16_t data)
{
    //Sets SS to 0, which turns on chip select on the DAC
	PORTB &= ~(0b100); 
	
    // Config bits:
    // 15 = 0 to write to DAC register
    // 14 = 1 to enable buffer for Vref
    // 13 = 1 for 1x gain
    // 12 = 1 for active mode operation
    data &= ~(1000 << 12);
    
    // send first byte as top half of data with config bits
	SPDR = (data >> 8);
	while(!(SPSR & (1<<SPIF))); //wait until SPSR has finished
	
    // send next byte as bottom half of data
	SPDR = (data & 0xFF);
	while(!(SPSR & (1<<SPIF) )); //wait until SPSR has finished
    
    //Sets SS to 1, which turns off chip enable on the DAC
	PORTB |= 0b100; 
	
	return 0;
}
