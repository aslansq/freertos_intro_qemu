/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
// demo hardware
#include "demo_hw.h"
#include "CMSDK_CM3.h"

#define DEFAULT_TASK_LOOP_PRIORITY (tskIDLE_PRIORITY + 1)
#define DEFAULT_TASK_STACK_SIZE    (1024u)

#define TM0 CMSDK_TIMER0
#define TIMER_INT_CLEAR() (TM0->INTCLEAR |= CMSDK_TIMER_INTCLEAR_Msk)
#define TIMER_FREQUENCY   ( 1UL )

static void _printValue( void * pvParameters );

static volatile uint32_t _isrCounter = 0;

void demo_init(void) {
    TIMER_INT_CLEAR();
    TM0->CTRL |= CMSDK_TIMER_CTRL_IRQEN_Msk;
    TM0->RELOAD = ( configCPU_CLOCK_HZ / TIMER_FREQUENCY ) + 1UL;
    TM0->CTRL |= CMSDK_TIMER_CTRL_EN_Msk;
    NVIC_SetPriority( TIMER0_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY );
    NVIC_EnableIRQ( TIMER0_IRQn );

    xTaskCreate(
        _printValue,                  // pvTaskCode
        "p",                    // pcName
        DEFAULT_TASK_STACK_SIZE,    // uxStackDepth
        NULL,                       // pvParameters
        DEFAULT_TASK_LOOP_PRIORITY, // uxPriority
        NULL                        // pxCreatedTask
    );

    vTaskStartScheduler();

    for( ; ; ) {
    }
}

static void _printValue( void * pvParameters ) {
    (void)pvParameters;
    for( ; ; ) {
        vTaskDelay( pdMS_TO_TICKS( 1300 ) );
        demo_hw_term_printf("%d\n", (int)_isrCounter);
        taskENTER_CRITICAL();
        _isrCounter--;
        taskEXIT_CRITICAL();
    }
}

void TIMER0_Handler( void )
{
    /* Clear interrupt. */
    TIMER_INT_CLEAR();
    UBaseType_t uxSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR();
    _isrCounter++;
    taskEXIT_CRITICAL_FROM_ISR(uxSavedInterruptStatus);
}
