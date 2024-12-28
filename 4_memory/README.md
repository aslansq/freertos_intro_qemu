# 4_memory

Implementation in [demo.c](./demo.c).

[Introduction to RTOS Part 4 - Memory Management ](https://www.youtube.com/watch?v=Qske3yZRW5I&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=4)

This file demonstrates memory management in FreeRTOS
Explanation of demos:
```
// demo 1 : overflow stack by recursive call
#define APP_DEMO_1 1
// demo 2 : allocating huge array in stack to ovf
#define APP_DEMO_2 2
// demo 3 : ovf heap u32 at a time
#define APP_DEMO_3 3
// demo 4 : ovf heap in single shot
#define APP_DEMO_4 4
// demo 5 : properly malloc and free. this should be fine
#define APP_DEMO_5 5
// demo 6 : overflow of static stack by recursive call
#define APP_DEMO_6 6

#ifndef APP_DEMO
    #define APP_DEMO APP_DEMO_1
#endif
```

## Terminal Output
Terminal output of APP_DEMO_1:
```
rem: 0 tec: 574
rem: 0 tec: 575
re

Stack overflow in A
```

## Notes
Use demo_init function in demo.c to implement your demo application.
Run in debug console to dump the trace  
-exec dump binary value trace.bin *RecorderDataPtr