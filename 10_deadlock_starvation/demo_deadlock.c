// sorry this wont look like c code but a story
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
// demo hardware
#include "demo_hw.h"
#include "semphr.h"
#include <string.h>

#define CHOP_STICK_1_ID (0u)
#define CHOP_STICK_2_ID (1u)
#define CHOP_STICK_3_ID (2u)
#define CHOP_STICK_4_ID (3u)
#define CHOP_STICK_5_ID (4u)

#define CHOP_STICK_1_PRIO (0u)
#define CHOP_STICK_2_PRIO (1u)
#define CHOP_STICK_3_PRIO (2u)
#define CHOP_STICK_4_PRIO (3u)
#define CHOP_STICK_5_PRIO (4u)

#define NUM_OF_CHOP_STICKS (5u)

#define PARTY_LIGHT_PRIO     (tskIDLE_PRIORITY + 1)
#define CRUZ_EAT_PRIO        (tskIDLE_PRIORITY + 2)
#define DOUGLASS_EAT_PRIO    (tskIDLE_PRIORITY + 2)
#define HYPATIA_EAT_PRIO     (tskIDLE_PRIORITY + 2)
#define CONFUCIUS_EAT_PRIO   (tskIDLE_PRIORITY + 2)
#define ANTISTHENES_EAT_PRIO (tskIDLE_PRIORITY + 2)

#define PHILOSOPHER_MIND (1024u) // haha. it is stack

#define CRUZ_ID        (0u)
#define DOUGLASS_ID    (1u)
#define HYPATIA_ID     (3u)
#define CONFUCIUS_ID   (4u)
#define ANTISTHENES_ID (5u)

#define NUM_OF_PHILOSOPHERS (6u)

// time it takes for philosopher to reach for chopstick
#define TIME_TO_REACH_A_CHOP_STICK (100u)
// philosopher are nice they eat for some time and give chopsticks back
#define TIME_TO_EAT (1000u)

#define GET_CHOPSTICK(chopstick) \
vTaskDelay( pdMS_TO_TICKS( TIME_TO_REACH_A_CHOP_STICK ) );\
xSemaphoreTake((chopstick), portMAX_DELAY)

#define GIVE_CHOPSTICK(chopstick) \
vTaskDelay( pdMS_TO_TICKS( TIME_TO_REACH_A_CHOP_STICK ) );\
xSemaphoreGive((chopstick))

#define GET_LEFT_CHOPSTICK(philosopher)  GET_CHOPSTICK(philosopher->leftChopStickPak->chopStick)
#define GET_RIGHT_CHOPSTICK(philosopher) GET_CHOPSTICK(philosopher->rightChopStickPak->chopStick)

#define GIVE_LEFT_CHOPSTICK(philosopher)  GIVE_CHOPSTICK(philosopher->leftChopStickPak->chopStick)
#define GIVE_RIGHT_CHOPSTICK(philosopher) GIVE_CHOPSTICK(philosopher->rightChopStickPak->chopStick)

#define EAT() vTaskDelay( pdMS_TO_TICKS( TIME_TO_EAT ) )

typedef struct {
    uint8_t id;
    uint8_t prio;
    SemaphoreHandle_t chopStick;
} chopStickPak_t; // chopstick package

typedef struct {
    char name[15];
    uint8_t id;
    uint8_t eatPrio;
    chopStickPak_t *leftChopStickPak;
    chopStickPak_t *rightChopStickPak;
} philosopher_t;

typedef struct {
    chopStickPak_t chopStickPaks[NUM_OF_CHOP_STICKS];
} table_t;

typedef struct {
    philosopher_t philosophers[NUM_OF_PHILOSOPHERS];
    table_t table;
} diningHall_t;

