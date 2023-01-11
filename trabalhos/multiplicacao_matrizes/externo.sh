#!/bin/bash

echo "2048 2048 2048" > 2048

# Compilando!
gcc -Wall externo.c -o externo -O3 -fopenmp 
echo "Parealelismo no loop externo"

for i in {1,2,4,8,16,32,64,128}; do 
        for j in {1..3}; do 
                echo "$i thread(s) / run $j"
                export OMP_NUM_THREADS=$i && time ./externo < 2048 > /dev/null
        done
        echo
done