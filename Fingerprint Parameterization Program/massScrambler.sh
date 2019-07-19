#!/bin/bash

#Now using command line input. $1 is input file/directory, $2 is the directory to put the new version in, $3 is the key and $4 is the mode

for f in "$1"*xyt
do
	filename=$(basename -- "$f")
	fname="${filename%.*}"
	addon=".xyt"
	fname="$fname$addon"
	newFile=$2
	fname="$newFile$fname"
	xyt_Editor.exe $f $fname $3 $4
done