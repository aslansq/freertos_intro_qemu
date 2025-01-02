# 11_priority_inversion
```
../shell/rebuild_run_qemu.sh .
```  
Challenge of [Introduction to RTOS Part 11 - Priority Inversion](https://www.youtube.com/watch?v=C2xKhxROmhA&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=11)  
  
Hmm I could not understand what is exactly we need to do. When we enter critical section, systick interrupt also gets disabled. It makes core stuck at while loop since xTickCount is not increasing.


## Terminal Output

```
(L) trying to acquire lock.

(L) lock acquired. Wait time: 0
```

## Notes
Use demo_init function in demo.c to implement your demo application.
Run in debug console to dump the trace  
-exec dump binary value trace.bin *RecorderDataPtr