#!/bin/bash
#PBS -q cs6210
#PBS -l nodes=1:fourcore
#PBS -l walltime=00:10:00
#PBS -N central2
FILE=central_500.txt
    for i in `seq 2 12`; do
       ./gtbarrier/bin/centralized 500 $i >> $FILE
    done
