/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
// demo hardware
#include "demo_hw.h"

#define DEFAULT_TASK_L_PRIO     (tskIDLE_PRIORITY + 1)
#define DEFAULT_TASK_M_PRIO     (tskIDLE_PRIORITY + 2)
#define DEFAULT_TASK_H_PRIO     (tskIDLE_PRIORITY + 3)
#define DEFAULT_TASK_STACK_SIZE (1024u)

// all ms
#define TASK_L_WORK_TIME         ( 250u  )
#define TASK_M_WORK_TIME         ( 5000u )
#define TASK_H_WORK_TIME         ( 500u  )
#define TASKS_DEFAULT_SLEEP_TIME ( 500u  )

#define TICK_TO_MS(tick) ((tick) * portTICK_PERIOD_MS)

static void _taskL(void *pvParameters);
static void _taskM(void *pvParameters);
static void _taskH(void *pvParameters);

static SemaphoreHandle_t _mutex;

void demo_init(void) {
    _mutex = xSemaphoreCreateBinary();
    xSemaphoreGive(_mutex);

    xTaskCreate(
        _taskL,
        "L",
        DEFAULT_TASK_STACK_SIZE,
        NULL,
        DEFAULT_TASK_L_PRIO,
        NULL
    );

    xTaskCreate(
        _taskM,
        "M",
        DEFAULT_TASK_STACK_SIZE,
        NULL,
        DEFAULT_TASK_M_PRIO,
        NULL
    );

    xTaskCreate(
        _taskH,
        "H",
        DEFAULT_TASK_STACK_SIZE,
        NULL,
        DEFAULT_TASK_H_PRIO,
        NULL
    );

    vTaskStartScheduler();

    for( ; ; ) {
    }
}

static void _taskL(void *pvParameters) {
    (void)pvParameters;
    TickType_t timestamp;
    for( ; ; ) {
        demo_hw_term_writeLine("(L) trying to acquire lock.");
        timestamp = xTaskGetTickCount();
        xSemaphoreTake(_mutex, portMAX_DELAY);
        demo_hw_term_printf("(L) lock acquired. Wait time: %d\n", TICK_TO_MS(xTaskGetTickCount() - timestamp));

        timestamp = xTaskGetTickCount();
        while(TICK_TO_MS(xTaskGetTickCount() - timestamp) < TASK_L_WORK_TIME) {
           __asm__("nop"); // work hard by doing nothing
        }
        demo_hw_term_writeLine("(L) lock released.");
        xSemaphoreGive(_mutex);
        demo_hw_term_writeLine("(L) sleepy.");
        vTaskDelay( pdMS_TO_TICKS( TASKS_DEFAULT_SLEEP_TIME ) );
    }
}

static void _taskM(void *pvParameters) {
    static uint8_t firsEntry = 0;
    if(firsEntry == 0) {
        firsEntry = 1;
        vTaskDelay( pdMS_TO_TICKS( 100 ) );
    }
    (void)pvParameters;
    TickType_t timestamp;
    for( ; ; ) {
        timestamp = xTaskGetTickCount();
        demo_hw_term_writeLine("(M) worky work.");
        while(TICK_TO_MS(xTaskGetTickCount() - timestamp) < TASK_M_WORK_TIME) {
            __asm__("nop"); // work hard by doing nothing
        }
        demo_hw_term_writeLine("(M) sleppy.");
        vTaskDelay( pdMS_TO_TICKS( TASKS_DEFAULT_SLEEP_TIME ) );
    }
}

static void _taskH(void *pvParameters) {
    static uint8_t firsEntry = 0;
    if(firsEntry == 0) {
        firsEntry = 100;
        vTaskDelay( pdMS_TO_TICKS( 1 ) );
    }
    (void)pvParameters;
    TickType_t timestamp;
    for( ; ; ) {
        demo_hw_term_writeLine("(H) trying to acquire lock.");
        timestamp = xTaskGetTickCount();
        xSemaphoreTake(_mutex, portMAX_DELAY);
        demo_hw_term_printf("(H) lock acquired. Wait time: %d\n", TICK_TO_MS(xTaskGetTickCount() - timestamp));

        timestamp = xTaskGetTickCount();
        while(TICK_TO_MS(xTaskGetTickCount() - timestamp) < TASK_H_WORK_TIME) {
            __asm__("nop"); // work hard by doing nothing
        }
        demo_hw_term_writeLine("(H) lock released.");
        xSemaphoreGive(_mutex);
        demo_hw_term_writeLine("(H) sleepy.");
        vTaskDelay( pdMS_TO_TICKS( TASKS_DEFAULT_SLEEP_TIME ) );
    }
}
