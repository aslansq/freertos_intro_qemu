#include <stdio.h>
#include <stdint.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "demo_hw.h"

#define DEFAULT_PRIORITY   (tskIDLE_PRIORITY + 1)
#define DEFAULT_STACK_SIZE (1024u)

static void _taskA( void * pvParameters );

/* Structure that will hold the TCB of the task being created. */
static StaticTask_t __taskA_buffer;
static StackType_t  __taskA_stack[DEFAULT_STACK_SIZE];

void demo_init(void) {

    xTaskCreateStatic(
                _taskA,
                "A",
                DEFAULT_STACK_SIZE,
                NULL,
                DEFAULT_PRIORITY,
                __taskA_stack,
                &__taskA_buffer );

    vTaskStartScheduler();

    for( ; ; )
    {
    }
}

// demo 6 : overflow of static stack by recursive call
static void _taskA( void * pvParameters ) {
    (void)pvParameters;
    // these made static, so it does not effect stack
    static int taskEntryCount = 0;
    static int remStack;
    remStack = (int)uxTaskGetStackHighWaterMark(NULL);
    for( ;; ) {
        if(remStack) {
            demo_hw_term_printf("rem: %d tec: %d\n", remStack, taskEntryCount);
        } else {
            demo_hw_term_printf("no remStack tec: %d\n", taskEntryCount);
        }
        taskEntryCount++;
        // lets ovf to see what happens to RTOS
        _taskA(NULL);
    }
}
// it goes to hardfault instead of stack ovf hook. who knows why
//rem: 0 tec: 497
//rem: 0 tec: 498
//rem: 0 tec: 499
//Calling prvGetRegistersFromStack() from fault handle
