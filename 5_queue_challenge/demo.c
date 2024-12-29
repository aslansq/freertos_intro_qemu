/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "demo_hw.h"

#define DEFAULT_PRIORITY   (tskIDLE_PRIORITY + 1)
#define DEFAULT_STACK_SIZE (1024u)

#define MSG_BUF_SIZE (100u)
#define USER_INPUT_BUF_SIZE (100u)

#define BLINKED_MSG_EVERY_NTH (100u)

static void _printMsgsFromQ2(void);
static void _handleUserIn(void);
static void _taskA(void * pvParameters);
static void _taskB(void * pvParameters);

static QueueHandle_t _xQueue1 = NULL;
static QueueHandle_t _xQueue2 = NULL;

typedef uint16_t delay_t;

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

    // can hold 10 int32_t
    _xQueue1 = xQueueCreate( 10, sizeof( delay_t ) );
    _xQueue2 = xQueueCreate( MSG_BUF_SIZE, sizeof( char ) );

    if(_xQueue1 == NULL) {
        demo_hw_term_writeLine("_xQueue1 null");
    }

    if(_xQueue2 == NULL) {
        demo_hw_term_writeLine("_xQueue2 null");
    }

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }
}

static void _printMsgsFromQ2(void) {
    static char msg[MSG_BUF_SIZE];
    static uint32_t msgIdx = 0;
    BaseType_t recvRet; // receive return value
    char c;

    if(_xQueue2 == NULL) {
        // do nothing
    } else {
        recvRet = xQueueReceive(_xQueue2, (void *)&c, (TickType_t)0);
        if(recvRet != pdTRUE) {
            // do nothing
        } else if(msgIdx >= MSG_BUF_SIZE) {
            demo_hw_term_writeLine("msg buf ovf");
            while(1)
                ;
        } else if(c != '\0'){
            msg[msgIdx] = c;
            msgIdx++;
        } else {
            msg[msgIdx] = c;
            demo_hw_term_printf("%s\n", msg);
            msgIdx = 0;
            msg[0] = '\0';
        }
    }
}

static void _handleUserIn(void) {
    static char userIn[USER_INPUT_BUF_SIZE];
    static uint32_t userInIdx = 0;
    int delay = -1;
    char c;

    while(demo_hw_term_readCharNonBlock(&c)) {
        demo_hw_term_writeChar(c);
        if(userInIdx >= USER_INPUT_BUF_SIZE) {
            demo_hw_term_writeLine("user input buf ovf");
        } else if(c != '\r') {
            userIn[userInIdx] = c;
            userInIdx++;
        } else if(userInIdx < 7){ // min expected num of chars 'delay 1'
            demo_hw_term_writeChar('\n');
            demo_hw_term_writeLine("malformed user input");
            // resetting everything
            userIn[0] = '\0';
            userInIdx = 0;
        } else {
            demo_hw_term_writeChar('\n');
            userIn[userInIdx] = '\0';
            userInIdx++;
            sscanf(userIn, "delay %d", &delay);
            if(delay >= 1) {
                delay_t delayT = (delay_t)delay;
                if(_xQueue1 != NULL) {
                    xQueueSend(_xQueue1, (void *)&delayT, (TickType_t)10);
                }
            } else {
                demo_hw_term_writeLine("ignored");
            }
            // resetting everything
            userIn[0] = '\0';
            userInIdx = 0;
        }
    }
}

static void _taskA( void * pvParameters ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)pvParameters;

    for( ; ; ) {
        _printMsgsFromQ2();
        _handleUserIn();
    }
    (void)pvParameters;
}

static void _taskB( void * pvParameters ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)pvParameters;
    delay_t delayT = 1000, tempDelayT;
    BaseType_t recvRet = pdFALSE; // receive return value
    uint16_t nth = 0;
    static char msg[] = "blinked";
    uint16_t i;

    for( ; ; ) {
        if(_xQueue1 != NULL) {
            recvRet = xQueueReceive(_xQueue1, (void *)&tempDelayT, (TickType_t)0);
        }
        if(recvRet != pdTRUE) {
            // do nothing
        } else {
            delayT = tempDelayT;
        }
        vTaskDelay( pdMS_TO_TICKS( delayT ) );
        demo_hw_led_toggle();

        // no need to execute below lines if q2 does not exist
        if(_xQueue2 == NULL) {
            continue;
        }

        nth++;
        if(nth == BLINKED_MSG_EVERY_NTH) {
            nth = 0;
            for(i = 0; i < (sizeof(msg)/sizeof(char)); ++i) {
                xQueueSend(_xQueue2, (void *)&msg[i], (TickType_t)10);
            }
        }
    }
}