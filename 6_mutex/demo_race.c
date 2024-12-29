/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "demo_hw.h"

#define DEFAULT_PRIORITY   (tskIDLE_PRIORITY + 1)
#define DEFAULT_STACK_SIZE (1024u)

static void _incTask(void * pvParameters);
static int __sharedVar = 0;

void demo_init(void) {

    xTaskCreate(_incTask,
                "A",
                DEFAULT_STACK_SIZE,
                NULL,
                DEFAULT_PRIORITY,
                NULL );

    xTaskCreate(_incTask,
                "B",
                DEFAULT_STACK_SIZE,
                NULL,
                DEFAULT_PRIORITY,
                NULL );

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    for( ; ; ) {
    }
}

static int _myRand(void) {
    static int ranDurOfOpLut[] = {973, 594, 28, 651, 73, 680, 452, 504}; // random duration of operation look up table
    static int ranIdx = 0;
    ranIdx++;
    ranIdx = ranIdx < 8 ? ranIdx : 0;
    // looks random enough, this particular environment is not happy calling rand function from stdlib
    return ranDurOfOpLut[ranIdx % 8];
}

static void _incTask(void * pvParameters) {
    int localVar = 0;
    int ranDurOfOp = 0;
    for( ; ; ) {
        ranDurOfOp = _myRand();
        localVar = __sharedVar;
        localVar++;
        vTaskDelay( pdMS_TO_TICKS( ranDurOfOp ) );
        __sharedVar = localVar;
        demo_hw_term_printf("%d\n", __sharedVar);
    }
}