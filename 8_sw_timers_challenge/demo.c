/* Kernel includes. */
#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"
#include "demo_hw.h"

#define DEFAULT_TASK_STACK_SIZE (1024u)
#define DEFAULT_TASK_PRIORITY   (tskIDLE_PRIORITY + 1)

// Timer call back
void _backlightTmCbk(TimerHandle_t xTimer);
static void _userInTask(void * pvParameters);

static const char _backlightTmChar = 'b';
// one shot timer handle
static TimerHandle_t _backlightTm;

void demo_init(void) {
    BaseType_t ret;
    _backlightTm = xTimerCreate(
        "backlightTm",              // pcTimerName
        pdMS_TO_TICKS( 5000 ),      // xTimerPeriod
        pdFALSE,                    // uxAutoReload
        (void *)&_backlightTmChar, // pvTimerID
        _backlightTmCbk             // pxCallbackFunction
    );

    ret = xTaskCreate(
        _userInTask,             // pvTaskCode
        "userIn",                // pcName
        DEFAULT_TASK_STACK_SIZE, // uxStackDepth
        NULL,                    // pvParameters
        DEFAULT_TASK_PRIORITY,   // uxPriority
        NULL                     // pxCreatedTask
    );

    if(_backlightTm == NULL ||
       ret != pdTRUE) {
        demo_hw_term_writeLine("err timer");
        while(1)
            ;
    }

    xTimerStart(_backlightTm, portMAX_DELAY);
    vTaskStartScheduler();
    for( ; ; ) {
    }
}

static void _userInTask(void * pvParameters) {
    if(_backlightTm == NULL) {
        demo_hw_term_writeLine("err back null");
        while(1)
            ;
    }
    (void)pvParameters;
    char c;
    int ret;
    for( ; ; ) {
        ret = demo_hw_term_readCharNonBlock(&c);
        if(ret) {
            demo_hw_led_set(1);
            demo_hw_term_writeChar(c);
            xTimerStart(_backlightTm, portMAX_DELAY);
        }
    }
}

void _backlightTmCbk(TimerHandle_t xTimer) {
    if(xTimer == NULL) {
        demo_hw_term_writeLine("err tm cbk");
        while(1)
            ;
    }
    char *cPtr = (char *)pvTimerGetTimerID(xTimer);
    if((*cPtr) == _backlightTmChar) {
        demo_hw_led_set(0);
    }
}
