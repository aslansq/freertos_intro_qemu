/* Kernel includes. */
#include "FreeRTOS.h"
#include "timers.h"
#include "demo_hw.h"

// Timer call back
void _timerCallback(TimerHandle_t xTimer);

static const char _oneShotTmChar = 'o';
static const char _autoReTmChar = 'a';

void demo_init(void) {
    // one shot timer handle
    TimerHandle_t oneShotTm;
    // auto reload timer handle
    TimerHandle_t autoReTm;

    oneShotTm = xTimerCreate("oneShotTm",                // pcTimerName
                             pdMS_TO_TICKS( 2000 ),      // xTimerPeriod
                             pdFALSE,                    // uxAutoReload
                             (void *)&_oneShotTmChar, // pvTimerID
                             _timerCallback);         // pxCallbackFunction


    autoReTm = xTimerCreate("autoReTm",                 // pcTimerName
                             pdMS_TO_TICKS( 1000 ),     // xTimerPeriod
                             pdTRUE,                    // uxAutoReload
                             (void *)&_autoReTmChar, // pvTimerID
                             _timerCallback);        // pxCallbackFunction

    configASSERT(!(oneShotTm == NULL));
    configASSERT(!(autoReTm == NULL));

    xTimerStart(oneShotTm, portMAX_DELAY);
    xTimerStart(autoReTm, portMAX_DELAY);
    vTaskStartScheduler();
    for( ; ; ) {
    }
}

void _timerCallback(TimerHandle_t xTimer) {
    char *cPtr = (char *)pvTimerGetTimerID(xTimer);
    if((*cPtr) == _oneShotTmChar) {
        demo_hw_term_writeLine("one shot tm expired.");
    } else if((*cPtr) == _autoReTmChar) {
        demo_hw_term_writeLine("auto reload tm expired.");
    }
}
