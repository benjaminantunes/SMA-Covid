#!/bin/bash
for i in `seq 0 9`;
do
        ./exe mts10p9N00000$i configParisLightVaccin.txt log$i.txt
done
