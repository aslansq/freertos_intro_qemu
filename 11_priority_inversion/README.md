# 11_priority_inversion (unbounded)
```
../shell/rebuild_run_qemu.sh .
```  
[Introduction to RTOS Part 11 - Priority Inversion](https://www.youtube.com/watch?v=C2xKhxROmhA&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=11)  
  

## Terminal Output

<mark>DEMO_UNBOUNDED_C</mark>  
<mark>(H) lock acquired. Wait time: 5001</mark>
```
(L) trying to acquire lock.

(L) lock acquired. Wait time: 0
(H) trying to acquire lock.

(M) worky work.

(M) sleppy.

(L) lock released.

(H) lock acquired. Wait time: 5001
(H) lock released.

(H) sleepy.
```

<mark>DEMO_INHERITANCE_C: It is still priority inversion but bounded.</mark>  
<mark>(H) lock acquired. Wait time: 241</mark>
```
(L) trying to acquire lock.

(L) lock acquired. Wait time: 1
(H) trying to acquire lock.

(L) lock released.

(H) lock acquired. Wait time: 241
(H) lock released.

(H) sleepy.

(M) worky work.
```
## Notes
Use demo_init function in demo.c to implement your demo application.
Run in debug console to dump the trace  
-exec dump binary value trace.bin *RecorderDataPtr