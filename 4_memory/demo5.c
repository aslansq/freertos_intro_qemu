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

// demo 5: heap alloc and free. this should be fine
static void _taskA( void * pvParameters ) {
    for(;;) {
        // lets ovf heap u32 at a time
        uint32_t *ptr = (uint32_t *)pvPortMalloc(sizeof(uint32_t));
        if(ptr != NULL) { // doing sth so compiler does not complain
            ptr[0]++;
        }
        uint32_t remHeap = xPortGetFreeHeapSize();
        if(remHeap) {
            demo_hw_term_printf("remHeap %d\n", (int)remHeap);
        } else {
            demo_hw_term_printf("no heapRem\n");
        }
        vPortFree(ptr);
    }
}
// it is fine, it just repeats below line
//remHeap 57192
//remHeap 57192
//remHeap 57192
