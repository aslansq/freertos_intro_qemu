# 4_memory

[Introduction to RTOS Part 4 - Memory Management ](https://www.youtube.com/watch?v=Qske3yZRW5I&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=4)

This file demonstrates memory management in FreeRTOS
Explanation of demos:

<mark>DEMO_1_C overflow stack by recursive call</mark>
```
../shell/rebuild_run_qemu.sh . -DDEMO_1_C:BOOL=ON
```

<mark>DEMO_2_C allocating huge array in stack to ovf</mark>
```
../shell/rebuild_run_qemu.sh . -DDEMO_2_C:BOOL=ON
```

<mark>DEMO_3_C ovf heap u32 at a time</mark>
```
../shell/rebuild_run_qemu.sh . -DDEMO_3_C:BOOL=ON
```

<mark>DEMO_4_C ovf heap in single shot</mark>
```
../shell/rebuild_run_qemu.sh . -DDEMO_4_C:BOOL=ON
```

<mark>DEMO_5_C properly malloc and free. this should be fine</mark>
```
../shell/rebuild_run_qemu.sh . -DDEMO_5_C:BOOL=ON
```

<mark>DEMO_6_C overflow of static stack by recursive call</mark>
```
../shell/rebuild_run_qemu.sh . -DDEMO_6_C:BOOL=ON
```

<mark> default DEMO_1_C
```
../shell/rebuild_run_qemu.sh .
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