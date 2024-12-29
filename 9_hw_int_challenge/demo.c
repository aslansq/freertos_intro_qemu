#include "demo_init.h"
#include "demo.h"

static demo_mainHandle_T _demoMainHandle;

void demo_init(void) {
    _demoMainHandle.adcAvgQ = xQueueCreate( 10, sizeof( uint8_t ) );

    configASSERT(!(_demoMainHandle.adcAvgQ == NULL));

    demo_init_taskLed();

    demo_init_taskA(
        &_demoMainHandle.demoTaskAHandle,
        _demoMainHandle.demoTmIsrHandle.ringBuf,
        _demoMainHandle.adcAvgQ
    );

    demo_init_tm(
        &_demoMainHandle.demoTmIsrHandle,
        _demoMainHandle.demoTaskAHandle.taskHandle
    );

    demo_init_taskB(
        &_demoMainHandle.demoTaskBHandle,
        _demoMainHandle.adcAvgQ
    );

    vTaskStartScheduler();

    for( ; ; ) {
    }
}

void TIMER0_Handler( void )
{
    demo_tmIsrHandle_T *demoHandle = &(_demoMainHandle.demoTmIsrHandle);
    xTraceISRBegin(demoHandle->traceIsrHandle);
    /* Clear interrupt. */
    TIMER_INT_CLEAR();
    xTraceISREnd(0);
}

void demo_taskA( void * pvParameters ) {
    configASSERT(!(pvParameters == NULL));
    for( ; ; ) {
    }
}

void demo_taskB( void * pvParameters ) {
    configASSERT(!(pvParameters == NULL));
    for( ; ; ) {
    }
}


void demo_taskLed( void * pvParameters ) {
    for( ; ; ) {
        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
        demo_hw_led_toggle();
    }
}