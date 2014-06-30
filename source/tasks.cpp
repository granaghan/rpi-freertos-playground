extern "C"
{
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <codegen/SPI.h>
#include "Drivers/interrupts.h"
#include "tasks.h"
}
#include "Drivers/GPIO.h"
#include "Drivers/PWM.h"
#include "Drivers/SPI.h"
#include "Drivers/UART.h"
#include "Peripherals/SparkfunLCD.h"
#include "Peripherals/MAX31855.h"
#include "constants.h"
#include <stdio.h>

const signed char* task1Str = reinterpret_cast<const signed char*>("task1");
const signed char* task2Str = reinterpret_cast<const signed char*>("task2");

typedef struct
{
   xQueueHandle queueHandle;
   SparkfunLCD& lcdRef;
   MAX31855& max31855Ref;
} TaskStruct;

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
   gpio.setPinFunction(18, GPIO::pinFunctionAlternate5);
   //gpio.setPinPullDirection(7, GPIO::pullDirectionUp);
   //gpio.setPinPullDirection(8, GPIO::pullDirectionUp);
   //gpio.setPinPullDirection(9, GPIO::pullDirectionUp);
   //gpio.setPinPullDirection(10, GPIO::pullDirectionUp);
   //gpio.setPinPullDirection(11, GPIO::pullDirectionUp);
   //gpio.setPinLevel(readyLEDPin, GPIO::pinLevelLow);
}

extern "C" void spawnTasks()
{
   xQueueHandle temperatureQueue = xQueueCreate(10, sizeof(uint32_t));
   UART uart(UART::UART0BaseAddress);
   SPI spi(SPI::SPI0BaseAddress);
   spi.setChipSelectPolarity(SPI::polarityLow);
   spi.setClockRate(976000);

   SparkfunLCD lcd(uart);
   MAX31855 temperatureReader(spi, 0);
   TaskStruct taskStruct = {temperatureQueue, lcd, temperatureReader};

	xTaskCreate(task1, task1Str, 256, &taskStruct, 0, NULL);
   xTaskCreate(task3, task2Str, 256, &taskStruct, 0, NULL);
   vTaskStartScheduler();
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

extern "C" void task1(void *pParam)
{
   GPIO& gpio = GPIO::getSingleton();
   MAX31855& temperatureReader = reinterpret_cast<TaskStruct*>(pParam)->max31855Ref;
   xQueueHandle queue = reinterpret_cast<TaskStruct*>(pParam)->queueHandle;
   PWM pwm(PWM::PWM0BaseAddress);
   int i = 0;
   uint32_t temperature = 0;
	
   pwm.enableChannel(0);
   while(1)
   {
      temperature = temperatureReader.readTemperature();
      xQueueSend(queue, &temperature, 0);
      pwm.setDutyCycle(0, 100);

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

   SparkfunLCD& lcd = reinterpret_cast<TaskStruct*>(pParam)->lcdRef;
   MAX31855& temperatureReader = reinterpret_cast<TaskStruct*>(pParam)->max31855Ref;
   xQueueHandle queue = reinterpret_cast<TaskStruct*>(pParam)->queueHandle;

   uint32_t temperature = 0;
   char strBuffer[48];

   lcd.setBacklightBrightness(20);
   lcd.enableCursorBlink(true);

   while(1)
   {
      if(xQueueReceive(queue, &temperature, portMAX_DELAY))
      {
         snprintf(strBuffer, 48, "%d", temperature);
         lcd.clear();
         lcd.sendString(strBuffer);
      }
	}
}