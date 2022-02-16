#!/bin/bash
for i in `seq 0 $(($1-1))`;
do
       time ./exe mts10p9N00000$i configParisFullNoVaccin.txt log$i.txt&
done
wait
