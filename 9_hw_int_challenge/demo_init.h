
#ifndef DEMO_INIT_H
#define DEMO_INIT_H

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "ringbuffer.h"
#include "queue.h"

// demo hardware
#include "demo_hw.h"
#include "CMSDK_CM3.h"
// timer related defines
#define TM0 CMSDK_TIMER0
#define TIMER_INT_CLEAR() (TM0->INTCLEAR |= CMSDK_TIMER_INTCLEAR_Msk)
#define TIMER_FREQUENCY   ( 10UL )
#define PRIO_ISR_TIMER configMAX_SYSCALL_INTERRUPT_PRIORITY // the hardware priority of the interrupt
#define SIZE_OF_ADC_QUEUE (10u)
// task priorities
#define DEFAULT_TASK_PRIORITY (tskIDLE_PRIORITY + 1)
#define LED_TASK_PRIORITY     (tskIDLE_PRIORITY + 2)
#define B_TASK_PRIORITY       (tskIDLE_PRIORITY + 3)
#define A_TASK_PRIORITY       (tskIDLE_PRIORITY + 4)
// default stack size
#define DEFAULT_TASK_STACK_SIZE (1024u)
// number of ring buffers
#define NUM_OF_RINGS (3u)
// size of ring buffer
#define SIZE_OF_RING_BUF (16u)
// notify task to process when you this number of samples
#define NOTIFY_WHEN_NUM_OF_ADC_READS (10u)
#if (SIZE_OF_RING_BUF - NOTIFY_WHEN_NUM_OF_ADC_READS - 1) < 0
    #error number of reads would not fit into ring buffer
#endif

typedef struct {
    // handle needed for tracing
    TraceISRHandle_t traceIsrHandle;
    // ring buffers
    ring_buffer_t ringBuf[NUM_OF_RINGS];
    // ring buffer in active use
    uint8_t ringBufIdx;
    // actual buffer for ring buffer
    char buf[NUM_OF_RINGS][SIZE_OF_RING_BUF];
    // task that is going to be notified when NOTIFY_WHEN_NUM_OF_ADC_READS met
    TaskHandle_t taskToNotify;
    // is handle successfully init
    BaseType_t isInitialized;
} demo_tmIsrHandle_T;

typedef struct {
    // handle of the task
    TaskHandle_t taskHandle;
    // ring buffers filled by tm isr
    ring_buffer_t *isrRingBuf[NUM_OF_RINGS];
    // ring buffer notification
    uint8_t ringBufNotifyIdx;
    // analog digital converted value average
    float adcAvg;
    // adc avg values provider for the queue
    QueueHandle_t pAdcAvgQ;
    // is handle successfully init
    BaseType_t isInitialized;
} demo_taskAHandle_T;

typedef struct {
    // adc avg values consumer for the queue
    QueueHandle_t cAdcAvgQ;
    BaseType_t isInitialized;
} demo_taskBHandle_T;

typedef struct {
    demo_tmIsrHandle_T demoTmIsrHandle;
    demo_taskAHandle_T demoTaskAHandle;
    demo_taskBHandle_T demoTaskBHandle;
    QueueHandle_t adcAvgQ;
} demo_mainHandle_T;

void demo_init_tm(demo_tmIsrHandle_T *demoHandle,
                  TaskHandle_t       taskToNotify);

void demo_init_taskA(demo_taskAHandle_T *demoHandle,
                     ring_buffer_t      *isrRing,
                     QueueHandle_t      providerAdcAvgQ);

void demo_init_taskB(demo_taskBHandle_T *demoHandle,
                     QueueHandle_t      consumerAdcAvgQ);

// this is just implemented to see if scheduler is running
void demo_init_taskLed(void);


#endif //DEMO_INIT_H