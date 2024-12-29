# 5_queue
```
../shell/rebuild_run_qemu.sh .
```
[Introduction to RTOS Part 5 - Queue](https://www.youtube.com/watch?v=pHJ3lxOoWeI&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=5)

## Terminal Output
When send is faster than print.
```
#define PRINT_MSG_DELAY (1000)
#define SEND_MSG_DELAY  (100)
```
Terminal output is:
```
0
1
2
3
4
5
6
7
8
9
10
11
20
29
```

## Notes
Use demo_init function in demo.c to implement your demo application.
Run in debug console to dump the trace  
-exec dump binary value trace.bin *RecorderDataPtr