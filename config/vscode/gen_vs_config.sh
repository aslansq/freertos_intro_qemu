thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")
rootDirPath=${thisDirPath}/../../

demos="$@"
launchTemplate="${thisDirPath}/launch.template"
tasksTemplate="${thisDirPath}/tasks.template"

tasksPath="${rootDirPath}/.vscode/tasks.json"
launchPath="${rootDirPath}/.vscode/launch.json"

launchHead=$(cat <<EOF
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
EOF
)

launchTail=$(cat <<EOF
    ]
}
EOF
)

tasksHead=$(cat <<EOF
{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "tasks": [
EOF
)

tasksTail=$(cat <<EOF
    ]
}
EOF
)

addToLaunch() {
    demo="${1}"
    sed "s/0_original/${demo}/g" "${launchTemplate}" >> "${launchPath}"
    echo >> "${launchPath}"
}

addToTasks() {
    demo="${1}"
    sed "s/0_original/${demo}/g" "${tasksTemplate}" >> "${tasksPath}"
    echo >> "${tasksPath}"
}

mkdir -p .vscode
echo "${launchHead}" > "${launchPath}"
for demo in $demos
do
    addToLaunch "${demo}"
done
echo "${launchTail}" >> "${launchPath}"

echo "${tasksHead}" > "${tasksPath}"
for demo in $demos
do
    addToTasks "${demo}"
done
echo "${tasksTail}" >> "${tasksPath}"

for demo in $demos
do
    echo "added to VSCode ${demo}"
done

sed -i "s|/Applications/ARM/bin|${GCC_ARM_NONE_EABI_BIN_PATH}|g" "${launchPath}"
