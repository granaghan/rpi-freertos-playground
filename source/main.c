#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include "Drivers/interrupts.h"
#include "tasks.h"

void main(void)
{

   initializePlatform();
   DisableInterrupts();
   InitInterruptController();
   spawnTasks();

   while(-1);
}
