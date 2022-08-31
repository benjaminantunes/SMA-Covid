#!/bin/bash
for i in `seq 1 $1`;
do
	echo '##########' >> resSMA-CovidAmdahlAffinityLog.txt
    ./totalSMA-CovidAmdahlAffinityLog.sh >> resSMA-CovidAmdahlAffinityLog.txt
done

