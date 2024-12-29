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
static SemaphoreHandle_t _adcSemphr = NULL;

TraceISRHandle_t _traceTmIsrHandle;

void demo_init(void) {
    xTraceISRRegister("t", PRIO_ISR_TIMER, &_traceTmIsrHandle);


    TIMER_INT_CLEAR();
    TM0->CTRL |= CMSDK_TIMER_CTRL_IRQEN_Msk;
    TM0->RELOAD = ( configCPU_CLOCK_HZ / TIMER_FREQUENCY ) + 1UL;
    TM0->CTRL |= CMSDK_TIMER_CTRL_EN_Msk;
    NVIC_SetPriority( TIMER0_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY );
    NVIC_EnableIRQ( TIMER0_IRQn );

    _adcSemphr = xSemaphoreCreateBinary();

    if(_adcSemphr == NULL) {
        demo_hw_term_writeLine("err _adcSemphr");
        while(1)
            ;
    }

    xTaskCreate(
        _printValue,             // pvTaskCode
        "p",                     // pcName
        DEFAULT_TASK_STACK_SIZE, // uxStackDepth
        NULL,                    // pvParameters
        PRINT_VAL_TASK_PRIORITY, // uxPriority
        NULL                     // pxCreatedTask
    );

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
    for( ; ; ) {
        xSemaphoreTake(_adcSemphr, portMAX_DELAY);
        demo_hw_term_printf("%d\n", (int)_adcVal);
    }
}

void TIMER0_Handler( void )
{
    xTraceISRBegin(_traceTmIsrHandle);
    /* Clear interrupt. */
    TIMER_INT_CLEAR();
    BaseType_t p;
    _adcVal = demo_hw_adc_read();
    xSemaphoreGiveFromISR(_adcSemphr, &p);
    portYIELD_FROM_ISR(p);
    xTraceISREnd(0);
}
