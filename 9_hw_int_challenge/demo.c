#include "demo_init.h"
#include "demo.h"
#include <string.h>
static demo_mainHandle_T _demoMainHandle;

void demo_init(void) {
    _demoMainHandle.adcAvgQ = xQueueCreate(SIZE_OF_ADC_QUEUE, sizeof( uint8_t ) );

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
    /* Clear interrupt. */
    TIMER_INT_CLEAR();
    xTraceISRBegin(demoHandle->traceIsrHandle);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint8_t isEmpty;
    char adcVal = (char)demo_hw_adc_read();
    ring_buffer_queue(&demoHandle->ringBuf[demoHandle->ringBufIdx], adcVal);
    ring_buffer_size_t num = ring_buffer_num_items(&demoHandle->ringBuf[demoHandle->ringBufIdx]);
    if(num == NOTIFY_WHEN_NUM_OF_ADC_READS) {
        vTaskNotifyGiveIndexedFromISR(demoHandle->taskToNotify, demoHandle->ringBufIdx, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        demoHandle->ringBufIdx = (demoHandle->ringBufIdx + 1) == NUM_OF_RINGS ? 0 : (demoHandle->ringBufIdx + 1);
        isEmpty = ring_buffer_is_empty(&demoHandle->ringBuf[demoHandle->ringBufIdx]);
        configASSERT(!(isEmpty != 1));
    }
    xTraceISREnd(0);
}

void demo_taskA( void * pvParameters ) {
    configASSERT(!(pvParameters == NULL));
    volatile demo_taskAHandle_T *demoHandle = (volatile demo_taskAHandle_T *)pvParameters;
    char c;
    uint8_t u8;
    uint8_t numOfRead = 0;
    for( ; ; ) {
        ulTaskNotifyTakeIndexed(
            demoHandle->ringBufNotifyIdx,
            pdFALSE,
            portMAX_DELAY
        );
        demoHandle->adcAvg = 0;
        numOfRead = 0;
        while(ring_buffer_dequeue(demoHandle->isrRingBuf[demoHandle->ringBufNotifyIdx], &c)) {
            demoHandle->adcAvg += (float)((uint8_t)c);
            numOfRead++;
        }
        configASSERT(!(numOfRead != NOTIFY_WHEN_NUM_OF_ADC_READS));
        demoHandle->adcAvg /= ((float) NOTIFY_WHEN_NUM_OF_ADC_READS);
        u8 = (uint8_t)demoHandle->adcAvg;
        demoHandle->ringBufNotifyIdx = (demoHandle->ringBufNotifyIdx + 1) == NUM_OF_RINGS ? 0 : (demoHandle->ringBufNotifyIdx + 1);
        xQueueSend(demoHandle->pAdcAvgQ, &u8, 3);
    }
}

void demo_taskB( void * pvParameters ) {
    configASSERT(!(pvParameters == NULL));
    volatile demo_taskBHandle_T *demoHandle = (volatile demo_taskBHandle_T *)pvParameters;
    uint8_t adcVal = 0;
    static char termBuf[100];
    static uint8_t termBufIdx = 0;
    char c;
    uint8_t read;
    for( ; ; ) {
        read = demo_hw_term_readCharNonBlock(&c);
        // if nothing is read do nothing
        if(read == 0) {
            continue;
        }

        // just echo
        demo_hw_term_writeChar(c);
        // save it to buffer
        if(c != '\r') {
            termBuf[termBufIdx] = c;
            termBufIdx++;
        } else {
            termBuf[termBufIdx] = '\0';
            if(strcmp(termBuf, "avg") == 0) {
                // I am not blocking user interface if I can not get adc value
                xQueueReceive(demoHandle->cAdcAvgQ, &adcVal, 3);
                demo_hw_term_printf("%d\n", (int)adcVal);
            }
            termBufIdx = 0;
            termBuf[termBufIdx] = '\0';
        }

    }
}


void demo_taskLed( void * pvParameters ) {
    (void)pvParameters;
    for( ; ; ) {
        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
        demo_hw_led_toggle();
    }
}