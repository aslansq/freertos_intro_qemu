/* Standard includes. */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "uart.h"
#include "util.h"

#define APP_TASK_INPUT_PRIORITY (tskIDLE_PRIORITY + 1)
#define APP_TASK_LED_PRIORITY   (tskIDLE_PRIORITY + 1)
#define APP_DEFAULT_TASK_STACK_SIZE 1024

static void taskInput(void *parameter);
static void taskLed(void *parameter);

static int ledDelay = 1000;

void demo_init(void) {
    xTaskCreate(taskInput,
                "in",
                APP_DEFAULT_TASK_STACK_SIZE,
                NULL,
                APP_TASK_INPUT_PRIORITY,
                NULL);

    xTaskCreate(taskLed,
                "led",
                APP_DEFAULT_TASK_STACK_SIZE,
                NULL,
                APP_TASK_LED_PRIORITY,
                NULL);

    /* Start the tasks and timer running. */
    vTaskStartScheduler();
}

static void taskInput( void * parameter ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)parameter;
    printf("\nEnter LED delay(ms): \n");
    uint32_t inLedDelay = 0;

    for( ;; ) {
        uint8_t r =  uart0_readU32(&inLedDelay);
        if(r) {
            ledDelay = inLedDelay;
            printf("\nLed delay updated to(ms): %d\n", ledDelay);
        }
    }
}

static void taskLed( void * parameter ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)parameter;
    uint8_t ledSt = 1;
    for( ;; ) {
        util_ledSet(ledSt);
        ledSt = !ledSt;
        vTaskDelay( pdMS_TO_TICKS( ledDelay ) );
    }
}