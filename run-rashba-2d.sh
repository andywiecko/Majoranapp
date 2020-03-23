#!/bin/bash

LANG=en_US

logs='logs/test-08'
mkdir -p $logs

L=100
H=1
delta=1
rashbax=0
rashbay=0.05
t_integral=1
zeeman=0
spinflip=0

for zeeman in $(seq 0.00 0.01 4.00); do
    for mu in $(seq 0.00 0.01 4.00); do

        lambda="./main.exe \
            -L $L\
            -H $H\
            -d $delta\
            -m $mu\
            -z $zeeman\
            -s $spinflip\
            -t $t_integral\
            -r $rashbay\
             | head -n 10 | tail -n 5"

        filename=$logs/L${L}H${H}d${delta}rx${rashbax}ry${rashbay}t${t_integral}
        echo "echo $mu $zeeman \`$lambda\` >> $filename"

    done
done
