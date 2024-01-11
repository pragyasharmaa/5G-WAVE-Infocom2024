#!/bin/bash

numExpts=20

base_folder="wave"
for j in $(seq 1 $numExpts)
do
    ./parse_rplogs.py $base_folder-$j
    ./parse_wavelogs.py $base_folder-$j
    ./final_parser.py $base_folder-$j
done


base_folder="nowave"
for j in $(seq 1 $numExpts)
do
    ./parse_rplogs.py $base_folder-$j
    mv "$base_folder-$j/table.csv" "$base_folder-$j/finaltable.csv" 
done




