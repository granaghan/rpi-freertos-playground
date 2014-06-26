#include "Peripherals/MAX31855.h"
#include <stdio.h>


MAX31855::MAX31855(SPI& spi, uint8_t chipSelectLine, SparkfunLCD& lcd):
   spi(spi),
   chipSelectLine(chipSelectLine),
   lcd(lcd)
{
   spi.setChannelChipSelectPolarity(chipSelectLine, SPI::polarityLow);
   spi.setTransferActive(true);
}

MAX31855::~MAX31855(){}

extern char getHexChar(uint8_t);
static char str[255];
uint32_t MAX31855::readTemperature()
{
   uint32_t data = 0;

   spi.assertChipSelect(chipSelectLine);
   spi.writeData(0xAA);
   spi.writeData(0xAA);
   spi.writeData(0xAA);
   spi.writeData(0xAA);

   lcd.clear();

   data = spi.readData();
   lcd.sendCharacter(getHexChar(data>>4));
   lcd.sendCharacter(getHexChar(data&0xF));
   lcd.sendCharacter(' ');

   data = (data << 8) | spi.readData();
   lcd.sendCharacter(getHexChar(data>>4));
   lcd.sendCharacter(getHexChar(data&0xF));
   lcd.sendCharacter(' ');

   data = (data << 8) | spi.readData();
   lcd.sendCharacter(getHexChar(data>>4));
   lcd.sendCharacter(getHexChar(data&0xF));
   lcd.sendCharacter(' ');

   data = (data << 8) | spi.readData();
   lcd.sendCharacter(getHexChar(data>>4));
   lcd.sendCharacter(getHexChar(data&0xF));
   lcd.sendCharacter(' ');


   // data = (data << 8) | spi.readData();
   // data = (data << 8) | spi.readData();
   // data = (data << 8) | spi.readData();
   // data = (data << 8) | spi.readData();
   data = data >> 20;
   if(data & (1<<11))
   {
      data |= ~(0x7FF);
   }
   sprintf(str, "%d", data);
   lcd.clear();
   lcd.sendString(str);
   //for(char* s = str; *s; ++s)
   //{
      //lcd.sendCharacter(*s);
   //}

   //sprintf(str, "0x%X ", data);
   //lcd.sendString(str);

   //sprintf(str, "0x%X ", data);
   //lcd.sendString(str);


   spi.assertChipSelect(3);

   return 0;
}
