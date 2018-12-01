#include <MCP492X.h>
#include <Mcp3208.h>

#define CS_ADC 4 // control chip select on DAC
#define CS_DAC 5 // control chip select on DAC

#define ADC_REF 0 //ADC reference voltage in mV

MCP3208 myAdc(ADC_REF, CS_ADC);
MCP492X myDac(CS_DAC);

void setup() {

  Serial.begin(9600);
  Serial.println("Starting!");

  //Pins
  digitalWrite(CS_ADC, HIGH);
  digitalWrite(CS_DAC, HIGH);

  //SPI
  SPISettings settings(160000, MSBFIRST, SPI_MODE0);
  SPI.begin();
  SPI.beginTransaction(settings);

  //ADC Setup
  //myAdc.calibrate(MCP3208::SINGLE_0);

  //DAC Setup
  myDac.begin();

  //Other
  //analogReference(INTERNAL);
  
}

void loop() {
  
  //Variables
  unsigned int data;

  //Read
  //data = analogRead(A0);
  data = myAdc.read(MCP3208::SINGLE_0);
  //data = myAdc.toAnalog(data);

  Serial.println(data);
  
  //Write
  myDac.analogWrite(0,0,0,1,data);

}
