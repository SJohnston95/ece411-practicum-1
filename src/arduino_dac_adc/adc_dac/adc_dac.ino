#include <MCP492X.h>
#include <SPI.h>
#include <Mcp3208.h>

#define CS_ADC 4 // control chip select on DAC
#define CS_DAC 5 // control chip select on DAC

#define ADC_REF 000 //ADC reference voltage in mV
#define ADC_CLK     1600000  // SPI clock 1.6MHz

MCP3208 myAdc(ADC_REF, CS_ADC);
MCP492X myDac(CS_DAC);

void setup() {

  Serial.begin(9600);
  Serial.println("Starting!");

  //Pins
  pinMode(CS_ADC, OUTPUT);
  pinMode(CS_DAC, OUTPUT);

  //ADC Setup
  //myAdc.calibrate(MCP3208::SINGLE_0);
  SPISettings settings(ADC_CLK, MSBFIRST, SPI_MODE0);
  SPI.begin();
  SPI.beginTransaction(settings);

  //DAC Setup
  myDac.begin();
  
}

void loop() {
  
  //Variables
  uint16_t data;

  //Read
  //data = analogRead(A0);
  data = myAdc.read(MCP3208::SINGLE_0);

  Serial.println(data);
  
  //Write
  myDac.analogWrite(0,0,0,1,data);

}
