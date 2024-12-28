/* Standard includes. */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "uart.h"
#include "util.h"

#define APP_DEFAULT_PRIORITY   (tskIDLE_PRIORITY + 1)
#define APP_DEFAULT_STACK_SIZE (1024u)

#define APP_MSG_BUF_SIZE (100u)
#define APP_USER_INPUT_BUF_SIZE (100u)

#define APP_BLINKED_MSG_EVERY_NTH (100u)

static void app_myTaskA(void * pvParameters);
static void app_myTaskB(void * pvParameters);

static QueueHandle_t xQueue1 = NULL;
static QueueHandle_t xQueue2 = NULL;

typedef uint16_t delay_t;

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

    // can hold 10 int32_t
    xQueue1 = xQueueCreate( 10, sizeof( delay_t ) );
    xQueue2 = xQueueCreate( APP_MSG_BUF_SIZE, sizeof( char ) );

    if(xQueue1 == NULL) {
        printf("xQueue1 null\n");
    }

    if(xQueue2 == NULL) {
        printf("xQueue2 null\n");
    }

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }
}

static void printMsgsFromQ2(void) {
    static char msg[APP_MSG_BUF_SIZE];
    static uint32_t msgIdx = 0;
    BaseType_t recvRet; // receive return value
    char c;

    if(xQueue2 == NULL) {
        // do nothing
    } else {
        recvRet = xQueueReceive(xQueue2, (void *)&c, (TickType_t)0);
        if(recvRet != pdTRUE) {
            // do nothing
        } else if(msgIdx >= APP_MSG_BUF_SIZE) {
            printf("msg buf ovf\n");
            while(1)
                ;
        } else if(c != '\0'){
            msg[msgIdx] = c;
            msgIdx++;
        } else {
            msg[msgIdx] = c;
            printf("%s\n", msg);
            msgIdx = 0;
            msg[0] = '\0';
        }
    }
}

static void handleUserIn(void) {
    static char userIn[APP_USER_INPUT_BUF_SIZE];
    static uint32_t userInIdx = 0;
    int delay = -1;
    char c;

    while(uart0_readNonBlock(&c, 1)) {
        printf("%c", c);
        if(userInIdx >= APP_USER_INPUT_BUF_SIZE) {
            printf("user input buf ovf\n");
        } else if(c != '\r') {
            userIn[userInIdx] = c;
            userInIdx++;
        } else if(userInIdx < 7){ // min expected num of chars 'delay 1'
            printf("\n");
            printf("malformed user input\n");
            // resetting everything
            userIn[0] = '\0';
            userInIdx = 0;
        } else {
            printf("\n");
            userIn[userInIdx] = '\0';
            userInIdx++;
            sscanf(userIn, "delay %d", &delay);
            if(delay >= 1) {
                delay_t delayT = (delay_t)delay;
                if(xQueue1 != NULL) {
                    xQueueSend(xQueue1, (void *)&delayT, (TickType_t)10);
                }
            } else {
                printf("ignored\n");
            }
            // resetting everything
            userIn[0] = '\0';
            userInIdx = 0;
        }
    }
}

static void app_myTaskA( void * pvParameters ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)pvParameters;

    for( ; ; ) {
        printMsgsFromQ2();
        handleUserIn();
    }
    (void)pvParameters;
}

static void app_myTaskB( void * pvParameters ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)pvParameters;
    delay_t delayT = 1000, tempDelayT;
    BaseType_t recvRet = pdFALSE; // receive return value
    uint8_t ledSt = 0;
    uint16_t nth = 0;
    static char msg[] = "blinked";
    uint16_t i;

    for( ; ; ) {
        if(xQueue1 != NULL) {
            recvRet = xQueueReceive(xQueue1, (void *)&tempDelayT, (TickType_t)0);
        }
        if(recvRet != pdTRUE) {
            // do nothing
        } else {
            delayT = tempDelayT;
        }
        vTaskDelay( pdMS_TO_TICKS( delayT ) );
        ledSt = !ledSt;
        util_ledSet(ledSt);

        // no need to execute below lines if q2 does not exist
        if(xQueue2 == NULL) {
            continue;
        }

        nth++;
        if(nth == APP_BLINKED_MSG_EVERY_NTH) {
            nth = 0;
            for(i = 0; i < (sizeof(msg)/sizeof(char)); ++i) {
                xQueueSend(xQueue2, (void *)&msg[i], (TickType_t)10);
            }
        }
    }
}