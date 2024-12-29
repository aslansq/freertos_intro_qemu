/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "demo_hw.h"
#include "string.h"

#define DEFAULT_PRIORITY   (tskIDLE_PRIORITY + 1)
#define DEFAULT_STACK_SIZE (1024u)

char *__msg = NULL;
uint8_t __msgReadyFlag = 0;

static void _taskA( void * pvParameters );
static void _taskB( void * pvParameters );

void demo_init(void) {

    xTaskCreate(_taskA,
                "A",
                DEFAULT_STACK_SIZE,
                NULL,
                DEFAULT_PRIORITY,
                NULL );

    xTaskCreate(_taskB,
                "B",
                DEFAULT_STACK_SIZE,
                NULL,
                DEFAULT_PRIORITY,
                NULL );

    vTaskStartScheduler();

    for( ; ; ) {
    }
}

static void _taskA( void * pvParameters ) {
    static char buf[200];
    for( ; ; ) {
        demo_hw_term_readLine(buf, 200);
        size_t msgSize = (strlen(buf)+1) * sizeof(char); // +1 for null
        __msg = (char *) pvPortMalloc(msgSize);
        memcpy(__msg, buf, msgSize);
        __msgReadyFlag = 1;
    }
}

static void _taskB( void * pvParameters ) {
    for( ; ; ) {
        if(__msgReadyFlag && __msg != NULL) {
            demo_hw_term_printf("%s\n", __msg);
            vPortFree(__msg);
            __msg = NULL;
            __msgReadyFlag = 0;
        }
    }
}