# 6_mutex

Two demos available. Pass one of the arguments to CMake.

<mark>demo_mutex.c</mark>
```
../shell/rebuild_run_qemu.sh . -DDEMO_MUTEX_C:BOOL=ON
```

<mark>demo_race.c</mark>
```
../shell/rebuild_run_qemu.sh . -DDEMO_RACE_C:BOOL=ON
```

<mark>default demo.c</mark>
```
../shell/rebuild_run_qemu.sh .
```

[Introduction to RTOS Part 6 - Mutex](https://www.youtube.com/watch?v=I55auRpbiTs&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=6)

## Terminal Output
```
$ ../shell/rebuild.sh . -DDEMO_MUTEX:BOOL=ON
$ ../shell/run_qemu.sh ./build/demo
char device redirected to /dev/pts/1 (label serial1)
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
12
13
14
15
```

```
$ ../shell/rebuild.sh . -DDEMO_RACE:BOOL=ON
$ ../shell/run_qemu.sh ./build/demo
char device redirected to /dev/pts/1 (label serial1)
1
1
2
2
3
3
4
5
```

## Notes
Use demo_init function in demo.c to implement your demo application.
Run in debug console to dump the trace  
-exec dump binary value trace.bin *RecorderDataPtr