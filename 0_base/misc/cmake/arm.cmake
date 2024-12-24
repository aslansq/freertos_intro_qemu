set(CMAKE_AR           $ENV{GCC_ARM_NONE_EABI_BIN_PATH}/arm-none-eabi-ar${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_ASM_COMPILER $ENV{GCC_ARM_NONE_EABI_BIN_PATH}/arm-none-eabi-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_C_COMPILER   $ENV{GCC_ARM_NONE_EABI_BIN_PATH}/arm-none-eabi-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_LINKER       $ENV{GCC_ARM_NONE_EABI_BIN_PATH}/arm-none-eabi-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_OBJCOPY      $ENV{GCC_ARM_NONE_EABI_BIN_PATH}/arm-none-eabi-objcopy${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_RANLIB       $ENV{GCC_ARM_NONE_EABI_BIN_PATH}/arm-none-eabi-ranlib${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_SIZE         $ENV{GCC_ARM_NONE_EABI_BIN_PATH}/arm-none-eabi-size${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_STRIP        $ENV{GCC_ARM_NONE_EABI_BIN_PATH}/arm-none-eabi-strip${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")

set(CMAKE_C_FLAGS  "-ffreestanding \
                    -mthumb \
                    -mcpu=cortex-m3 \
                    -Wall -Wextra -Wshadow \
                    -ggdb \
                    -Og \
                    -ffunction-sections \
                    -fdata-sections" CACHE INTERNAL "")

set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/0_base/misc/mps2_m3.ld \
                            -Xlinker -Map=${prj}.map \
                            -Xlinker --gc-sections \
                            -nostartfiles \
                            -specs=nano.specs -specs=nosys.specs")
