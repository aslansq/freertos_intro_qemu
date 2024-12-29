logFile=$1
serialPort=""
while [ 1 == 1 ]
do
    line=$(cat $logFile | grep 'char device redirected to ')
    if [ ! -z "$line" ]
    then
        serialPort=$(echo $line | awk '{print $5}')
        echo Found $serialPort
        break
    fi
done

screen $serialPort
