/* Standard includes. */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"

#define APP_DEFAULT_PRIORITY   (tskIDLE_PRIORITY + 1)
#define APP_DEFAULT_STACK_SIZE (1024u)

char *app_msg = NULL;
uint8_t app_msgReadyFlag = 0;

static void app_myTaskA( void * pvParameters );
static void app_myTaskB( void * pvParameters );

void demo_init(void) {

    xTaskCreate(app_myTaskA,
                "A",
                APP_DEFAULT_STACK_SIZE,
                NULL,
                APP_DEFAULT_PRIORITY,
                NULL );

    xTaskCreate(app_myTaskB,
                "B",
                APP_DEFAULT_STACK_SIZE,
                NULL,
                APP_DEFAULT_PRIORITY,
                NULL );

    vTaskStartScheduler();

    for( ; ; ) {
    }
}

static void app_myTaskA( void * pvParameters ) {
    static char serialBuf[200];
    for( ; ; ) {
        uart0_readLine(serialBuf, 200);
        size_t app_msgSize = (strlen(serialBuf)+1) * sizeof(char); // +1 for null
        app_msg = (char *) pvPortMalloc(app_msgSize);
        memcpy(app_msg, serialBuf, app_msgSize);
        app_msgReadyFlag = 1;
    }
}

static void app_myTaskB( void * pvParameters ) {
    for( ; ; ) {
        if(app_msgReadyFlag && app_msg != NULL) {
            printf("%s\n", app_msg);
            vPortFree(app_msg);
            app_msg = NULL;
            app_msgReadyFlag = 0;
        }
    }
}