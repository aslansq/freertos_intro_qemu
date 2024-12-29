# 4_memory

Implementation in [demo.c](./demo.c).

[Introduction to RTOS Part 4 - Memory Management ](https://www.youtube.com/watch?v=Qske3yZRW5I&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=4)

This file demonstrates memory management in FreeRTOS
Explanation of demos:
```
DEMO_1_C
overflow stack by recursive call
```
```
DEMO_2_C
allocating huge array in stack to ovf
```
```
DEMO_3_C
ovf heap u32 at a time
```
```
DEMO_4_C
ovf heap in single shot
```
```
DEMO_5_C
properly malloc and free. this should be fine
```
```
DEMO_6_C
overflow of static stack by recursive call
```
```
default
DEMO_1_C
```

## Terminal Output
Terminal output of DEMO_1_C:
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