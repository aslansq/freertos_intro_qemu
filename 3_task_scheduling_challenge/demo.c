#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "demo_hw.h"

#define TASK_INPUT_PRIORITY (tskIDLE_PRIORITY + 1)
#define TASK_LED_PRIORITY   (tskIDLE_PRIORITY + 1)
#define DEFAULT_TASK_STACK_SIZE 1024

static void _taskInput(void *parameter);
static void _taskLed(void *parameter);

static int _ledDelay = 1000;

void demo_init(void) {
    xTaskCreate(_taskInput,
                "in",
                DEFAULT_TASK_STACK_SIZE,
                NULL,
                TASK_INPUT_PRIORITY,
                NULL);

    xTaskCreate(_taskLed,
                "led",
                DEFAULT_TASK_STACK_SIZE,
                NULL,
                TASK_LED_PRIORITY,
                NULL);

    /* Start the tasks and timer running. */
    vTaskStartScheduler();
}

static void _taskInput( void * parameter ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)parameter;
    demo_hw_term_writeLine("Enter LED delay(ms):");
    int inledDelay = 0;
    int r;
    char buf[50];

    for( ;; ) {
        r = demo_hw_term_readLine(buf, sizeof(buf));
        if(r >= 0) {
            inledDelay = atoi(buf);
            _ledDelay = inledDelay;
            demo_hw_term_printf("Led delay updated to(ms): %d", _ledDelay);
            demo_hw_term_writeChar('\n');
        }
    }
}

static void _taskLed( void * parameter ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)parameter;
    for( ;; ) {
        demo_hw_led_toggle();
        vTaskDelay( pdMS_TO_TICKS( _ledDelay ) );
    }
}