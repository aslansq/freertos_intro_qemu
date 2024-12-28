#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "demo_hw.h"

#define APP_TASK_INPUT_PRIORITY (tskIDLE_PRIORITY + 1)
#define APP_TASK_LED_PRIORITY   (tskIDLE_PRIORITY + 1)
#define APP_DEFAULT_TASK_STACK_SIZE 1024

static void _taskInput(void *parameter);
static void _taskLed(void *parameter);

static int __ledDelay = 1000;

void demo_init(void) {
    xTaskCreate(_taskInput,
                "in",
                APP_DEFAULT_TASK_STACK_SIZE,
                NULL,
                APP_TASK_INPUT_PRIORITY,
                NULL);

    xTaskCreate(_taskLed,
                "led",
                APP_DEFAULT_TASK_STACK_SIZE,
                NULL,
                APP_TASK_LED_PRIORITY,
                NULL);

    /* Start the tasks and timer running. */
    vTaskStartScheduler();
}

static void _taskInput( void * parameter ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)parameter;
    demo_hw_term_writeLine("Enter LED delay(ms):");
    int inledDelay = 0;
    char buf[100];
    int r;

    for( ;; ) {
        r = demo_hw_term_readLine(buf, sizeof(buf));
        if(r >= 0) {
            inledDelay = atoi(buf);
            __ledDelay = inledDelay;
            sprintf(buf, "Led delay updated to(ms): %d", __ledDelay);
            demo_hw_term_writeLine(buf);
        }
    }
}

static void _taskLed( void * parameter ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)parameter;
    for( ;; ) {
        demo_hw_led_toggle();
        vTaskDelay( pdMS_TO_TICKS( __ledDelay ) );
    }
}