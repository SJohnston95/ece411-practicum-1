#include <MCP492X.h>

#define CS_DAC 5 // control chip select on DAC
#define CS_ADC 4
#define DATAOUT 11//MOSI
#define DATAIN  12//MISO
#define SPICLOCK  13//Clock

int read_adc(int channel);

MCP492X myDac(CS_DAC);

void setup() {
  
  //set pin modes 
  pinMode(CS_ADC, OUTPUT); 
  pinMode(DATAOUT, OUTPUT); 
  pinMode(DATAIN, INPUT); 
  pinMode(SPICLOCK, OUTPUT); 
  //disable device to start with 
  digitalWrite(CS_ADC,HIGH); 
  digitalWrite(DATAOUT,LOW); 
  digitalWrite(SPICLOCK,LOW); 

  myDac.begin();
  SPI.end();

  //Serial.begin(9600);
  
}

void loop() {

  //Varliables
  unsigned int data;

  data = read_adc(1); 
  //Serial.println(data,DEC); 

  SPI.begin();
  myDac.analogWrite(0,0,0,1,data);
  SPI.end();
}

int read_adc(int channel){
  int adcvalue = 0;
  byte commandbits = B11000000; //command bits - start, mode, chn (3), dont care (3)

  //allow channel selection
  commandbits|=((channel-1)<<3);

  digitalWrite(CS_ADC,LOW); //Select adc
  // setup bits to be written
  for (int i=7; i>=3; i--){
    digitalWrite(DATAOUT,commandbits&1<<i);
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);    
  }

  digitalWrite(SPICLOCK,HIGH);    //ignores 2 null bits
  digitalWrite(SPICLOCK,LOW);
  digitalWrite(SPICLOCK,HIGH);  
  digitalWrite(SPICLOCK,LOW);

  //read bits from adc
  for (int i=11; i>=0; i--){
    adcvalue+=digitalRead(DATAIN)<<i;
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);
  }
  digitalWrite(CS_ADC, HIGH); //turn off device
  return adcvalue;
}
