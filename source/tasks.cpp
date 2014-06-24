extern "C"
{
#include <FreeRTOS.h>
#include <task.h>

#include <codegen/SPI.h>
#include "Drivers/interrupts.h"
#include "tasks.h"
}
#include "Drivers/UART.h"
#include "Drivers/GPIO.h"
#include "Drivers/SPI.h"
#include "Peripherals/SparkfunLCD.h"
#include "constants.h"

extern "C" void initializePlatform()
{
   GPIO& gpio = GPIO::getSingleton();
   gpio.setPinFunction(readyLEDPin, GPIO::pinFunctionOutput);
   gpio.setPinFunction(uartTxPin, GPIO::pinFunctionAlternate0);
   gpio.setPinFunction(uartRxPin, GPIO::pinFunctionAlternate0);
   gpio.setPinFunction(7, GPIO::pinFunctionAlternate0);
   gpio.setPinFunction(8, GPIO::pinFunctionAlternate0);
   gpio.setPinFunction(9, GPIO::pinFunctionAlternate0);
   gpio.setPinFunction(10, GPIO::pinFunctionAlternate0);
   gpio.setPinFunction(11, GPIO::pinFunctionAlternate0);
   gpio.setPinPullDirection(uartTxPin, GPIO::pullDirectionDown);
   gpio.setPinPullDirection(uartRxPin, GPIO::pullDirectionDown);
}

char getHexChar(uint8_t c)
{
   if(c >= 0 && c <= 9)
   {
      return c + '0';
   }
   if(c >= 10 && c <= 16)
   {
      return (c - 10) + 'A';
   }
   return 'x';
}

extern "C" void task3(void *pParam)
{
   uint32_t data = 0;
   GPIO& gpio = GPIO::getSingleton();
   SPI spi(SPI::SPI0BaseAddress);
   spi.setChannelChipSelectPolarity(0, SPI::polarityLow);
   spi.setChipSelectPolarity(SPI::polarityLow);
   spi.setClockRate(976000);
   spi.setTransferActive(true);

   vTaskDelay(1000);
   UART uart(UART::UART0BaseAddress);
   SparkfunLCD lcd(uart);
   lcd.setBacklightBrightness(20);

   while(1)
   {
      //lcd.sendString("123");
      spi.assertChipSelect(0);
      spi.writeData(0);
      spi.writeData(0);
      spi.writeData(0);
      spi.writeData(0);

      lcd.sendCharacter('x');
      data = spi.readData();
      lcd.sendCharacter(data >> 4);
      lcd.sendCharacter(data & 0xF);
      data = spi.readData();
      lcd.sendCharacter(data >> 4);
      lcd.sendCharacter(data & 0xF);
      data = spi.readData();
      lcd.sendCharacter(data >> 4);
      lcd.sendCharacter(data & 0xF);
      //lcd.sendCharacter(spi.readData());
      //lcd.sendCharacter(spi.readData());
      lcd.sendCharacter(' ');
      if(spi.dataAvailable())
      {
         gpio.setPinLevel(readyLEDPin, GPIO::pinLevelLow);
      }

		vTaskDelay(1000);
      spi.assertChipSelect(1);
		vTaskDelay(1000);
	}
}