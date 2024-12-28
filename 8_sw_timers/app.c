/* Standard includes. */
#include <stdio.h>
#include <stdint.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "timers.h"

// Timer call back
void app_timerCallback(TimerHandle_t xTimer);

static const char app_oneShotTmChar = 'o';
static const char app_autoReTmChar = 'a';

void app_init(void) {
    // one shot timer handle
    TimerHandle_t oneShotTm;
    // auto reload timer handle
    TimerHandle_t autoReTm;

    oneShotTm = xTimerCreate("oneShotTm",                // pcTimerName
                             pdMS_TO_TICKS( 2000 ),      // xTimerPeriod
                             pdFALSE,                    // uxAutoReload
                             (void *)&app_oneShotTmChar, // pvTimerID
                             app_timerCallback);         // pxCallbackFunction


    autoReTm = xTimerCreate("autoReTm",                 // pcTimerName
                             pdMS_TO_TICKS( 1000 ),     // xTimerPeriod
                             pdTRUE,                    // uxAutoReload
                             (void *)&app_autoReTmChar, // pvTimerID
                             app_timerCallback);        // pxCallbackFunction

    if(oneShotTm == NULL ||
       autoReTm == NULL) {
        printf("err timer\n");
        while(1)
            ;
    }

    xTimerStart(oneShotTm, portMAX_DELAY);
    xTimerStart(autoReTm, portMAX_DELAY);
    vTaskStartScheduler();
    for( ; ; ) {
    }
}

void app_timerCallback(TimerHandle_t xTimer) {
    char *cPtr = (char *)pvTimerGetTimerID(xTimer);
    if((*cPtr) == app_oneShotTmChar) {
        printf("one shot tm expired.\n");
    } else if((*cPtr) == app_autoReTmChar) {
        printf("auto reload tm expired.\n");
    }
}
