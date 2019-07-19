#!/bin/bash

# I want to execute Bozorth3 on a multitude of files. I want to determine the starting point and 
# how many files it iterates through

# Output above a certain threshold --> C:/NBIS/Main/bin/bozorth3.exe -T 40
# Output score and filename --> C:/NBIS/Main/bin/bozorth3.exe -Aoutfmt=[spg]
#C:/Users/Dr4gonborn/Desktop/FingerprintFiles/ScrambledPrints/1_1_1_1_e.xyt <-- location of scrambled print

# $1 is path to the xyt files directory $2 is the path to the .lis file $3 is the path to the score file directory $4 is the path to the bozorth3.exe

for g in "$1"*xyt
do
	filename=$(basename -- "$g")
	fname="${filename%.*}"
	addon=".txt"
	fname="$fname$addon"
	newFile=$3
	fname="$newFile$fname"
	$4 -T 40 -A outfmt=sg -p $g -G $2 >> $fname

done
