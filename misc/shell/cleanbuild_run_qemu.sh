prjPath="$1"

ungracefulExit()
{
    echoerr
    echoerr ERROR!!
    exit 1
}

cd "${prjPath}"

if [ $? != 0 ]; then
    echoerr "cd ${prjPath} failure"
    ungracefulExit
fi

rm -rf build
mkdir -p build
cd build
cmake ..
make -j all
if [ $? != 0 ]; then
    echoerr "compilation failure"
    ungracefulExit
fi
echo 'QEMU_started'
qemu-system-arm -machine mps2-an385 -cpu cortex-m3 -kernel ${prjPath}/build/demo -monitor none -nographic -serial stdio -s -S