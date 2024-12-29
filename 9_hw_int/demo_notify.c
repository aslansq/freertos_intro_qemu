/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
// demo hardware
#include "demo_hw.h"
#include "CMSDK_CM3.h"
#include "semphr.h"

#define LOOP_TASK_PRIORTY       (tskIDLE_PRIORITY + 1)
#define PRINT_VAL_TASK_PRIORITY (tskIDLE_PRIORITY + 2)
#define DEFAULT_TASK_STACK_SIZE (1024u)

#define TM0 CMSDK_TIMER0
#define TIMER_INT_CLEAR() (TM0->INTCLEAR |= CMSDK_TIMER_INTCLEAR_Msk)
#define TIMER_FREQUENCY   ( 1UL )

#define PRIO_ISR_TIMER configMAX_SYSCALL_INTERRUPT_PRIORITY // the hardware priority of the interrupt

static void _loop( void * pvParameters );
static void _printValue( void * pvParameters );
static uint8_t _adcVal = 0;

TraceISRHandle_t _traceTmIsrHandle;
TaskHandle_t _printValueTaskHandle = NULL;

void demo_init(void) {
    xTraceISRRegister("t", PRIO_ISR_TIMER, &_traceTmIsrHandle);


    TIMER_INT_CLEAR();
    TM0->CTRL |= CMSDK_TIMER_CTRL_IRQEN_Msk;
    TM0->RELOAD = ( configCPU_CLOCK_HZ / TIMER_FREQUENCY ) + 1UL;
    TM0->CTRL |= CMSDK_TIMER_CTRL_EN_Msk;
    NVIC_SetPriority( TIMER0_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY );
    NVIC_EnableIRQ( TIMER0_IRQn );

    xTaskCreate(
        _printValue,             // pvTaskCode
        "p",                     // pcName
        DEFAULT_TASK_STACK_SIZE, // uxStackDepth
        NULL,                    // pvParameters
        PRINT_VAL_TASK_PRIORITY, // uxPriority
        &_printValueTaskHandle    // pxCreatedTask
    );

    configASSERT(!(_printValueTaskHandle == NULL));

    xTaskCreate(
        _loop,                   // pvTaskCode
        "l",                     // pcName
        DEFAULT_TASK_STACK_SIZE, // uxStackDepth
        NULL,                    // pvParameters
        LOOP_TASK_PRIORTY,       // uxPriority
        NULL                     // pxCreatedTask
    );

    vTaskStartScheduler();

    for( ; ; ) {
    }
}

static void _loop( void * pvParameters ) {
    (void)pvParameters;
    for( ; ; ) {
        // do nothing
    }
}


static void _printValue( void * pvParameters ) {
    (void)pvParameters;
    uint32_t ulNotificationValue;
    for( ; ; ) {
        ulNotificationValue = ulTaskNotifyTake(
            pdTRUE,
            portMAX_DELAY
        );

        configASSERT(!(ulNotificationValue == 0));
        demo_hw_term_printf("%d\n", (int)_adcVal);
    }
}

void TIMER0_Handler( void )
{
    xTraceISRBegin(_traceTmIsrHandle);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    /* Clear interrupt. */
    TIMER_INT_CLEAR();
    _adcVal = demo_hw_adc_read();
    vTaskNotifyGiveFromISR(_printValueTaskHandle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    xTraceISREnd(0);
}
