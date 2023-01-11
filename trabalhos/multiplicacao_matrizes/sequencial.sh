#!/bin/bash

echo "2048 2048 2048" > 2048

# Compilando!
gcc -Wall sequencial.c -o sequencial -O3 -fopenmp 
echo "Sequencial"

for i in {1}; do 
        for j in {1..3}; do 
                echo "$i thread(s) / run $j"
                time ./sequencial < 2048 > /dev/null
        done
        echo
done