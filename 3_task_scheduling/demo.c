/* Standard includes. */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"


#define APP_TASK_LOOP_PRIORITY (tskIDLE_PRIORITY + 1)
#define APP_TASK1_PRIORITY     (tskIDLE_PRIORITY + 2)
#define APP_TASK2_PRIORITY     (tskIDLE_PRIORITY + 3)
#define APP_DEFAULT_TASK_STACK_SIZE 1024

static void startTask1(void *parameter);
static void startTask2(void *parameter);
static void loop(void *parameter);
static void slowPrintf(const char *s);

// putting strings here so it can not get out of scope of a task
static const char task1Msg[] = "Barkadeer brig Arr booty rum.";
static const char task1DelMsg[] = "Task1 deleted.";

TaskHandle_t task_1 = NULL;
TaskHandle_t task_2 = NULL;

void app_init(void) {
    xTaskCreate(startTask1,
                "startTask1",
                APP_DEFAULT_TASK_STACK_SIZE,
                NULL,
                APP_TASK1_PRIORITY,
                &task_1);

    xTaskCreate(startTask2,
                "startTask2",
                APP_DEFAULT_TASK_STACK_SIZE,
                NULL,
                APP_TASK2_PRIORITY,
                &task_2);

    xTaskCreate(loop,
                "loop",
                APP_DEFAULT_TASK_STACK_SIZE,
                NULL,
                APP_TASK_LOOP_PRIORITY,
                NULL);

    /* Start the tasks and timer running. */
    vTaskStartScheduler();
}

static void slowPrintf(const char *s) {
    size_t sLen = strlen(s);
    for (size_t i = 0; i < sLen; i++) {
        for(int j = 0; j < 10000000; j++) {
            __asm__("nop");
        }
        printf("%c", s[i]);
    }
}


static void loop(void *parameter) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)parameter;
    uint8_t i = 0;
    while(1) {
        for(i = 0; i < 3; ++i)
        {
            vTaskSuspend( task_2 );
            vTaskDelay( pdMS_TO_TICKS( 2000 ) );
            vTaskResume( task_2 );
            vTaskDelay( pdMS_TO_TICKS( 2000 ) );
        }

        if(task_1 != NULL) {
            vTaskDelete(task_1);
            task_1 = NULL;
            printf(task1DelMsg);
        }
    }
}

static void startTask1( void * parameter ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)parameter;
    for( ;; ) {
        slowPrintf("\n");
        slowPrintf(task1Msg);
        slowPrintf("\n");
        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
    }
}

static void startTask2( void * parameter ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)parameter;
    for( ;; ) {
        vTaskDelay( pdMS_TO_TICKS( 100 ) );
        slowPrintf("*");
    }
}