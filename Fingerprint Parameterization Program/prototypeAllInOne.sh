#!/bin/bash

finished=0
echo -e "Welcome to the Fingerprint Parameterization Prototype\n"
sleep 1
read -p "Before we begin, we require some information. Please enter the full path to mindtct.exe:" mindtct
read -p "Thank you. Please enter the full path to Bozorth3.exe:" bozorth3
echo -e "Thank you\n"
while ! ((finished))
do
	echo  "Input Directory Path 1: $input1"
	echo "Input Directory Path 2: $input2"
	echo "Output Path: $output"
	echo -e "Current key: $key \n"
	echo "0. Change Input Directory Path 1"
	echo "1. Change Input Directory Path 2"
	echo "2. Change Output Path"
	echo "3. Change Key"
	echo "4. Execute mindtct.exe"
	echo "5. Generate list file"
	echo "6. Scramble/Unscramble .xyt files"
	echo "7. Execute a one-to-one fingerprint match"
	echo "8. Execute a one-to-many fingerprint match"
	echo "9. Help"
	echo "10. Change mindtct.exe path"
	echo "11. Change bozorth3.exe path"
	echo "12. Exit"
	read -p "Please make a selection: " mainMenuChoice
	echo ""
	
	case $mainMenuChoice in
		0)
		read -p "Please enter Input Path 1. If directory, end with /, if it is a file, please end with the file name and extension: " input1
		;;
		1)
		read -p "Please enter Input Path 2. If directory, end with /, if it is a file, please end with the file name and extension: " input2
		;;
		2)
		read -p "Please enter Output Path. If directory, end with /, if its a file, please end with the file name and extension: " output
		;;
		3)
		read -p "Please enter the new binary key: " key
		;;
		4)
		read -p "Would you like to add an extra identifier to the end of the mindtcted files? If so, please type the extension. Else, just press Enter" addon
		./massMindtct.sh $input1 $addon $mindtct $output
		;;
		5)
		./listFileGenerator.sh $input1 $output
		;;
		6)
		read -p "Press 1 to scramble, 2 to unscramble: " mode
		./massScrambler.sh $input1 $output $key $mode
		;;
		7)
		./oneToOneFingerprintMatcher.sh $input1 $input2 $output $bozorth3
		;;
		8)
		./fingerprintMatcher.sh $input1 $input2 $output $bozorth3
		;;
		9)
		echo -e "Here is what each command does:\nChange Input Directory Path 1: Changes directory path for the used scripts. Please make sure to end with /\n"
		echo -e "Change Input Directory Path 2: Same as above, but only needed for the matching commands\n"
		echo -e "Change Output Path: Required for all operations that have output. Changes the output path\n"
		echo -e "Change Key: Changes the key that will be used for the next Scramble/Unscramble command\n"
		echo -e "Execute mindtct.exe: Requires valid mindtct path, valid output directory path, and valid input directory path 1 that contains valid fingerprint input as per mindtct documentation. Generates the .xyt files from fingerprint images\n"
		echo -e "Generate list file: Requires valid output path to .lis file to create and valid input directory path 1 that contains .xyt files. Generates list file used for one-to-many matching\n"
		echo -e "Scramble/Unscramble .xyt files: Requires valid input directory path 1 that contains .xyt files, valid output directory path, and key. Will scramble or unscrambled the .xyt files based on the key given \n"
		echo -e "Execute a one-to-one fingerprint match: Requires both input paths to be directories containing xyt files, and requires valid output diretory. Will compare fingerprints of the same name against each other, used to validate that fingerprint.\n"
		echo -e "Execute a one-to-many fingerprint match: Requires input path 1 to be a directory containing xyt files, input path 2 being a path to a valid .lis file, and a valid output directory. Will compare each fingerprint in input directory against all the ones listed in the .lis file, generates score text files in output directory showing all matching prints. Empty files mean no match was found.\n"
		echo -e "Change mindtct.exe path: Change the path to mindtct.exe\n"
		echo -e "Change bozorth3.exe path: Change the path to bozorth3.exe\n"
		;;
		10)
		read -p "Please enter the new mindtct.exe path: " mindtct
		;;
		11)
		read -p "Please enter the new bozorth3.exe path: " bozorth3
		;;
		12)
		echo -e  "Exiting program"
		break
		;;
		*)
		echo -e "Choice not valid. Please enter a number 0-12"
		;;
		
	esac
	echo ""
done