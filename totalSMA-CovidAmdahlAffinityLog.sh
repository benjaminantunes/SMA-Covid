#!/bin/bash
j=1;
echo $j
#echo "##########" >> piValueSeqAmdahl.txt	
( { time ./scriptRunSMA-CovidAmdahlAffinityLog.sh $j ; } 2>&1 )
for i in `seq 4 4 96`;
do
	echo $i
	#echo "##########" >> piValueSeqAmdahl.txt
    ( { time ./scriptRunSMA-CovidAmdahlAffinityLog.sh $i ; } 2>&1 )
done

