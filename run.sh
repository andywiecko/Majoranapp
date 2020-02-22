
#!/bin/bash

LANG=en_US

logs='logs/test-01'
mkdir -p $logs


for delta in 0.8 
do
   for mu in `seq 0.0 0.01 4.00`
   do
      for L in `seq 10 10 100` `seq 200 100 1000`
      do
         ./main.exe -d $delta -m $mu -t 1.0 -L $L -v > $logs/L${L}D${delta}M${mu}
      done
   done
done
