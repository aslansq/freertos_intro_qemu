# 9_hw_int
 
<mark>demo_tm.c</mark>  
```
../shell/rebuild_run_qemu.sh . -DDEMO_TM_C:BOOL=ON
```
<mark>demo_adc.c</mark>  
```
../shell/rebuild_run_qemu.sh . -DDEMO_ADC_C:BOOL=ON
```
<mark>demo_notify.c</mark>  
```
../shell/rebuild_run_qemu.sh . -DDEMO_NOTIFY_C:BOOL=ON
```
  
[Introduction to RTOS Part 9 - Hardware Interrupts](https://www.youtube.com/watch?v=qsflCf6ahXU&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=9)  
  
As he explains while loop is running, interrupt occurs then OS switches to printValue.  
Purpose isr should be as short as possible. You let other task to handle information. This called deferred interrupt.  
![adcTrace](./doc/adcTrace.png "adcTrace")

## Terminal Output

## Notes
Use demo_init function in demo.c to implement your demo application.
Run in debug console to dump the trace  
-exec dump binary value trace.bin *RecorderDataPtr