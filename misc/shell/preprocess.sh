#!/bin/bash
# This script is used to preprocess a demo
# Usage: ./preprocess.sh <demo path>
demoPath="$1"

thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")
source "${thisDirPath}/util.sh"

if [ -z "${demoPath}" ]
then
    echoerr "demo path is not provided"
    ungracefulExit
fi

if [ ! -d "${demoPath}" ]
then
    echoerr "demo path does not exist"
    ungracefulExit
fi

out=$(python3 --help 2>&1 1>/dev/null)
if [ $? != 0 ]
then
    echoerr "${out}"
    echoerr most likely you dont have python3 installed
    ungracefulExit
fi

cd "${demoPath}/build"
if [ $? != 0 ]
then
    echoerr "cd ${demoPath}/build" failure
    ungracefulExit
fi

if [ ! -f Makefile ]
then
    echoerr Makefile is not found
    ungracefulExit
fi

if [ ! -f "source_files.txt" ]
then
    echoerr source_files.txt file is not found
    ungracefulExit
fi

if [ ! -f "include_files.txt" ]
then
    echoerr include_files.txt file is not found
    ungracefulExit
fi

out=$(python3 - <<EOF
import os
armGccPath = ''
try:
        armGccPath = str(os.environ['GCC_ARM_NONE_EABI_BIN_PATH'])
except Exception as e:
        raise Exception("GCC_ARM_NONE_EABI_BIN_PATH environment variable is not found")
sourceFiles = []
includeFiles = []
with open("source_files.txt", "r") as f:
    lines = f.readlines()
    for line in lines:
        line = line.strip()
        sourceFiles.append(line)
with open("include_files.txt", "r") as f:
    lines = f.readlines()
    for line in lines:
        line = line.strip()
        includeFiles.append(line)
with open("preprocess.sh", "w") as f:
    f.write("#!/bin/bash\n")
    f.write("echo -- Preprocessing\n")
    numOfSourceFiles = len(sourceFiles)
    for sourceIdx in range(numOfSourceFiles):
        sourceFile = sourceFiles[sourceIdx]
        s = armGccPath + "/arm-none-eabi-gcc "
        for includeFile in includeFiles:
            s = s + "-I" + includeFile + " "
        prjDir=str(os.path.abspath(".."))
        outFile = sourceFile.replace(prjDir, prjDir + "/build/preprocessed")
        outFile = outFile.replace(".c", ".i")
        outDir = str(os.path.dirname(outFile))
        sourceFileName = os.path.basename(sourceFile)
        s = s + "-E " + sourceFile + " -o " + outFile + "\n"
        s = "mkdir -p " + outDir + "\n" + s
        s = "echo  \"   " + str(sourceIdx+1) + "/" + str(numOfSourceFiles) + " " + sourceFileName + "\"\n" + s
        f.write(s)
EOF
)

if [ $? != 0 ]
then
    echoerr "${out}"
    echoerr failed to generate preprocess.sh
    ungracefulExit
fi

chmod +x preprocess.sh
./preprocess.sh "$demoPath"