# freertos_qemu_vscode
FreeRTOS Qemu Demos in VSCode

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