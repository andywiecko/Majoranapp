#!/bin/bash

LANG=en_US

logs='logs/test-03'
mkdir -p $logs

L=100
delta=1
rashbax=0.0
rashbay=0.1
t_integral=1

for zeeman in $(seq 0.00 0.1 8.00); do
    for mu in $(seq 0.00 0.1 8.00); do

        lambda="./main.exe \
            -L $L\
            -d $delta\
            -m $mu\
            -z $zeeman\
            -t $t_integral\
            -r $rashbay\
             | head -n 6 | tail -n 5"

        filename=$logs/L${L}d${delta}rx${rashbay}ry${rashbay}t${t_integral}
        echo "echo $mu $zeeman \`$lambda\` >> $filename"

    done
done
