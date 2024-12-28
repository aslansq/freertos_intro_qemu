/* Standard includes. */
#include <stdio.h>
#include <stdint.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

#define APP_DEFAULT_PRIORITY   (tskIDLE_PRIORITY + 1)
#define APP_DEFAULT_STACK_SIZE (1024u)

#define APP_PRINT_MSG_DELAY (1000)
#define APP_SEND_MSG_DELAY  (100)

static void app_printMsgs(void * pvParameters);
static void app_sendMsg(void * pvParameters);

static QueueHandle_t xQueue1 = NULL;

void demo_init(void) {
    xTaskCreate(app_printMsgs,
                "print",
                APP_DEFAULT_STACK_SIZE,
                NULL,
                APP_DEFAULT_PRIORITY,
                NULL );

    xTaskCreate(app_sendMsg,
                "send",
                APP_DEFAULT_STACK_SIZE,
                NULL,
                APP_DEFAULT_PRIORITY,
                NULL );

    // can hold 10 int32_t
    xQueue1 = xQueueCreate( 10, sizeof( uint8_t ) );

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }
}

static void app_printMsgs( void * pvParameters ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)pvParameters;
    uint8_t msg = 0;
    BaseType_t recvRet; // receive return value
    for( ;; ) {
        if (xQueue1 == NULL) {
            // do nothing
        } else {
            recvRet = xQueueReceive(xQueue1, (void *)&msg, (TickType_t)0);
            if(recvRet != pdTRUE) {
                printf("-1\n");
            } else {
                printf("%d\n", (int)msg);
            }
        }
        vTaskDelay( pdMS_TO_TICKS( APP_PRINT_MSG_DELAY ) );
    }
}

static void app_sendMsg( void * pvParameters ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)pvParameters;
    uint8_t msg = 0;
    BaseType_t sendRet; // send function return value
    for( ;; ) {
        if(xQueue1 == NULL) {
            // do nothing
        } else {
            // can wait for 10 ticks if necessary
            sendRet = xQueueSend(xQueue1, (void *)&msg, (TickType_t)10);
            if(sendRet != pdTRUE) {
                // just here so you can put breakpoint
            }
        }
        msg++;
        vTaskDelay( pdMS_TO_TICKS( APP_SEND_MSG_DELAY ) );
    }
}