# freertos_qemu_vscode
FreeRTOS Qemu Demos in VSCode

This repo implements concepts from Digi-Key FreeRTOS introduction.

[Introduction to RTOS | Digi-Key Electronics](https://www.youtube.com/playlist?list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz)

| Youtube                                     | Link in Repo      |
|---------------------------------------------|-------------------|
|[Introduction to RTOS Part 3 - Task Scheduling](https://www.youtube.com/watch?v=95yUbClyf3E&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=3)|[3_task_scheduling](./3_task_scheduling/README.md)|

## Usecase
You dont have hardware and you dont care about any specific hardware but learning FreeRTOS.

## Prerequisites
* Install [C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) in VSCode.
* Install(download and unzip path of your choice) [arm-none-eabi-gcc](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads).
* Create environment variable GCC_ARM_NONE_EABI_BIN_PATH which points to binaries.
* Install GNU make utility.
* Install CMake utility.
* Update submodules recursively. ```git submodule update --init --recursive```
* Give execute permission files under ```misc\shell```. ```chmod +x misc\shell\*.sh```
* After all satisfied, run ```configure.sh```.```configure.sh``` checks prerequisities.

## Running with VSCode
1. Open VSCode to this folder.
2. On the VSCode left side panel, select the “Run and Debug” button.
3. Then select “Launch QEMU ```demo of your choice```” from the dropdown on the top right and press the play button.
4. This will build, run, and attach a debugger to the demo program.

## Manual Build and Run QEMU
Use the scripts under ```misc\shell```