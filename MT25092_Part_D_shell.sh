#!/bin/bash

OUTCSV="MT25092_Part_D_CSV.csv"
echo "Program,Worker,Count,CPU_Percent,Disk_TPS,Time_Seconds" > $OUTCSV

run_test () {
    PROG=$1
    LABEL=$2
    WORKER=$3
    COUNT=$4

    echo "Running $LABEL + $WORKER + $COUNT"

    TIME_OUT=$(/usr/bin/time -f "%P %e" taskset -c 0 ./$PROG $WORKER $COUNT 2>&1 >/dev/null)

    CPU_PCT=$(echo $TIME_OUT | awk '{print $1}' | tr -d '%')
    TIME_SEC=$(echo $TIME_OUT | awk '{print $2}')

    IO_TPS=$(iostat -d 1 2 | awk 'NR>6 {sum+=$2; n++} END {if(n>0) printf "%.2f", sum/n; else print 0}')

    echo "$LABEL,$WORKER,$COUNT,$CPU_PCT,$IO_TPS,$TIME_SEC" >> $OUTCSV
}

# -------- Program A : processes 2 to 5 --------
for WORKER in cpu mem io; do
    for C in 2 3 4 5; do
        run_test programA A $WORKER $C
    done
done

# -------- Program B : threads 2 to 8 --------
for WORKER in cpu mem io; do
    for C in 2 3 4 5 6 7 8; do
        run_test programB B $WORKER $C
    done
done

echo "Saved to $OUTCSV"
