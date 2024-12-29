/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "demo_hw.h"

#define DEFAULT_PRIORITY   (tskIDLE_PRIORITY + 1)
#define DEFAULT_STACK_SIZE (1024u)

#define PRINT_MSG_DELAY (1000)
#define SEND_MSG_DELAY  (100)

static void _printMsgs(void * pvParameters);
static void _sendMsg(void * pvParameters);

static QueueHandle_t __xQueue1 = NULL;

void demo_init(void) {
    xTaskCreate(_printMsgs,
                "print",
                DEFAULT_STACK_SIZE,
                NULL,
                DEFAULT_PRIORITY,
                NULL );

    xTaskCreate(_sendMsg,
                "send",
                DEFAULT_STACK_SIZE,
                NULL,
                DEFAULT_PRIORITY,
                NULL );

    // can hold 10 int32_t
    __xQueue1 = xQueueCreate( 10, sizeof( uint8_t ) );

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }
}

static void _printMsgs( void * pvParameters ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)pvParameters;
    uint8_t msg = 0;
    BaseType_t recvRet; // receive return value
    for( ;; ) {
        if (__xQueue1 == NULL) {
            // do nothing
        } else {
            recvRet = xQueueReceive(__xQueue1, (void *)&msg, (TickType_t)0);
            if(recvRet != pdTRUE) {
                demo_hw_term_writeLine("-1");
            } else {
                printf("%d\n", (int)msg);
            }
        }
        vTaskDelay( pdMS_TO_TICKS( PRINT_MSG_DELAY ) );
    }
}

static void _sendMsg( void * pvParameters ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)pvParameters;
    uint8_t msg = 0;
    BaseType_t sendRet; // send function return value
    for( ;; ) {
        if(__xQueue1 == NULL) {
            // do nothing
        } else {
            // can wait for 10 ticks if necessary
            sendRet = xQueueSend(__xQueue1, (void *)&msg, (TickType_t)10);
            if(sendRet != pdTRUE) {
                // just here so you can put breakpoint
            }
        }
        msg++;
        vTaskDelay( pdMS_TO_TICKS( SEND_MSG_DELAY ) );
    }
}