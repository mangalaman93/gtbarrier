#!/bin/bash
#PBS -q cs6210
#PBS -l nodes=1:sixcore
#PBS -l walltime=00:10:00
#PBS -N central
FILE=central_500_2.txt
./gtbarrier/bin/centralized 500 2 >> $FILE
