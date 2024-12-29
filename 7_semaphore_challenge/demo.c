/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "ringbuffer.h"
#include "demo_hw.h"

#define DEFAULT_TASK_PRIORITY (tskIDLE_PRIORITY + 1)
#define DEFAULT_TASK_STACK_SIZE 1024

#define NUM_OF_PRODUCERS (5u)
#define RING_BUF_SIZE (32u)

void _producerTask(void *pvParameters);
void _consumerTask(void *pvParameters);

typedef struct {
    char nameChar;
    uint8_t numOfSend;
} producerHandle_T;

static producerHandle_T _producerHandles[NUM_OF_PRODUCERS];

static ring_buffer_t _ringBuf;
static SemaphoreHandle_t _ringBuf_mutex = NULL;
static SemaphoreHandle_t _ringBuf_semphr = NULL;
static char _ringBuf_buf[RING_BUF_SIZE];

void demo_init(void) {
    uint8_t i;

    ring_buffer_init(&_ringBuf, _ringBuf_buf, sizeof(_ringBuf_buf));
    _ringBuf_mutex = xSemaphoreCreateMutex();
    _ringBuf_semphr = xSemaphoreCreateCounting(RING_BUF_SIZE, 0);

    for(i = 0; i < NUM_OF_PRODUCERS; ++i) {
        char taskName[2];
        taskName[0] = '0' + i;
        taskName[1] = '\0';
        _producerHandles[i].nameChar = '0' + i;
        _producerHandles[i].numOfSend = 0;
        xTaskCreate(_producerTask,           /* The function that implements the task. */
                    taskName,                /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                    DEFAULT_TASK_STACK_SIZE, /* The size of the stack to allocate to the task. */
                    &(_producerHandles[i]), /* The parameter passed to the task */
                    DEFAULT_TASK_PRIORITY,   /* The priority assigned to the task. */
                    NULL );                  /* The task handle is not required, so NULL is passed. */
    }

    xTaskCreate(_consumerTask,               /* The function that implements the task. */
                "A",                         /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                DEFAULT_TASK_STACK_SIZE,     /* The size of the stack to allocate to the task. */
                NULL,                        /* The parameter passed to the task */
                DEFAULT_TASK_PRIORITY,       /* The priority assigned to the task. */
                NULL );                      /* The task handle is not required, so NULL is passed. */

    xTaskCreate(_consumerTask,               /* The function that implements the task. */
                "B",                         /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                DEFAULT_TASK_STACK_SIZE,     /* The size of the stack to allocate to the task. */
                NULL,                        /* The parameter passed to the task */
                DEFAULT_TASK_PRIORITY,       /* The priority assigned to the task. */
                NULL );                      /* The task handle is not required, so NULL is passed. */

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    for( ; ; ) {
    }
}

void _consumerTask(void *pvParameters) {
    // null pointer checks
    if(_ringBuf_mutex == NULL ||
       _ringBuf_semphr == NULL) {
        while(1)
            ;
    }
    char c;

    for( ; ; ) {
        if(xSemaphoreTake(_ringBuf_semphr, 0) == pdTRUE) {
            // wait until you get ringBuf access
            while(xSemaphoreTake(_ringBuf_mutex, 0) != pdTRUE)
                ;
            // it is not possible that buffer is empty due _ringBuf_semphr
            ring_buffer_dequeue(&_ringBuf, &c);
            demo_hw_term_writeChar(c);
            demo_hw_term_writeChar('\n');
            xSemaphoreGive(_ringBuf_mutex);
        }
    }
}

void _producerTask(void *pvParameters) {
    // null pointer checks
    if(pvParameters == NULL ||
       _ringBuf_mutex == NULL ||
       _ringBuf_semphr == NULL) {
        while(1)
            ;
    }

    producerHandle_T *producerHandlePtr = ((producerHandle_T *)pvParameters);

    for( ; ; ) {
        if(producerHandlePtr->numOfSend >= 3) {
            // already achieved our goal
            break;
        } if(xSemaphoreTake(_ringBuf_mutex, 0) != pdTRUE) {
            // do nothing if I can not get access
        } else if(ring_buffer_is_full(&_ringBuf)) {
            // if it is full just release
            xSemaphoreGive(_ringBuf_mutex);
        } else {
            ring_buffer_queue(&_ringBuf, producerHandlePtr->nameChar);
            producerHandlePtr->numOfSend++;
            xSemaphoreGive(_ringBuf_semphr);
            xSemaphoreGive(_ringBuf_mutex);
        }
    }

    vTaskDelete(NULL);
}
