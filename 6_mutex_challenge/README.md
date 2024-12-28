# 6_mutex_challenge

Implementation in [demo.c](./demo.c).

Challenge of [Introduction to RTOS Part 6 - Mutex](https://www.youtube.com/watch?v=I55auRpbiTs&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=6)

On the video he says this hack.
Well new FreeRTOS version can detect the hack and assert.
Below is their explanation:
```
 /* A task can only have an inherited priority if it holds the mutex.
  * If the mutex is held by a task then it cannot be given from an
  * interrupt, and if a mutex is given by the holding task then it must
  * be the running state task. */
```
So binary semaphore used to solve the challenge

## Terminal Output

## Notes
Use app_init function in demo.c to implement your demo application.
Run in debug console to dump the trace  
-exec dump binary value trace.bin *RecorderDataPtr