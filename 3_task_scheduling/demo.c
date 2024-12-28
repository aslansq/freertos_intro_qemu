/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "demo_hw.h"


#define LOOP_PRIORITY           (tskIDLE_PRIORITY + 1)
#define TASK1_PRIORITY          (tskIDLE_PRIORITY + 2)
#define TASK2_PRIORITY          (tskIDLE_PRIORITY + 3)
#define DEFAULT_TASK_STACK_SIZE (1024u)

static void _task1(void *parameter);
static void _task2(void *parameter);
static void _loop(void *parameter);
static void _slowTermWriteLine(const char *s);

TaskHandle_t __task1Handle = NULL;
TaskHandle_t __task2Handle = NULL;

void demo_init(void) {
    xTaskCreate(_task1,
                "_task1",
                DEFAULT_TASK_STACK_SIZE,
                NULL,
                TASK1_PRIORITY,
                &__task1Handle);

    xTaskCreate(_task2,
                "_task2",
                DEFAULT_TASK_STACK_SIZE,
                NULL,
                TASK2_PRIORITY,
                &__task2Handle);

    xTaskCreate(_loop,
                "_loop",
                DEFAULT_TASK_STACK_SIZE,
                NULL,
                LOOP_PRIORITY,
                NULL);

    /* Start the tasks and timer running. */
    vTaskStartScheduler();
}

static void _slowTermWriteChar(const char c) {
    int j;
    for(j = 0; j < 10000000; j++) {
        __asm__("nop");
    }
    demo_hw_term_writeChar(c);
}

static void _slowTermWriteLine(const char *s) {
    for (size_t i = 0; s[i] != '\0'; i++) {
        _slowTermWriteChar(s[i]);
    }
    demo_hw_term_writeChar('\n');
    demo_hw_term_writeChar('\r');
}


static void _loop(void *parameter) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)parameter;
    uint8_t i = 0;
    while(1) {
        for(i = 0; i < 3; ++i)
        {
            vTaskSuspend( __task2Handle );
            vTaskDelay( pdMS_TO_TICKS( 2000 ) );
            vTaskResume( __task2Handle );
            vTaskDelay( pdMS_TO_TICKS( 2000 ) );
        }

        if(__task1Handle != NULL) {
            vTaskDelete(__task1Handle);
            __task1Handle = NULL;
            demo_hw_term_writeLine("Task1 deleted.");
        }
    }
}

static void _task1( void * parameter ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)parameter;
    for( ;; ) {
        _slowTermWriteLine("Barkadeer brig Arr booty rum.");
        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
    }
}

static void _task2( void * parameter ) {
    /* Prevent the compiler warning about the unused parameter. */
    (void)parameter;
    for( ;; ) {
        vTaskDelay( pdMS_TO_TICKS( 100 ) );
        _slowTermWriteChar('*');
    }
}