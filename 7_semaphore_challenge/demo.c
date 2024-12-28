/* Standard includes. */
#include <stdio.h>
#include <stdint.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include "util.h"
#include "semphr.h"
#include "string.h"
#include "ringbuffer.h"

#define APP_DEFAULT_TASK_PRIORITY (tskIDLE_PRIORITY + 1)
#define APP_DEFAULT_TASK_STACK_SIZE 1024

#define APP_NUM_OF_PRODUCERS (5u)
#define APP_RING_BUF_SIZE (32u)

void app_producerTask(void *pvParameters);
void app_consumerTask(void *pvParameters);

typedef struct {
    char nameChar;
    uint8_t numOfSend;
} app_producerHandle_T;

static app_producerHandle_T app_producerHandles[APP_NUM_OF_PRODUCERS];

static ring_buffer_t app_ringBuf;
static SemaphoreHandle_t app_ringBuf_mutex = NULL;
static SemaphoreHandle_t app_ringBuf_semphr = NULL;
static char app_ringBuf_buf[APP_RING_BUF_SIZE];

void app_init(void) {
    uint8_t i;

    ring_buffer_init(&app_ringBuf, app_ringBuf_buf, sizeof(app_ringBuf_buf));
    app_ringBuf_mutex = xSemaphoreCreateMutex();
    app_ringBuf_semphr = xSemaphoreCreateCounting(APP_RING_BUF_SIZE, 0);

    for(i = 0; i < APP_NUM_OF_PRODUCERS; ++i) {
        char taskName[5];
        sprintf(taskName, "%d", (int)i);
        app_producerHandles[i].nameChar = '0' + i;
        app_producerHandles[i].numOfSend = 0;
        xTaskCreate(app_producerTask,            /* The function that implements the task. */
                    taskName,                    /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                    APP_DEFAULT_TASK_STACK_SIZE, /* The size of the stack to allocate to the task. */
                    &(app_producerHandles[i]),  /* The parameter passed to the task */
                    APP_DEFAULT_TASK_PRIORITY,   /* The priority assigned to the task. */
                    NULL );                      /* The task handle is not required, so NULL is passed. */
    }

    xTaskCreate(app_consumerTask,            /* The function that implements the task. */
                "A",                         /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                APP_DEFAULT_TASK_STACK_SIZE, /* The size of the stack to allocate to the task. */
                NULL,                        /* The parameter passed to the task */
                APP_DEFAULT_TASK_PRIORITY,   /* The priority assigned to the task. */
                NULL );                      /* The task handle is not required, so NULL is passed. */

    xTaskCreate(app_consumerTask,            /* The function that implements the task. */
                "B",                         /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                APP_DEFAULT_TASK_STACK_SIZE, /* The size of the stack to allocate to the task. */
                NULL,                        /* The parameter passed to the task */
                APP_DEFAULT_TASK_PRIORITY,   /* The priority assigned to the task. */
                NULL );                      /* The task handle is not required, so NULL is passed. */

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    for( ; ; ) {
    }
}

void app_consumerTask(void *pvParameters) {
    // null pointer checks
    if(app_ringBuf_mutex == NULL ||
       app_ringBuf_semphr == NULL) {
        while(1)
            ;
    }
    char c;

    for( ; ; ) {
        if(xSemaphoreTake(app_ringBuf_semphr, 0) == pdTRUE) {
            // wait until you get ringBuf access
            while(xSemaphoreTake(app_ringBuf_mutex, 0) != pdTRUE)
                ;
            // it is not possible that buffer is empty due app_ringBuf_semphr
            ring_buffer_dequeue(&app_ringBuf, &c);
            printf("%c\n", c);
            xSemaphoreGive(app_ringBuf_mutex);
        }
    }
}

void app_producerTask(void *pvParameters) {
    // null pointer checks
    if(pvParameters == NULL ||
       app_ringBuf_mutex == NULL ||
       app_ringBuf_semphr == NULL) {
        while(1)
            ;
    }

    app_producerHandle_T *producerHandlePtr = ((app_producerHandle_T *)pvParameters);

    for( ; ; ) {
        if(producerHandlePtr->numOfSend >= 3) {
            // already achieved our goal
            break;
        } if(xSemaphoreTake(app_ringBuf_mutex, 0) != pdTRUE) {
            // do nothing if I can not get access
        } else if(ring_buffer_is_full(&app_ringBuf)) {
            // if it is full just release
            xSemaphoreGive(app_ringBuf_mutex);
        } else {
            ring_buffer_queue(&app_ringBuf, producerHandlePtr->nameChar);
            producerHandlePtr->numOfSend++;
            xSemaphoreGive(app_ringBuf_semphr);
            xSemaphoreGive(app_ringBuf_mutex);
        }
    }

    vTaskDelete(NULL);
}
