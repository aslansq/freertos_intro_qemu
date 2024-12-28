/* Standard includes. */
#include <stdio.h>
#include <stdint.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"
#include "util.h"

#define APP_DEFAULT_TASK_STACK_SIZE (1024u)
#define APP_DEFAULT_TASK_PRIORITY   (tskIDLE_PRIORITY + 1)

// Timer call back
void app_backlightTmCbk(TimerHandle_t xTimer);
static void app_userInTask(void * pvParameters);

static const char app_backlightTmChar = 'b';
// one shot timer handle
static TimerHandle_t app_backlightTm;

void app_init(void) {
    BaseType_t ret;
    app_backlightTm = xTimerCreate(
        "backlightTm",                // pcTimerName
        pdMS_TO_TICKS( 5000 ),        // xTimerPeriod
        pdFALSE,                      // uxAutoReload
        (void *)&app_backlightTmChar, // pvTimerID
        app_backlightTmCbk            // pxCallbackFunction
    );

    ret = xTaskCreate(
        app_userInTask,              // pvTaskCode
        "userIn",                    // pcName
        APP_DEFAULT_TASK_STACK_SIZE, // uxStackDepth
        NULL,                        // pvParameters
        APP_DEFAULT_TASK_PRIORITY,   // uxPriority
        NULL                         // pxCreatedTask
    );

    if(app_backlightTm == NULL ||
       ret != pdTRUE) {
        printf("err timer\n");
        while(1)
            ;
    }

    xTimerStart(app_backlightTm, portMAX_DELAY);
    vTaskStartScheduler();
    for( ; ; ) {
    }
}

static void app_userInTask(void * pvParameters) {
    if(app_backlightTm == NULL) {
        printf("err back null\n");
        while(1)
            ;
    }
    (void)pvParameters;
    char c;
    int ret;
    for( ; ; ) {
        ret = uart0_readNonBlock(&c, 1);
        if(ret) {
            util_ledSet(1);
            printf("%c", c);
            xTimerStart(app_backlightTm, portMAX_DELAY);
        }
    }
}

void app_backlightTmCbk(TimerHandle_t xTimer) {
    if(xTimer == NULL) {
        printf("err tm cbk\n");
        while(1)
            ;
    }
    char *cPtr = (char *)pvTimerGetTimerID(xTimer);
    if((*cPtr) == app_backlightTmChar) {
        util_ledSet(0);
    }
}
