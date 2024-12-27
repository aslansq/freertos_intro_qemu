thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")
source "${thisDirPath}/misc/shell/util.sh"

if [ -z "${GCC_ARM_NONE_EABI_BIN_PATH}" ]
then
    echoerr environment variable GCC_ARM_NONE_EABI_BIN_PATH is empty
    ungracefulExit
else
    echo "- found environment var GCC_ARM_NONE_EABI_BIN_PATH"
fi

out=$(${GCC_ARM_NONE_EABI_BIN_PATH}/arm-none-eabi-gcc --help 2>&1 1>/dev/null)
if [ $? != 0 ]
then
    echoerr "${out}"
    echoerr most likely GCC_ARM_NONE_EABI_BIN_PATH is not correct
    ungracefulExit
else
    echo "- found arm-none-eabi-gcc"
    echoWTab "$(${GCC_ARM_NONE_EABI_BIN_PATH}/arm-none-eabi-gcc --version)"
fi

out=$(${GCC_ARM_NONE_EABI_BIN_PATH}/arm-none-eabi-gdb --help 2>&1 1>/dev/null)
if [ $? != 0 ]
then
    echoerr "${out}"
    echoerr most likely GCC_ARM_NONE_EABI_BIN_PATH is not correct
    ungracefulExit
else
    echo "- found arm-none-eabi-gdb"
fi

out=$(make --help 2>&1 1>/dev/null)
if [ $? != 0 ]
then
    echoerr "${out}"
    echoerr most likely make is not installed
    ungracefulExit
else
    echo "- found make"
    echoWTab "$(make --version)"
fi

out=$(cmake --help 2>&1 1>/dev/null)
if [ $? != 0 ]
then
    echoerr "${out}"
    echoerr most likely cmake is not installed
    ungracefulExit
else
    echo "- found cmake"
    echoWTab "$(cmake --version)"
fi

files=$(find ${thisDirPath}/0_base/misc/FreeRTOS -type f)
if [ -z "${files}" ]
then
    echoerr FreeRTOS files not found. update submodules
    ungracefulExit
else
    echo "- found FreeRTOS files"
fi

files=$(find "${thisDirPath}/misc/shell" -type f)
for file in ${files}
do
    if [ ! -x "${file}" ]
    then
        echoerr "${file} does not have execute permission"
        ungracefulExit
    else
        echo "- found execute permission for ${file}"
    fi
done

out=$(qemu-system-arm --help 2>&1 1>/dev/null)
if [ $? != 0 ]
then
    echoerr "${out}"
    echoerr you are good to compile but can not run with qemu.
    echoerr most likely you dont have qemu installed or it is not in path.
    ungracefulExit
else
    echo "- found qemu"
    echoWTab "$(qemu-system-arm --version)"
fi

echo
echo SUCCESS!!
