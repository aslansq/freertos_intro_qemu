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
#define TIMER_FREQUENCY	  ( 1UL )

void demo_init(void) {
    TIMER_INT_CLEAR();
    TM0->CTRL |= CMSDK_TIMER_CTRL_IRQEN_Msk;
    TM0->RELOAD = ( configCPU_CLOCK_HZ / TIMER_FREQUENCY ) + 1UL;
    TM0->CTRL |= CMSDK_TIMER_CTRL_EN_Msk;
    NVIC_SetPriority( TIMER0_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY );
    NVIC_EnableIRQ( TIMER0_IRQn );

    vTaskStartScheduler();

    for( ; ; )
    {
    }
}

void TIMER0_Handler( void )
{
	/* Clear interrupt. */
	TIMER_INT_CLEAR();
    demo_hw_led_toggle();
}
