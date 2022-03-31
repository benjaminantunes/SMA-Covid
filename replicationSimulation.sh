#!/bin/bash
j=0
for param in "$@"
do
    j=$(($j + 1))
    if [ $j -le $(($# - 2)) ]
    then
        for i in `seq 0 $((${@: -1}-1))`;
        do
            time ./exe mts10p9N00000$i  $param ${@: -2:1} log$param$i.txt&
        done
    fi
done
wait
