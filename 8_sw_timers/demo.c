/* Kernel includes. */
#include "FreeRTOS.h"
#include "timers.h"
#include "demo_hw.h"

// Timer call back
void _timerCallback(TimerHandle_t xTimer);

static const char __oneShotTmChar = 'o';
static const char __autoReTmChar = 'a';

void demo_init(void) {
    // one shot timer handle
    TimerHandle_t oneShotTm;
    // auto reload timer handle
    TimerHandle_t autoReTm;

    oneShotTm = xTimerCreate("oneShotTm",                // pcTimerName
                             pdMS_TO_TICKS( 2000 ),      // xTimerPeriod
                             pdFALSE,                    // uxAutoReload
                             (void *)&__oneShotTmChar, // pvTimerID
                             _timerCallback);         // pxCallbackFunction


    autoReTm = xTimerCreate("autoReTm",                 // pcTimerName
                             pdMS_TO_TICKS( 1000 ),     // xTimerPeriod
                             pdTRUE,                    // uxAutoReload
                             (void *)&__autoReTmChar, // pvTimerID
                             _timerCallback);        // pxCallbackFunction

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

void _timerCallback(TimerHandle_t xTimer) {
    char *cPtr = (char *)pvTimerGetTimerID(xTimer);
    if((*cPtr) == __oneShotTmChar) {
        demo_hw_term_writeLine("one shot tm expired.");
    } else if((*cPtr) == __autoReTmChar) {
        demo_hw_term_writeLine("auto reload tm expired.");
    }
}
