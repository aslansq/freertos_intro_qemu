/* This file demonstrates memory management in FreeRTOS
 * define APP_DEMO macro with value APP_DEMO_[1..6] or [1..6]
 * Example:
 * #define APP_DEMO APP_DEMO_1
 * #define APP_DEMO 1
 */
/* Standard includes. */
#include <stdio.h>
#include <stdint.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

// demo 1 : overflow stack by recursive call
#define APP_DEMO_1 1
// demo 2 : allocating huge array in stack to ovf
#define APP_DEMO_2 2
// demo 3 : ovf heap u32 at a time
#define APP_DEMO_3 3
// demo 4 : ovf heap in single shot
#define APP_DEMO_4 4
// demo 5 : properly malloc and free. this should be fine
#define APP_DEMO_5 5
// demo 6 : overflow of static stack by recursive call
#define APP_DEMO_6 6

#ifndef APP_DEMO
    #define APP_DEMO APP_DEMO_1
#endif

#define APP_DEFAULT_PRIORITY   (tskIDLE_PRIORITY + 1)
#define APP_DEFAULT_STACK_SIZE (1024u)

static void app_myTaskA( void * pvParameters );

#if APP_DEMO == APP_DEMO_2
static void app_myTaskB( void * pvParameters );
#endif // APP_DEMO_2

#if APP_DEMO == APP_DEMO_6
/* Structure that will hold the TCB of the task being created. */
static StaticTask_t app_myTaskA_buffer;
static StackType_t app_myTaskA_stack[APP_DEFAULT_STACK_SIZE];
#endif // APP_DEMO_6

void app_init(void) {

#if APP_DEMO != APP_DEMO_6
    xTaskCreate(app_myTaskA,
                "A",
                APP_DEFAULT_STACK_SIZE,
                NULL,
                APP_DEFAULT_PRIORITY,
                NULL );
#else // APP_DEMO_6
    xTaskCreateStatic(
                app_myTaskA,
                "A",
                APP_DEFAULT_STACK_SIZE,
                NULL,
                APP_DEFAULT_PRIORITY,
                app_myTaskA_stack,
                &app_myTaskA_buffer );
#endif

#if APP_DEMO == APP_DEMO_2
    xTaskCreate(app_myTaskB,
                "B",
                APP_DEFAULT_STACK_SIZE,
                NULL,
                APP_DEFAULT_PRIORITY,
                NULL );
#endif // APP_DEMO_2

    vTaskStartScheduler();

    for( ; ; )
    {
    }
}

#if APP_DEMO == APP_DEMO_1
// demo 1 : overflow stack by recursive call
static void app_myTaskA( void * pvParameters ) {
    // this made static, so it does not effect stack
    static int taskEntryCount = 0;
    for( ;; ) {
        printf("rem: %d tec: %d\n", (int)uxTaskGetStackHighWaterMark(NULL), taskEntryCount++);
        // lets ovf to see what happens to RTOS
        app_myTaskA(NULL);
    }
}
//rem: 0 tec: 574
//rem: 0 tec: 575
//re
//
//Stack overflow in A
#endif // APP_DEMO_1

#if APP_DEMO == APP_DEMO_2
// This task survives, if there is no other task.
// demo 2 : allocating huge array in stack to ovf.
static void app_myTaskA( void * pvParameters ) {
    uint32_t myHugeArray[APP_DEFAULT_STACK_SIZE+1];
    printf("remStack: %d\n", (int)uxTaskGetStackHighWaterMark(NULL));
    uint32_t anotherU32 = 0;
    printf("remStack: %d\n", (int)uxTaskGetStackHighWaterMark(NULL));
    uint32_t idx = 0;

    while(1) { // to see if task survives and prints remaining stack constantly
        // implementing sth so compiler does not optimize out
        myHugeArray[idx] = idx;
        myHugeArray[idx]++;
        myHugeArray[idx]--;
        anotherU32++;
        idx++;
        if(idx == (APP_DEFAULT_STACK_SIZE+1)) {
            idx = 0;
        }

        int remStack = (int)uxTaskGetStackHighWaterMark(NULL);
        if (remStack) {
            printf("remStack: %d\n", remStack);
        } else {
            printf("no remStack\n");
        }
    }
}
// output when when app_myTaskB defined.
//no remStack
//no
//
//Stack overflow in A
// dummy task. purpose of this function: context switching happens between A and B
static void app_myTaskB( void * pvParameters ) {
    uint32_t arr[APP_DEFAULT_STACK_SIZE/2];
    uint32_t idx = 0;
    for(;;) {
        // implementing sth so compiler does not optimize out
        arr[idx] = idx;
        arr[idx]++;
        arr[idx]--;
        idx++;
        if(idx == APP_DEFAULT_STACK_SIZE/2) {
            idx = 0;
        }
    }
}
#endif // APP_DEMO_2

