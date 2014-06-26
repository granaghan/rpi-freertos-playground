#ifndef TASKS_H_
#define TASKS_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include <task.h>

void initializePlatform();
void task1(void *pParam);
void task3(void *pParam);
void statusOn();
void statusOff();

#ifdef __cplusplus
}
#endif
#endif
