# 11_priority_inversion (unbounded)
```
../shell/rebuild_run_qemu.sh .
```  
[Introduction to RTOS Part 11 - Priority Inversion](https://www.youtube.com/watch?v=C2xKhxROmhA&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=11)  
  

## Terminal Output
<mark>(H) lock acquired. Wait time: 5099</mark>
```
(L) trying to acquire lock.

(H) trying to acquire lock.

(L) lock acquired. Wait time: 0
(M) worky work.

(M) sleppy.

(L) lock released.

(H) lock acquired. Wait time: 5099
(H) lock released.

(H) sleepy.

(M) worky work.

(H) trying to acquire lock.

(H) lock acquired. Wait time: 0
(H) lock released.

(H) sleepy.
```
## Notes
Use demo_init function in demo.c to implement your demo application.
Run in debug console to dump the trace  
-exec dump binary value trace.bin *RecorderDataPtr