#!/bin/bash
#temp=$((192/$1));
#mts=0;
for i in `seq 1 $1`;
do
    taskset -c $i ./exe  mts10p9N000000 configLyon configVaccin logConfigLyon0 &
    #mts=$(($mts+$temp));
done
wait