// description of dining hall
diningHall_t diningHall = {
    .table.chopStickPaks[CHOP_STICK_1_ID] = {
        .id = CHOP_STICK_1_ID,
        .prio = CHOP_STICK_1_PRIO
    },
    .table.chopStickPaks[CHOP_STICK_2_ID] = {
        .id = CHOP_STICK_2_ID,
        .prio = CHOP_STICK_2_PRIO
    },
    .table.chopStickPaks[CHOP_STICK_3_ID] = {
        .id = CHOP_STICK_3_ID,
        .prio = CHOP_STICK_3_PRIO
    },
    .table.chopStickPaks[CHOP_STICK_4_ID] = {
        .id = CHOP_STICK_4_ID,
        .prio = CHOP_STICK_4_PRIO
    },
    .table.chopStickPaks[CHOP_STICK_5_ID] = {
        .id = CHOP_STICK_5_ID,
        .prio = CHOP_STICK_5_PRIO
    },
    .philosophers[CRUZ_ID] = {
        .name = "Cruz",
        .id = CRUZ_ID,
        .eatPrio = CRUZ_EAT_PRIO,
        .leftChopStickPak = &diningHall.table.chopStickPaks[CHOP_STICK_2_ID],
        .rightChopStickPak = &diningHall.table.chopStickPaks[CHOP_STICK_1_ID]
    },
    .philosophers[DOUGLASS_ID] = {
        .name = "Douglass",
        .id = DOUGLASS_ID,
        .eatPrio = DOUGLASS_EAT_PRIO,
        .leftChopStickPak = &diningHall.table.chopStickPaks[CHOP_STICK_3_ID],
        .rightChopStickPak = &diningHall.table.chopStickPaks[CHOP_STICK_2_ID]
    },
    .philosophers[HYPATIA_ID] = {
        .name = "Hypatia",
        .id = HYPATIA_ID,
        .eatPrio = HYPATIA_EAT_PRIO,
        .leftChopStickPak = &diningHall.table.chopStickPaks[CHOP_STICK_4_ID],
        .rightChopStickPak = &diningHall.table.chopStickPaks[CHOP_STICK_3_ID]
    },
    .philosophers[CONFUCIUS_ID] = {
        .name = "Confucius",
        .id = CONFUCIUS_ID,
        .eatPrio = CONFUCIUS_EAT_PRIO,
        .leftChopStickPak = &diningHall.table.chopStickPaks[CHOP_STICK_5_ID],
        .rightChopStickPak = &diningHall.table.chopStickPaks[CHOP_STICK_4_ID]
    },
    .philosophers[ANTISTHENES_ID] = {
        .name = "Antisthenes",
        .id = ANTISTHENES_ID,
        .eatPrio = ANTISTHENES_EAT_PRIO,
        .leftChopStickPak = &diningHall.table.chopStickPaks[CHOP_STICK_1_ID],
        .rightChopStickPak = &diningHall.table.chopStickPaks[CHOP_STICK_5_ID]
    },
};

static void invitePhilosophersToHall(philosopher_t *philosopher);
static void philosopherEat(void * pvParameters);
static void lightUpTheParty(void * pvParameters);
static void prepareDiningHall(void);

void demo_init(void) {
    prepareDiningHall();
    vTaskStartScheduler();

    for( ; ; ) {
    }
}

static void prepareDiningHall(void) {
    uint8_t i;
    // prepare table
    for(i = 0; i < NUM_OF_CHOP_STICKS; ++i) {
        diningHall.table.chopStickPaks[i].chopStick = xSemaphoreCreateMutex();
    }
    // invite philosophers and prepare them to eat
    invitePhilosophersToHall(&diningHall.philosophers[CRUZ_ID]       );
    invitePhilosophersToHall(&diningHall.philosophers[DOUGLASS_ID]   );
    invitePhilosophersToHall(&diningHall.philosophers[HYPATIA_ID]    );
    invitePhilosophersToHall(&diningHall.philosophers[CONFUCIUS_ID]  );
    invitePhilosophersToHall(&diningHall.philosophers[ANTISTHENES_ID]);

    // hall ready lets turn on part lights
    xTaskCreate(
        lightUpTheParty,            // pvTaskCode
        "party",                    // pcName
        1024,                       // uxStackDepth
        NULL,                       // pvParameters
        PARTY_LIGHT_PRIO,           // uxPriority
        NULL                        // pxCreatedTask
    );
}

static void invitePhilosophersToHall(philosopher_t *philosopher) {
    configASSERT(!(philosopher    == NULL));
    // they are checking if their chopsticks ready
    configASSERT(!(philosopher->leftChopStickPak             == NULL));
    configASSERT(!(philosopher->rightChopStickPak            == NULL));
    configASSERT(!(philosopher->leftChopStickPak->chopStick  == NULL));
    configASSERT(!(philosopher->rightChopStickPak->chopStick == NULL));
    BaseType_t ret;
    // explaining them how to eat
    ret = xTaskCreate(
        philosopherEat,
        philosopher->name,
        PHILOSOPHER_MIND,
        philosopher,
        philosopher->eatPrio,
        NULL
    );
    configASSERT(!(ret != pdTRUE));
}

static void philosopherEat(void * pvParameters) {
    configASSERT(!(pvParameters == NULL));
    philosopher_t *philosopher = (philosopher_t *)pvParameters;
    for( ; ; ) {
        demo_hw_term_printf("%s waiting\n", philosopher->name);
        GET_LEFT_CHOPSTICK(philosopher);
        demo_hw_term_printf("%s got left\n", philosopher->name);
        GET_RIGHT_CHOPSTICK(philosopher);
        demo_hw_term_printf("%s :)\n", philosopher->name);

        EAT();
        demo_hw_term_printf("%s :D\n", philosopher->name);

        GIVE_RIGHT_CHOPSTICK(philosopher);
        demo_hw_term_printf("%s gave left\n", philosopher->name);
        GIVE_LEFT_CHOPSTICK(philosopher);
        demo_hw_term_printf("%s :(\n", philosopher->name);
    }
}

static void lightUpTheParty(void * pvParameters) {
    (void)pvParameters;
    for( ;; ) {
        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
        demo_hw_led_toggle();
    }
}