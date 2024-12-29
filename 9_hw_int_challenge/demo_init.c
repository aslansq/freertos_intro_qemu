#include "demo_init.h"
#include "demo.h"

void demo_init_tm(demo_tmIsrHandle_T *demoHandle,
                  TaskHandle_t       taskToNotify) {
    // null pointer asserts
    configASSERT(!(demoHandle == NULL));
    configASSERT(!(taskToNotify == NULL));
    uint8_t i;

    // init tracing for interrupt
    xTraceISRRegister("t", PRIO_ISR_TIMER, &(demoHandle->traceIsrHandle));

    // init ring buffers
    for(i = 0; i < NUM_OF_RINGS; ++i) {
        ring_buffer_init(
            &demoHandle->ringBuf[i],
            demoHandle->buf[i],
            sizeof(char) * SIZE_OF_RING_BUF
        );
    }
    // ring buffer index
    demoHandle->ringBufIdx = 0;
    // save task to notify
    demoHandle->taskToNotify = taskToNotify; 
    // init timer
    TIMER_INT_CLEAR();
    TM0->CTRL |= CMSDK_TIMER_CTRL_IRQEN_Msk;
    TM0->RELOAD = ( configCPU_CLOCK_HZ / TIMER_FREQUENCY ) + 1UL;
    TM0->CTRL |= CMSDK_TIMER_CTRL_EN_Msk;
    NVIC_SetPriority( TIMER0_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY );
    NVIC_EnableIRQ( TIMER0_IRQn );

    demoHandle->isInitialized = pdTRUE;
}

void demo_init_taskA(demo_taskAHandle_T *demoHandle,
                     ring_buffer_t      *isrRingBuf,
                     QueueHandle_t      providerAdcAvgQ) {
    // null pointer checks
    configASSERT(!(demoHandle == NULL));
    configASSERT(!(isrRingBuf == NULL));
    configASSERT(!(providerAdcAvgQ == NULL));
    BaseType_t ret;
    uint8_t i = 0;

    // init taskA
    demoHandle->taskHandle = NULL;
    ret = xTaskCreate(
        demo_taskA,               // pvTaskCode
        "a",                      // pcName
        DEFAULT_TASK_STACK_SIZE,  // uxStackDepth
        (void *)demoHandle,       // pvParameters
        A_TASK_PRIORITY,          // uxPriority
        &demoHandle->taskHandle   // pxCreatedTask
    );

    configASSERT(!(ret != pdTRUE));
    configASSERT(!(demoHandle->taskHandle == NULL));
    // get references of ring buffers
    for(i = 0; i < NUM_OF_RINGS; ++i) {
        demoHandle->isrRingBuf[i] = &isrRingBuf[i];
    }
    // start from first ring buffer
    demoHandle->ringBufNotifyIdx = 0;
    // default avegared adc reading
    demoHandle->adcAvg = 0.0;
    // get reference for queue
    demoHandle->pAdcAvgQ = providerAdcAvgQ;
    demoHandle->isInitialized = pdTRUE;
}

void demo_init_taskB(demo_taskBHandle_T *demoHandle,
                     QueueHandle_t      consumerAdcAvgQ) {
    configASSERT(!(demoHandle == NULL));
    configASSERT(!(consumerAdcAvgQ == NULL));
    BaseType_t ret;
    ret = xTaskCreate(
        demo_taskB,               // pvTaskCode
        "b",                      // pcName
        DEFAULT_TASK_STACK_SIZE,  // uxStackDepth
        (void *)demoHandle,       // pvParameters
        B_TASK_PRIORITY,          // uxPriority
        NULL                      // pxCreatedTask
    );

    configASSERT(!(ret != pdTRUE));
    // get ref for queue
    demoHandle->cAdcAvgQ = consumerAdcAvgQ;
    demoHandle->isInitialized = pdTRUE;
}

void demo_init_taskLed(void) {
    BaseType_t ret;
    ret = xTaskCreate(
        demo_taskLed,             // pvTaskCode
        "l",                      // pcName
        DEFAULT_TASK_STACK_SIZE,  // uxStackDepth
        NULL,                     // pvParameters
        LED_TASK_PRIORITY,        // uxPriority
        NULL                      // pxCreatedTask
    );

    configASSERT(!(ret != pdTRUE));
}