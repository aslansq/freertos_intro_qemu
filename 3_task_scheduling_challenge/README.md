# 3_task_scheduling

```
../shell/rebuild_run_qemu.sh .
```

Challenge of [Introduction to RTOS Part 3 - Task Scheduling | Digi-Key Electronics](https://www.youtube.com/watch?v=95yUbClyf3E&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=3)

At highligted timestamp, I(the user) entered 100 ms request. You could see context switch of led task timestamp are now 100ms intervals.
![User selectable blink rate](./doc/userInputLedDelay.png "User selectable blink rate")

## Terminal Output
```
Enter LED delay(ms):
Led delay updated to(ms): 100
```

## Notes
Use demo_init function in demo.c to implement your demo application.
Run in debug console to dump the trace  
-exec dump binary value trace.bin *RecorderDataPtr