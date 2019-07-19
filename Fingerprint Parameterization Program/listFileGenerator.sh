#!/bin/bash

#$2 is output lis file path $1 is where the xyt files are 

fname=$2
> $fname
for f in "$1"*xyt
do
	echo $f >> $fname
done