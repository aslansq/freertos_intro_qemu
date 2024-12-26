/* Standard includes. */
#include <stdio.h>
#include <stdint.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

#define APP_BLINKY_TASK_PRIORITY (tskIDLE_PRIORITY + 1)
#define APP_BLINKY_TASK_STACK_SIZE 1024

static void app_blinky(void * pvParameters);

void app_init(void) {
    /* Start the two tasks as described in the comments at the top of this
        * file. */
    xTaskCreate(app_blinky,                 /* The function that implements the task. */
                "blinky",                   /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                APP_BLINKY_TASK_STACK_SIZE, /* The size of the stack to allocate to the task. */
                NULL,                       /* The parameter passed to the task - not used in this simple case. */
                APP_BLINKY_TASK_PRIORITY,   /* The priority assigned to the task. */
                NULL );                     /* The task handle is not required, so NULL is passed. */
    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following
     * line will never be reached.  If the following line does execute, then
     * there was insufficient FreeRTOS heap memory available for the idle and/or
     * timer tasks	to be created.  See the memory management section on the
     * FreeRTOS web site for more details.  NOTE: This demo uses static allocation
     * for the idle and timer tasks so this line should never execute. */
    for( ; ; )
    {
    }
}

static void app_blinky( void * pvParameters ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)pvParameters;
    static uint8_t led_st = 0;
    for( ;; ) {
        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
        led_st = !led_st;
        printf("Memory Blinky: %d\n", (int)led_st);
    }
}