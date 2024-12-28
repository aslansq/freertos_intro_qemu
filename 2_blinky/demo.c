/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
// demo hardware
#include "demo_hw.h"

#define DEFAULT_TASK_LOOP_PRIORITY (tskIDLE_PRIORITY + 1)
#define DEFAULT_TASK_STACK_SIZE    (1024u)

static void blinkTask(void * pvParameters);

void demo_init(void) {
    xTaskCreate(
        blinkTask,                  // pvTaskCode
        "blink",                    // pcName
        DEFAULT_TASK_STACK_SIZE,    // uxStackDepth
        NULL,                       // pvParameters
        DEFAULT_TASK_LOOP_PRIORITY, // uxPriority
        NULL                        // pxCreatedTask
    );

    vTaskStartScheduler();

    for( ; ; )
    {
    }
}

static void blinkTask( void * pvParameters ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)pvParameters;
    static uint8_t ledSt = 0;
    for( ;; ) {
        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
        ledSt = !ledSt;
        demo_hw_led_set(ledSt);
    }
}
