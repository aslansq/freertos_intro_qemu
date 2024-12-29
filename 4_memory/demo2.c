#include "demo_hw.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

#define DEFAULT_PRIORITY   (tskIDLE_PRIORITY + 1)
#define DEFAULT_STACK_SIZE (1024u)

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

    for( ; ; )
    {
    }
}

// This task survives, if there is no other task.
// demo 2 : allocating huge array in stack to ovf.
static void _taskA( void * pvParameters ) {
    uint32_t myHugeArray[DEFAULT_STACK_SIZE+1];
    demo_hw_term_printf("remStack: %d\n", (int)uxTaskGetStackHighWaterMark(NULL));
    uint32_t anotherU32 = 0;
    demo_hw_term_printf("remStack: %d\n", (int)uxTaskGetStackHighWaterMark(NULL));
    uint32_t idx = 0;

    while(1) { // to see if task survives and prints remaining stack constantly
        // implementing sth so compiler does not optimize out
        myHugeArray[idx] = idx;
        myHugeArray[idx]++;
        myHugeArray[idx]--;
        anotherU32++;
        idx++;
        if(idx == (DEFAULT_STACK_SIZE+1)) {
            idx = 0;
        }

        int remStack = (int)uxTaskGetStackHighWaterMark(NULL);
        if (remStack) {
            demo_hw_term_printf("remStack: %d\n", remStack);
        } else {
            demo_hw_term_printf("no remStack\n");
        }
    }
}

// output when when _taskB defined.
//no remStack
//no
//
//Stack overflow in A
// dummy task. purpose of this function: context switching happens between A and B
static void _taskB( void * pvParameters ) {
    uint32_t arr[DEFAULT_STACK_SIZE/2];
    uint32_t idx = 0;
    for(;;) {
        // implementing sth so compiler does not optimize out
        arr[idx] = idx;
        arr[idx]++;
        arr[idx]--;
        idx++;
        if(idx == DEFAULT_STACK_SIZE/2) {
            idx = 0;
        }
    }
}