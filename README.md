![all_builds](https://github.com/aslansq/freertos_intro_qemu/actions/workflows/c-cpp.yml/badge.svg)
# freertos_intro_qemu
FreeRTOS Introduction with Qemu in VSCode

This repo implements concepts from Digi-Key FreeRTOS introduction.

[Introduction to RTOS | Digi-Key Electronics](https://www.youtube.com/playlist?list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz)

| Youtube                                     | Demo              | Challenge Solution |
|---------------------------------------------|-------------------|--------------------|
|[Introduction to RTOS Part 3 - Task Scheduling](https://www.youtube.com/watch?v=95yUbClyf3E&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=3)|[3_task_scheduling](./3_task_scheduling/README.md)|[3_task_scheduling_challenge](./3_task_scheduling_challenge/README.md)|
|[Introduction to RTOS Part 4 - Memory Management ](https://www.youtube.com/watch?v=Qske3yZRW5I&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=4)|[4_memory](./4_memory/README.md)|[4_memory_challenge](./4_memory_challenge/README.md)|
|[Introduction to RTOS Part 5 - Queue](https://www.youtube.com/watch?v=pHJ3lxOoWeI&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=5)|[5_queue](./5_queue/README.md)|[5_queue_challenge](./5_queue_challenge/README.md)|
|[Introduction to RTOS Part 6 - Mutex](https://www.youtube.com/watch?v=I55auRpbiTs&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=6)|[6_mutex](./6_mutex/README.md)|[6_mutex_challenge](./6_mutex_challenge/README.md)|
|[Introduction to RTOS Part 7 - Semaphore](https://www.youtube.com/watch?v=5JcMtbA9QEE&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=7)|[7_semaphore](./7_semaphore/README.md)|[7_semaphore_challenge](./7_semaphore_challenge/README.md)|
|[Introduction to RTOS Part 8 - Software Timer](https://www.youtube.com/watch?v=b1f1Iex0Tso&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=8)|[8_sw_timers](./8_sw_timers/README.md)|[8_sw_timers_challenge](./8_sw_timers_challenge/README.md)|
|[Introduction to RTOS Part 9 - Hardware Interrupts](https://www.youtube.com/watch?v=qsflCf6ahXU&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=9)|[9_hw_int](./9_hw_int/README.md)|[9_hw_int_challenge](./9_hw_int_challenge/README.md)|
|[Introduction to RTOS Part 10 - Deadlock and Starvation](https://www.youtube.com/watch?v=hRsWi4HIENc&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=10)|[10_deadlock_starvation](./10_deadlock_starvation/README.md)|[10_deadlock_starvation_challenge](./10_deadlock_starvation_challenge/README.md)|
|[Introduction to RTOS Part 11 - Priority Inversion](https://www.youtube.com/watch?v=C2xKhxROmhA&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=11)|[11_priority_inversion](./11_priority_inversion/README.md)|[11_priority_inversion_challenge](./11_priority_inversion_challenge/README.md)|
## Usecase
You dont have hardware and you dont care about any specific hardware but learning FreeRTOS.

## Prerequisites
* Install [C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) in VSCode.
* Install(download and unzip path of your choice) [arm-none-eabi-gcc](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads).
* Create environment variable GCC_ARM_NONE_EABI_BIN_PATH which points to binaries.
* Install GNU make utility.
* Install CMake utility.
* Update submodules recursively. ```git submodule update --init --recursive```
* Give execute permission files under shell. ```chmod +x shell/*.sh```
* After all satisfied, run configure.sh. configure.sh checks prerequisities.

## Running with VSCode
1. Open VSCode to this folder.
2. On the VSCode left side panel, select the “Run and Debug” button.
3. Then select “Launch QEMU <mark>demo of your choice</mark>” from the dropdown on the top right and press the play button.
4. This will build, run, and attach a debugger to the demo program.

## Manual Build and Run QEMU
Use the scripts under <mark>shell</mark>. Examples:
```
./shell/rebuild_run_qemu.sh 9_hw_int_challenge/
```
```
./shell/rebuild.sh 9_hw_int_challenge/
```  
```
./shell/rebuild_all.sh
```

## Tip
If you make environment variable FREERTOS_INTRO_QEMU_TERM, it will try to launch and connect serial hardware display. Tested with gnome-terminal. In case something fails see the err.txt under build folder.
Example  
```export FREERTOS_INTRO_QEMU_TERM=gnome-terminal```

## Versions

Exact versions are not mandatory. Given as example.

| Tool              | Version      |
|-------------------|--------------|
| qemu-system-arm   | 6.2.0        |
| arm-none-eabi-gcc | 10.3-2021.10 |
| make              | 4.3          |
| cmake             | 3.25.1       |
| Tracealyzer       | 4.10.2       |
