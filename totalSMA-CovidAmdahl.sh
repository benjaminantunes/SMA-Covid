#!/bin/bash
j=1;
echo $j
#echo "##########" >> piValueSeqAmdahl.txt	
( { time ./scriptRunSMA-CovidAmdahl.sh $j ; } 2>&1 )
for i in `seq 8 8 192`;
do
	echo $i
	#echo "##########" >> piValueSeqAmdahl.txt
    ( { time ./scriptRunSMA-CovidAmdahl.sh $i ; } 2>&1 )
done

