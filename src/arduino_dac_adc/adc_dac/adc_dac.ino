#include <MCP492X.h>
#include <SPI.h>
#include <Mcp3208.h>

#define CS_ADC 7 // control chip select on ADC
#define CS_DAC 5 // control chip select on DAC

#define ADC_REF 5000 //ADC reference voltage in mV
#define ADC_CLK     2000  // SPI clock 1.6MHz

MCP3208 myAdc(ADC_REF, CS_ADC);
MCP492X myDac(CS_DAC);

void setup() {

  //Pins
  pinMode(CS_ADC, OUTPUT);
  //pinMode(CS_DAC, OUTPUT);
 
  //ADC Setup
  //SPISettings settings(ADC_CLK, MSBFIRST, SPI_MODE0);
  //SPI.begin();
  //SPI.beginTransaction(settings);

 //DAC Setup
  myDac.begin();
  
}

void loop() {
  
  //Variables
  unsigned int data;

  //Read
  data = myAdc.read(MCP3208::SINGLE_7);
  
  //Write
  myDac.analogWrite(0,0,1,1,(data));

}
