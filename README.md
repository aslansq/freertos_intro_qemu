# freertos_qemu_vscode
FreeRTOS Qemu Demos in VSCode

## Prerequisites
* Install [C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) in VSCode.
* Install(download and unzip path of your choice) [arm-none-eabi-gcc](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads).
* Create environment variable GCC_ARM_NONE_EABI_BIN_PATH which points to binaries.
* Install GNU make utility.
* Install CMake utility.

## Building and Running
1. Update submodules recursively. ```git submodule update --init --recursive```
2. Open VSCode to this folder.
3. After prerequisites satisfied, run ```configure.sh```.```configure.sh``` checks prerequisities.
4. On the VSCode left side panel, select the “Run and Debug” button. Then select “Launch QEMU ```demo of your choice```” from the dropdown on the top right and press the play button. This will build, run, and attach a debugger to the demo program.
