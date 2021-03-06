/* ---------------------------------------------------------------------------*/
/*
  FeabhOS OS abstraction layer

  OS-specific definitions.
  These must be configured for the particular
  underlying OS.
*/
/* ---------------------------------------------------------------------------*/
#ifndef FEABHOS_DEFS_H
#define FEABHOS_DEFS_H

/* 
  Got to include the OS-specific configuration and header
  files.
*/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"


/* ---------------------------------------------------------------------------*/
/*
  Stack size definitions.
  For your underlying OS define the legitimate stack sizes (in bytes).
*/
#define OS_STACK_TINY   	256
#define OS_STACK_SMALL  	512
#define OS_STACK_NORMAL 	1024
#define OS_STACK_LARGE  	2048
#define OS_STACK_HUGE   	4096


/* ---------------------------------------------------------------------------*/
/*
  Priority definitions
  --------------------
  The definition of thread priority varies from OS to OS.  Use
  these macros to define the range of priorities for your
  system.
  You may create additional priority definitions if you need
  them.
*/
#define OS_PRIORITY_LOWEST    tskIDLE_PRIORITY + 1
#define OS_PRIORITY_LOW     	tskIDLE_PRIORITY + 2
#define OS_PRIORITY_NORMAL  	tskIDLE_PRIORITY + 3
#define OS_PRIORITY_HIGH   	  tskIDLE_PRIORITY + 4
#define OS_PRIORITY_HIGHEST 	tskIDLE_PRIORITY + 5


/* ---------------------------------------------------------------------------*/
/*
  OS-specific structures
  ----------------------
  All OSes use specific types to identify OS elements.  These may be simple
  integer values, structures or pointers-to-opaque-types.  Use the following
  macros to define the underlying types used by your OS.
*/

#define OS_TASK_TYPE               xTaskHandle
#define OS_MUTEX_TYPE              xSemaphoreHandle
#define OS_SIGNAL_TYPE             xSemaphoreHandle
#define OS_CONDITION_TYPE
#define OS_BINARY_SEMAPHORE_TYPE   xSemaphoreHandle
#define OS_COUNTING_SEMAPHORE_TYPE xSemaphoreHandle
#define OS_QUEUE_TYPE              xQueueHandle


/* ---------------------------------------------------------------------------*/
/*
  OS-specific time durations
  --------------------------
  Your OS uses its own underlying type for specifying time instants/durations.
  Use the macro definition below to specify the specific underlying type for
  your OS.
  You will also need to specify what constitutes a 'zero' duration and an
  'infinite' period of time for your particular OS.
*/
#define OS_TIME_TYPE            portTickType
#define OS_ZERO_TIMEOUT         0
#define OS_INFINITE_TIMEOUT     portMAX_DELAY



/* ---------------------------------------------------------------------------*/
/*
  OS-specific error types
  -----------------------
  Use this macro to define the type returned by your OS in the event of an error.
  You may extend this list if your OS returns different error types.
*/
#define OS_ERROR_TYPE           portBASE_TYPE

/* ---------------------------------------------------------------------------*/


#endif /* FEABHOS_DEFS_H */
