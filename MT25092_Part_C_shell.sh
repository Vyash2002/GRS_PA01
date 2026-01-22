#!/bin/bash

OUTCSV="MT25092_Part_C_CSV.csv"
echo "Program,Worker,CPU_Percent,Disk_TPS,Time_Seconds" > $OUTCSV

run_test () {
    PROG=$1
    LABEL=$2
    WORKER=$3
    COUNT=$4

    echo "Running $LABEL + $WORKER"

    # Run and collect CPU% and Time from /usr/bin/time
    TIME_OUT=$(/usr/bin/time -f "%P %e" taskset -c 0 ./$PROG $WORKER $COUNT 2>&1 >/dev/null)

    CPU_PCT=$(echo $TIME_OUT | awk '{print $1}' | tr -d '%')
    TIME_SEC=$(echo $TIME_OUT | awk '{print $2}')

    # Disk IO stats
    IO_TPS=$(iostat -d 1 2 | awk 'NR>6 {sum+=$2; n++} END {if(n>0) printf "%.2f", sum/n; else print 0}')

    echo "$LABEL,$WORKER,$CPU_PCT,$IO_TPS,$TIME_SEC" >> $OUTCSV
}

# ---- PART C RUNS ----

run_test programA A cpu 2
run_test programA A mem 2
run_test programA A io  2

run_test programB B cpu 2
run_test programB B mem 2
run_test programB B io  2

echo "Saved to $OUTCSV"


