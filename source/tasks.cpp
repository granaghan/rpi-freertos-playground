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

extern "C" void task3(void *pParam)
{
   uint32_t i = 0;
   UART uart(reinterpret_cast<uint8_t*>(0x20201000));//UART::UART0BaseAddress);
   vTaskDelay(5000);
   uart.setBaudRate(9600);
   uart.setWordSize(8);
   uart.setParity(UART::parityNone);
   uart.setStopBitCount(1);
   uart.enableTransmit(true);
   while(1)
   {
      if(uart.txFIFOFull())
      {
         SetGpio(16, 1);
      }
      else
      {
         SetGpio(16, 0);
      }
		uart.sendByte(0x7c);
      uart.sendByte(128);
		vTaskDelay(1000);
      uart.sendByte(0x7c);
      uart.sendByte(157);
      vTaskDelay(1000);
      uart.sendByte('A');
	}
}