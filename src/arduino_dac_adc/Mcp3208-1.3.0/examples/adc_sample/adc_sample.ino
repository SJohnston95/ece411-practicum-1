/**
 * Basic ADC reading example.
 * - connects to ADC
 * - reads value from channel
 * - converts value to analog voltage
 */

#include <SPI.h>
#include <Mcp3208.h>

#define SPI_CS    	4 		   // SPI slave select
#define ADC_VREF    5000     // 3.3V Vref
#define ADC_CLK     1600000  // SPI clock 1.6MHz


MCP3208 adc(ADC_VREF, SPI_CS);

void setup() {

  // configure PIN mode
  pinMode(SPI_CS, OUTPUT);

  // set initial PIN state
  digitalWrite(SPI_CS, HIGH);

  // initialize serial
  Serial.begin(9600);

  // initialize SPI interface for MCP3208
  SPISettings settings(ADC_CLK, MSBFIRST, SPI_MODE0);
  SPI.begin();
  SPI.beginTransaction(settings);
}

void loop() {

  uint32_t t1;
  uint32_t t2;

  // start sampling

  uint16_t raw = adc.read(MCP3208::SINGLE_0);

  // readed value
  Serial.print("value: ");
  Serial.println(raw);


}
