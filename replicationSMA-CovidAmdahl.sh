#!/bin/bash
for i in `seq 1 $1`;
do
	echo '##########' >> resSMA-CovidAmdahl.txt
    ./totalSMA-CovidAmdahl.sh >> resSMA-CovidAmdahl.txt
done

