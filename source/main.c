#include <FreeRTOS.h>
#include <task.h>

#include <codegen/SPI.h>
#include "Drivers/interrupts.h"
#include "tasks.h"

void task2(void *pParam) {

	int i = 0;
	while(1) {
		i++;
		vTaskDelay(100);
		//SetGpio(16, 0);
		vTaskDelay(100);
	}
}

void main(void)
{

   initializePlatform();
	DisableInterrupts();
	InitInterruptController();

	xTaskCreate(task1, "LED_0", 256, NULL, 0, NULL);
	//xTaskCreate(task2, "LED_1", 4096, NULL, 0, NULL);
   uint32_t ret = xTaskCreate(task3, "AAAAA", 256, NULL, 0, NULL);

	vTaskStartScheduler();

	while(-1);
}
