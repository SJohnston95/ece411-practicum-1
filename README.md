# ECE411 Practicum 
The main goal of this project is to gain project management experience, and pass ECE411.

### Resources
- [Github Markdown Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)
- [Atmel 8-bit AVR controller](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8271-8-bit-AVR-Microcontroller-ATmega48A-48PA-88A-88PA-168A-168PA-328-328P_datasheet_Complete.pdf)

### Live Notes
- [Meeting Notes](https://docs.google.com/document/d/19kvDTP8waEN3RQ6yVrNDx6z7Xe4eh67vW1i40oPSDoY/edit?usp=sharing)
- [Bill of Materials](https://docs.google.com/spreadsheets/d/1W5p3Xew4WHdP0dK88rSV139m2ax4RcH9-pE1J-V8YP8/edit?usp=sharing)

### AVR Pin programming
How to connect the ATmega to the AVR Dragon can be found on page 62 of the [pdf for Atmel
AVR
Dragon](https://github.com/philiparola/ece411-practicum/blob/master/datasheets/atmel-42723-avr-dragon_userguide.pdf)

[Code to program the ATmega](http://www.avr-tutorials.com/digital/about-avr-8-bit-microcontrollers-digital-io-ports)

### Programming ATMEGA328 onboard with AVR Dragon
Using the Arduino IDE go to 'sketch/export compiled binary'.
This will compile your code and output it to a pair of *.hex files in the code directory.

We will be using the *.hex files that does not include a bootloader.

In Ateml Studio, go to 'Tools/Device Programming'. Select 'AVR Dragon' as the tool, 'ATmega328P' as the device, and 'ISP' as the interface, click apply, then when it accept that, click 'read' under device signature.

If it reads a device signature the device is correctly plugged in, now go to the 'Fuses' menu on the left. Uncheck the checkbox corresponding to 'LOW.CKDIV8'. This disables the clock divider that lowers the internal clock speed.

If you would like to enable output of the internal clock to pin 14 for power testing, check 'LOW.CKOUT'.

When done setting fuses, click 'program' so set the fuses on the chip.

Now go to the 'Memories' menu. Under 'Flash' use the file browser to navigate to the *.hex file you compiled earlier, and click 'Program' to program the chip.

#ADC contact
http://maxembedded.com/2011/06/the-adc-of-the-avr/

#SPI connections
http://maxembedded.com/2013/11/the-spi-of-the-avr/#Master_Slave
