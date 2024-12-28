/* Standard includes. */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

// if none chosen make race condition default demo
#ifndef APP_DEMO_RACE
#ifndef APP_DEMO_MUTEX
    #define APP_DEMO_RACE
#endif // APP_DEMO_MUTEX
#endif // APP_DEMO_RACE

#ifdef APP_DEMO_RACE
#ifdef APP_DEMO_MUTEX
    #error double selection APP_DEMO_RACE and APP_DEMO_MUTEX. choose either
#endif // APP_DEMO_MUTEX
#endif // APP_DEMO_RACE

#define APP_DEFAULT_PRIORITY   (tskIDLE_PRIORITY + 1)
#define APP_DEFAULT_STACK_SIZE (1024u)

static void app_incTask(void * pvParameters);
static int app_sharedVar = 0;

#ifdef APP_DEMO_MUTEX
static SemaphoreHandle_t app_sharedVar_mutex;
#endif

void demo_init(void) {
#ifdef APP_DEMO_MUTEX
    app_sharedVar_mutex = xSemaphoreCreateMutex();
#endif

    xTaskCreate(app_incTask,
                "A",
                APP_DEFAULT_STACK_SIZE,
                NULL,
                APP_DEFAULT_PRIORITY,
                NULL );

    xTaskCreate(app_incTask,
                "B",
                APP_DEFAULT_STACK_SIZE,
                NULL,
                APP_DEFAULT_PRIORITY,
                NULL );

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    for( ; ; ) {
    }
}

#ifdef APP_DEMO_RACE
static int app_rand(void) {
    static int ranDurOfOpLut[] = {973, 594, 28, 651, 73, 680, 452, 504}; // random duration of operation look up table
    static int ranIdx = 0;
    ranIdx++;
    ranIdx = ranIdx < 8 ? ranIdx : 0;
    // looks random enough, this particular environment is not happy calling rand function from stdlib
    return ranDurOfOpLut[ranIdx % 8];
}

static void app_incTask(void * pvParameters) {
    int localVar = 0;
    int ranDurOfOp = 0;
    for( ; ; ) {
        ranDurOfOp = app_rand();
        localVar = app_sharedVar;
        localVar++;
        vTaskDelay( pdMS_TO_TICKS( ranDurOfOp ) );
        app_sharedVar = localVar;
        printf("%d\n", app_sharedVar);
    }
}
#endif //APP_DEMO_RACE

#ifdef APP_DEMO_MUTEX
static int app_rand(void) {
    static int ranDurOfOpLut[] = {973, 594, 28, 651, 73, 680, 452, 504}; // random duration of operation look up table
    static int ranIdx = 0;
    ranIdx++;
    ranIdx = ranIdx < 8 ? ranIdx : 0;
    // looks random enough, this particular environment is not happy calling rand function from stdlib
    return ranDurOfOpLut[ranIdx % 8];
}

static void app_incTask(void * pvParameters) {
    int localVar = 0;
    int ranDurOfOp = 0;
    for( ; ; ) {
        if(xSemaphoreTake(app_sharedVar_mutex, 5) == pdTRUE) {
            ranDurOfOp = app_rand();
            localVar = app_sharedVar;
            localVar++;
            vTaskDelay( pdMS_TO_TICKS( ranDurOfOp ) );
            app_sharedVar = localVar;
            printf("%d\n", app_sharedVar);
            xSemaphoreGive(app_sharedVar_mutex);
        }
    }
}
#endif //APP_DEMO_MUTEX