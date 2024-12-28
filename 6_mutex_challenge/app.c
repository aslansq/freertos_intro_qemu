/* Standard includes. */
#include <stdio.h>
#include <stdint.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include "util.h"
#include "semphr.h"

#define APP_BLINKY_TASK_PRIORITY (tskIDLE_PRIORITY + 1)
#define APP_BLINKY_TASK_STACK_SIZE 1024

static SemaphoreHandle_t app_mutex = NULL;

void setup(void * pvParameters);
static void app_blinkLED(void * pvParameters);

void app_init(void) {
    xTaskCreate(setup,                      /* The function that implements the task. */
                "s",                        /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                APP_BLINKY_TASK_STACK_SIZE, /* The size of the stack to allocate to the task. */
                NULL,                       /* The parameter passed to the task */
                APP_BLINKY_TASK_PRIORITY,   /* The priority assigned to the task. */
                NULL );                     /* The task handle is not required, so NULL is passed. */

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }
}

// simulating arduino environment
void setup(void * pvParameters) {
    (void)pvParameters;
    // on the video he says this hack
    // well new FreeRTOS version can detect the hack and assert
    // below is their explanation:
            /* A task can only have an inherited priority if it holds the mutex.
             * If the mutex is held by a task then it cannot be given from an
             * interrupt, and if a mutex is given by the holding task then it must
             * be the running state task. */
    // app_mutex = xSemaphoreCreateMutex();

    // so semaphore used to solve this challenge
    app_mutex = xSemaphoreCreateBinary();
    uint32_t delay = 1000;

    xSemaphoreTake(app_mutex, 5);
    printf("Enter delay: ");
    uart0_readU32(&delay);
    printf("\nDelay set to %d\n", (int)delay);

    xTaskCreate(app_blinkLED,               /* The function that implements the task. */
                "blink",                    /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                APP_BLINKY_TASK_STACK_SIZE, /* The size of the stack to allocate to the task. */
                &delay,                     /* The parameter passed to the task */
                APP_BLINKY_TASK_PRIORITY,   /* The priority assigned to the task. */
                NULL );                     /* The task handle is not required, so NULL is passed. */

    xSemaphoreTake(app_mutex, 5);
    xSemaphoreGive(app_mutex);
    vTaskDelete(NULL);
}

static void app_blinkLED( void * pvParameters ) {
    if(app_mutex == NULL ||
       pvParameters == NULL) {
        printf("null checks fail");
        while(1)
            ;
    }
    static uint8_t led_st = 0;
    uint32_t delay = 100;
    delay = *((uint32_t *) pvParameters);
    xSemaphoreGive(app_mutex);
    for( ;; ) {
        vTaskDelay( pdMS_TO_TICKS( delay ) );
        led_st = !led_st;
        util_ledSet(led_st);
    }
}