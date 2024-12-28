/* Standard includes. */
#include <stdio.h>
#include <stdint.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include "util.h"
#include "semphr.h"
#include "string.h"

#define APP_DEFAULT_TASK_PRIORITY (tskIDLE_PRIORITY + 1)
#define APP_DEFAULT_TASK_STACK_SIZE 1024

void app_init(void) {

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }
}
