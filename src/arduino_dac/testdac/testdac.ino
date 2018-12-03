#include <MCP492X.h>

#define CS_DAC 5 // control chip select on DAC

MCP492X myDac(CS_DAC);

void setup() {
  // put your setup code here, to run once:
  myDac.begin();
  //analogReference(INTERNAL);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int data;
  data = analogRead(A0);
  myDac.analogWrite(0,0,0,1,data);
}
