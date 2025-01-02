/* Standard includes. */
#include <stdlib.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "demo_hw.h"

#define BLINK_TASK_PRIORITY (tskIDLE_PRIORITY + 1)
#define BLINK_TASK_STACK_SIZE 1024

static SemaphoreHandle_t _binSemphr = NULL;

void _setup(void * pvParameters);
static void _blinkLED(void * pvParameters);

void demo_init(void) {
    xTaskCreate(_setup,                /* The function that implements the task. */
                "s",                   /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                BLINK_TASK_STACK_SIZE, /* The size of the stack to allocate to the task. */
                NULL,                  /* The parameter passed to the task */
                BLINK_TASK_PRIORITY,   /* The priority assigned to the task. */
                NULL );                /* The task handle is not required, so NULL is passed. */

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }
}

// simulating arduino environment
void _setup(void * pvParameters) {
    (void)pvParameters;
    char buf[100];
    // on the video he says this hack
    // well new FreeRTOS version can detect the hack and assert
    // below is their explanation:
            /* A task can only have an inherited priority if it holds the mutex.
             * If the mutex is held by a task then it cannot be given from an
             * interrupt, and if a mutex is given by the holding task then it must
             * be the running state task. */
    // _binSemphr = xSemaphoreCreateMutex();

    // so semaphore used to solve this challenge
    _binSemphr = xSemaphoreCreateBinary();
    uint32_t delay = 1000;

    demo_hw_term_write("Enter delay: ");
    demo_hw_term_readLine(buf, sizeof(buf));
    delay = atoi(buf);
    demo_hw_term_printf("\nDelay set to %d\n", (int)delay);

    xTaskCreate(_blinkLED,               /* The function that implements the task. */
                "blink",                    /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                BLINK_TASK_STACK_SIZE, /* The size of the stack to allocate to the task. */
                &delay,                     /* The parameter passed to the task */
                BLINK_TASK_PRIORITY,   /* The priority assigned to the task. */
                NULL );                     /* The task handle is not required, so NULL is passed. */

    // wait until you take
    xSemaphoreTake(_binSemphr, portMAX_DELAY);
    demo_hw_term_writeLine("_setup done");
    vTaskDelete(NULL);
}

static void _blinkLED( void * pvParameters ) {
    configASSERT(!( _binSemphr == NULL));
    configASSERT(!( pvParameters == NULL));
    uint32_t delay = 100;
    delay = *((uint32_t *) pvParameters);
    xSemaphoreGive(_binSemphr);
    for( ;; ) {
        vTaskDelay( pdMS_TO_TICKS( delay ) );
        demo_hw_led_toggle();
    }
}