#if APP_DEMO == APP_DEMO_3
// demo 3 : ovf heap u32 at a time
static void app_myTaskA( void * pvParameters ) {
    for(;;) {
        // lets ovf heap u32 at a time
        uint32_t *ptr = (uint32_t *)pvPortMalloc(sizeof(uint32_t));
        if(ptr != NULL) { // doing sth so compiler does not complain
            ptr[0]++;
        }
        uint32_t remHeap = xPortGetFreeHeapSize();
        if(remHeap) {
            printf("remHeap %d\n", (int)remHeap);
        } else {
            printf("no heapRem\n");
        }
    }
}
//remHeap 40
//remHeap 24
//no heapRem
//
//
//Malloc failed
#endif // APP_DEMO_3

#if APP_DEMO == APP_DEMO_4
// demo 4: ovf heap in single shot
static void app_myTaskA( void * pvParameters ) {
    // heap ovf single shot
    uint32_t *ptr = (uint32_t *)pvPortMalloc(sizeof(uint32_t)*UINT32_MAX);
    if(ptr != NULL) { // doing sth so compiler does not complain
        ptr[0]++;
    }
    uint32_t remHeap = xPortGetFreeHeapSize();
    if(remHeap) {
        printf("remHeap %d\n", (int)remHeap);
    } else {
        printf("no heapRem\n");
    }
    for(;;) {
    }
}
//
//
//Malloc failed
#endif // APP_DEMO_4

#if APP_DEMO == APP_DEMO_5
// demo 5: heap alloc and free. this should be fine
static void app_myTaskA( void * pvParameters ) {
    for(;;) {
        // lets ovf heap u32 at a time
        uint32_t *ptr = (uint32_t *)pvPortMalloc(sizeof(uint32_t));
        if(ptr != NULL) { // doing sth so compiler does not complain
            ptr[0]++;
        }
        uint32_t remHeap = xPortGetFreeHeapSize();
        if(remHeap) {
            printf("remHeap %d\n", (int)remHeap);
        } else {
            printf("no heapRem\n");
        }
        vPortFree(ptr);
    }
}
// it is fine, it just repeats below line
//remHeap 57192
//remHeap 57192
//remHeap 57192
#endif // APP_DEMO_5

#if APP_DEMO == APP_DEMO_6
// demo 6 : overflow of static stack by recursive call
static void app_myTaskA( void * pvParameters ) {
    // these made static, so it does not effect stack
    static int taskEntryCount = 0;
    static int remStack;
    remStack = (int)uxTaskGetStackHighWaterMark(NULL);
    for( ;; ) {
        if(remStack) {
            printf("rem: %d tec: %d\n", remStack, taskEntryCount);
        } else {
            printf("no remStack tec: %d\n", taskEntryCount);
        }
        taskEntryCount++;
        // lets ovf to see what happens to RTOS
        app_myTaskA(NULL);
    }
}
// it goes to hardfault instead of stack ovf hook. who knows why
//rem: 0 tec: 497
//rem: 0 tec: 498
//rem: 0 tec: 499
//Calling prvGetRegistersFromStack() from fault handle
#endif // APP_DEMO_1