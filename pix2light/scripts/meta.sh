#!/bin/bash
# get the absoluth path
pushd `dirname $0` > /dev/null
SCRIPTPATH=`pwd -P`
popd > /dev/null

#echo "scriptIsHere " $SCRIPTPATH

# set systemdpath
cd $SCRIPTPATH


#echo "systemD " $SYSTEMDPATH

# how many .service file in the folder
numScripts=($SCRIPTPATH/*.*)
numScripts=${#numScripts[@]}
#echo $numServices

#declare -a SERVICES_ARRAY=()
#SERVICES_FUNCTION=("start" "stop" "restart" "status")

EXITSCRIPTS=0
while [ $EXITSCRIPTS -le 0 ]
cd $SCRIPTPATH
do
	INDEXSCRIPTS=1
	clear 
	echo `basename $0`
	echo $USER"@"$HOSTNAME
	echo "=========" 

	for file in $SCRIPTPATH/*.*
	do
   		echo $INDEXSCRIPTS `basename $file`
   
   		#echo $index
   		SCRIPTS_ARRAY[$INDEXSCRIPTS]=`basename $file`
   		INDEXSCRIPTS=$((INDEXSCRIPTS+1))
   		#echo ${SERVICES_ARRAY[$index]}
	done
	
	echo "?=====<<0"
	
	read INPUTSCRIPTS
	
	if [ $INPUTSCRIPTS -eq 0 ]
		then
		EXITSCRIPTS=1
		sleep .2
		
	elif [ $INPUTSCRIPTS -le $numScripts ]
		then
		clear	
		echo  ${SCRIPTS_ARRAY[$INPUTSCRIPTS]}
			./${SCRIPTS_ARRAY[$INPUTSCRIPTS]}
	sleep 1		
	
		#sudo systemctl start 'basename ${SERVICES_ARRAY[$x]'}	
	else
		echo "other"	
	fi
	
done		 	