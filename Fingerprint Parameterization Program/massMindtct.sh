#!/bin/bash

#FILES = C:/Users/starr/Desktop/FingerPrints_Delhi_MOFL/DB1_Lumidgm/*
#STRING = "C:/Users/starr/Desktop/FingerPrints_Delhi_MOFL/DB2_Secugen/"
#echo "$STRING" | sed "s/.*\///"
#$1 is the path to directories with the fingerprints to mindtct, $2 is any extension you want to add to the file $3 is path to mindtct $4 is the output file directory
cd $4
for f in $1
do
	filename=$(basename -- "$f")
	fname="${filename%.*}"
	addon="$2"
	fname="$fname$addon"
	$3 $f $fname
done