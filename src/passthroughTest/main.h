//==============================================================================
//Header: passthroughTest (main.cpp)
//Author: Jordan Bergmann
//
//Description: Attempts to test straight passthrough of audio, starting as an
//  analog signal into an ATMEGA48A or ATMEGA328P ADC pin, which converts the
//  signal to digital and sends it via SPI to an external MCP4921 DAC.
//
//  Written expecting compilation in Atmel Studio, for an AVR Dragon, for
//  an ATMEGA48A or ATMEGA328P.
//==============================================================================

//Defines:
#define F_CPU 1000000UL //Tells compiler expected CPU speed, does not change actual speed.

//Includes:
#include <util/delay.h>
#include <avr/interrupt.h>

//Function Declarations

//==============================================================================
//Function: setup
//Description: Initiaizes chip settings.
//
//Return(void): N/A
//==============================================================================
void setup();

//==============================================================================
//Function: input
//Description: Takes analog input from outside, converts it to digital.
//
//Return(unsigned char): Top 8 bits of converted analog input.
//==============================================================================
unsigned char input();

//==============================================================================
//Function: output
//Description: Sends eight bit converted analog values to external DAC (MCP4921)
//	using SPI.
//
//Argument list:
//	(unsigned char)sensorValue: Digital value to send to DAC for output.
//
//Return(void): N/A
//==============================================================================
void output(unsigned char sensorValue);


