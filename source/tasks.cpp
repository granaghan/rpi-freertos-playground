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
#include "Peripherals/MAX31855.h"
#include "constants.h"
#include <stdio.h>

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
   //gpio.setPinPullDirection(7, GPIO::pullDirectionUp);
   //gpio.setPinPullDirection(8, GPIO::pullDirectionUp);
   //gpio.setPinPullDirection(9, GPIO::pullDirectionUp);
   //gpio.setPinPullDirection(10, GPIO::pullDirectionUp);
   //gpio.setPinPullDirection(11, GPIO::pullDirectionUp);
   //gpio.setPinLevel(readyLEDPin, GPIO::pinLevelLow);
}

extern "C" void statusOn()
{
   GPIO& gpio = GPIO::getSingleton();
   gpio.setPinLevel(readyLEDPin, GPIO::pinLevelLow);
}

extern "C" void statusOff()
{
   GPIO& gpio = GPIO::getSingleton();
   gpio.setPinLevel(readyLEDPin, GPIO::pinLevelHigh);
}


char getHexChar(uint8_t nibble)
{
   switch(nibble)
   {
      case 0:
         return '0';
      case 1:
         return '1';
      case 2:
         return '2';
      case 3:
         return '3';
      case 4:
         return '4';
      case 5:
         return '5';
      case 6:
         return '6';
      case 7:
         return '7';
      case 8:
         return '8';
      case 9:
         return '9';
      case 10:
         return 'A';
      case 11:
         return 'B';
      case 12:
         return 'C';
      case 13:
         return 'D';
      case 14:
         return 'E';
      case 15:
         return 'F';
      default:
         return '-';
   }
}

extern "C" void task1(void *pParam)
{
   GPIO& gpio = GPIO::getSingleton();
	int i = 0;
	while(1) {
		i++;
		if(i&1)
      {
         gpio.setPinLevel(readyLEDPin, GPIO::pinLevelLow);
      }
      else
      {
         gpio.setPinLevel(readyLEDPin, GPIO::pinLevelHigh);
      }
		vTaskDelay(500);
	}
}

extern "C" void task3(void *pParam)
{
   statusOn();
   GPIO& gpio = GPIO::getSingleton();
   gpio.setPinLevel(readyLEDPin, GPIO::pinLevelHigh);
   UART uart(UART::UART0BaseAddress);
   SPI spi(SPI::SPI0BaseAddress);
   spi.setChipSelectPolarity(SPI::polarityLow);
   spi.setClockRate(976000);

   vTaskDelay(1000);
   SparkfunLCD lcd(uart);
   MAX31855 temperatureReader(spi, 0, lcd);

   lcd.setBacklightBrightness(20);
   lcd.enableCursorBlink(true);

   while(1)
   {
      //gpio.setPinLevel(readyLEDPin, GPIO::pinLevelHigh);
      temperatureReader.readTemperature();
      lcd.sendCharacter(' ');
      //gpio.setPinLevel(readyLEDPin, GPIO::pinLevelLow);

      if(spi.dataAvailable())
      {
         //gpio.setPinLevel(readyLEDPin, GPIO::pinLevelLow);
      }

		vTaskDelay(500);
	}
}