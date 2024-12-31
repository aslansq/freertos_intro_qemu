# 10_deadlock_starvation_challenge (Dining Philosopher Problem Arbitrator Solution)
```
../shell/rebuild_run_qemu.sh .
```  
Challenge of [Introduction to RTOS Part 10 - Deadlock and Starvation](https://www.youtube.com/watch?v=hRsWi4HIENc&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=10)  
  

## Terminal Output
```
Douglass waiting
Hypatia waiting
Confucius waiting
Antisthenes waiting
Cruz waiting
Cruz got left
Cruz :)
Cruz :D
Cruz gave right
Cruz gave left
Douglass got left
Douglass :)
Cruz waiting
Douglass :D
Douglass gave right
Douglass gave left
Douglass waiting
Hypatia got left
Hypatia :)
Hypatia :D
Hypatia gave right
Hypatia gave left
Confucius got left
Confucius :)
Hypatia waiting
Confucius :D
Confucius gave right
Confucius gave left
Antisthenes got left
Antisthenes :)
Confucius waiting
Antisthenes :D
Antisthenes gave right
Antisthenes gave left
```
## Notes
Use demo_init function in demo.c to implement your demo application.
Run in debug console to dump the trace  
-exec dump binary value trace.bin *RecorderDataPtr