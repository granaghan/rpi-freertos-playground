#include <FreeRTOS.h>
#include <task.h>

#include <codegen/SPI.h>
#include "Drivers/interrupts.h"
#include "Drivers/gpio.h"
#include "tasks.h"

void task1(void *pParam) {

	int i = 0;
	while(1) {
		i++;
		//SetGpio(16, i&1);
		vTaskDelay(1000);
	}
}

void task2(void *pParam) {

	int i = 0;
	while(1) {
		i++;
		vTaskDelay(100);
		//SetGpio(16, 0);
		vTaskDelay(100);
	}
}


/**
 *	This is the systems main entry, some call it a boot thread.
 *
 *	-- Absolutely nothing wrong with this being called main(), just it doesn't have
 *	-- the same prototype as you'd see in a linux program.
 **/
void main(void) {

	DisableInterrupts();
	InitInterruptController();

	SetGpioFunction(16, 1);			// RDY led
	SetGpioFunction(15, 0x4);		// UART
	SetGpioFunction(14, 0x4);		// UART
   PudGpio(15, PULL_DOWN);
   PudGpio(14, PULL_DOWN);

	xTaskCreate(task1, "LED_0", 128, NULL, 0, NULL);
	xTaskCreate(task2, "LED_1", 128, NULL, 0, NULL);
   xTaskCreate(task3, "AAAAA", 128, NULL, 0, NULL);

	vTaskStartScheduler();

	/*
	 *	We should never get here, but just in case something goes wrong,
	 *	we'll place the CPU into a safe loop.
	 */
	while(1) {
		;
	}
}
