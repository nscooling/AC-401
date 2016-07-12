#include "feabhOS_interrupts.h"
#include "FreeRTOS.h"
#include "task.h"


void feabhOS_enable_interrupts(void)
{
  taskEXIT_CRITICAL();
}


void feabhOS_disable_interrupts(void)
{
  taskENTER_CRITICAL();
}
