extern "C"
{
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <codegen/SPI.h>
#include "Drivers/interrupts.h"
#include "tasks.h"
}
#include "Drivers/Clock.h"
#include "Drivers/GPIO.h"
#include "Drivers/I2C.h"
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
   gpio.setPinFunction(0, GPIO::pinFunctionAlternate0);
   gpio.setPinFunction(1, GPIO::pinFunctionAlternate0);
   gpio.setPinFunction(18, GPIO::pinFunctionAlternate5);
   gpio.setPinPullDirection(uartTxPin, GPIO::pullDirectionDown);
   gpio.setPinPullDirection(uartRxPin, GPIO::pullDirectionDown);
   gpio.setPinPullDirection(0, GPIO::pullDirectionUp);
   gpio.setPinPullDirection(1, GPIO::pullDirectionUp);
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

   //xTaskCreate(taskBlink, task1Str, 256, &taskStruct, 0, NULL);
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
   Clock pwmClock(Clock::PWMClockBaseAddress);
   pwmClock.setDivisor(100, 0);
   pwmClock.setMASHControl(Clock::MASH1Stage);
   pwmClock.setClockSource(Clock::clockSourcePLLD);
   pwmClock.enable();


   PWM pwm(PWM::PWM0BaseAddress);
   int i = 0;
   uint32_t temperature = 0;
   pwm.setDutyCycle(0, 75);
   pwm.setPWMMode(0);

   pwm.enableChannel(0);
   while(1)
   {
      temperature = temperatureReader.readTemperature();
      xQueueSend(queue, &temperature, 0);

      i++;
      if(i&1)
      {
         gpio.setPinLevel(readyLEDPin, GPIO::pinLevelLow);
      }
      else
      {
         gpio.setPinLevel(readyLEDPin, GPIO::pinLevelHigh);
      }

      if(temperature > 26)
      {
         pwm.setDutyCycle(0, 10);
      }
      else
      {
         pwm.setDutyCycle(0, 75);
      }

      vTaskDelay(500);
   }
}

extern "C" void taskBlink(void *pParam)
{
   GPIO& gpio = GPIO::getSingleton();
   int i = 0;

   while(1)
   {
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

   I2C i2c(I2C::I2C0BaseAddress);
   i2c.setAddress(1);
   i2c.setTransferMode(I2C::transferModeRead);
   i2c.setClockDivider(2500); // 100kHz
   i2c.setDataLength(1);
   //i2c.setClockStretchTimeout(255);
   i2c.clearFIFO();
   i2c.enable();

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
      i2c.startTransfer();
      while(i2c.dataAvailable() && !i2c.checkForError())
      {
         lcd.setCursorPosition(15);
         snprintf(strBuffer, 48, " %d", i2c.read());
         lcd.sendString(strBuffer);
      }
      if(i2c.ackErrorDetected())
      {
         lcd.setCursorPosition(15);
         lcd.sendString(" ack error");
      }
   }
}