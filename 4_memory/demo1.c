#include <stdio.h>
#include <stdint.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "demo_hw.h"

#define DEFAULT_PRIORITY   (tskIDLE_PRIORITY + 1)
#define DEFAULT_STACK_SIZE (1024u)

static void _taskA( void * pvParameters );

void demo_init(void) {

    xTaskCreate(_taskA,
                "A",
                DEFAULT_STACK_SIZE,
                NULL,
                DEFAULT_PRIORITY,
                NULL );

    vTaskStartScheduler();

    for( ; ; )
    {
    }
}

// demo 1 : overflow stack by recursive call
static void _taskA( void * pvParameters ) {
    // this made static, so it does not effect stack
    static int taskEntryCount = 0;
    for( ;; ) {
        demo_hw_term_printf("rem: %d tec: %d\n", (int)uxTaskGetStackHighWaterMark(NULL), taskEntryCount++);
        // lets ovf to see what happens to RTOS
        _taskA(NULL);
    }
}
//rem: 0 tec: 574
//rem: 0 tec: 575
//re
//
//Stack overflow in A
