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

#define APP_NUM_OF_PRINT_MSG_TASK (5u)

static SemaphoreHandle_t app_semphr = NULL;

void setup(void * pvParameters);
static void app_printMsg(void * pvParameters);

void app_init(void) {
    xTaskCreate(setup,                      /* The function that implements the task. */
                "S",                        /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                APP_DEFAULT_TASK_STACK_SIZE, /* The size of the stack to allocate to the task. */
                NULL,                       /* The parameter passed to the task */
                APP_DEFAULT_TASK_PRIORITY,   /* The priority assigned to the task. */
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
    char msg[] = "Hi from setup\'s stack\n";
    char taskNames[APP_NUM_OF_PRINT_MSG_TASK][2] = {"A", "B", "C", "D", "E"};
    uint8_t i;

    app_semphr = xSemaphoreCreateCounting(APP_NUM_OF_PRINT_MSG_TASK, 0);

    for(i = 0; i < APP_NUM_OF_PRINT_MSG_TASK; ++i) {
        xTaskCreate(app_printMsg,               /* The function that implements the task. */
                    taskNames[i],                    /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                    APP_DEFAULT_TASK_STACK_SIZE, /* The size of the stack to allocate to the task. */
                    msg,                     /* The parameter passed to the task */
                    APP_DEFAULT_TASK_PRIORITY,   /* The priority assigned to the task. */
                    NULL );                     /* The task handle is not required, so NULL is passed. */
    }

    for(i = 0; i < APP_NUM_OF_PRINT_MSG_TASK; ++i) {
        while(xSemaphoreTake(app_semphr, 5) != pdTRUE)
            ;
    }

    printf("setup done\n");
    vTaskDelete(NULL);
}

static void app_printMsg( void * pvParameters ) {
    if(app_semphr == NULL ||
       pvParameters == NULL) {
        printf("null checks fail");
        while(1)
            ;
    }
    char msg[100];
    strcpy(msg, (char *)pvParameters);
    printf("%s", msg);
    xSemaphoreGive(app_semphr);
    vTaskDelete(NULL);
}