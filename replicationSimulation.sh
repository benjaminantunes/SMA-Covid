#!/bin/bash
# ./replicationSimulation nbRepli configVaccin config1 config2 config3 ....
compteur=0
for j in  `seq 0 $(($1 -1))`;
do

    for ((i=3; i<=$#; i++));
    do
        echo mts000M00$(printf "%04d" $compteur)  $j $2 ${!i}
        time ./exe mts000M00$(printf "%04d" $compteur)  $j $2 ${!i}&
        compteur=$(($compteur+1))
    done
    
done
wait
