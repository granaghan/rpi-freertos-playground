extern "C"
{
#include <FreeRTOS.h>
#include <task.h>

#include <codegen/SPI.h>
#include "Drivers/interrupts.h"
#include "Drivers/gpio.h"
#include "tasks.h"
}
#include "Drivers/UART.h"
#include "Peripherals/SparkfunLCD.h"

extern "C" void task3(void *pParam)
{
   vTaskDelay(1000);
   UART uart(UART::UART0BaseAddress);
   SparkfunLCD lcd(uart);
   lcd.setBacklightBrightness(20);

   while(1)
   {
      lcd.sendString("123");
		vTaskDelay(200);
	}
}