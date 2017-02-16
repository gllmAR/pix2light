#!/bin/bash
# get the absoluth path
pushd `dirname $0` > /dev/null
SCRIPTPATH=`pwd -P`
popd > /dev/null

#echo "scriptIsHere " $SCRIPTPATH

# set systemdpath
cd $SCRIPTPATH
cd ../systemd
SYSTEMDPATH=`pwd`

#echo "systemD " $SYSTEMDPATH

# how many .service file in the folder
numServices=($SYSTEMDPATH/*.service)
numServices=${#numServices[@]}
#echo $numServices

declare -a SERVICES_ARRAY=()
SERVICES_FUNCTION=("start" "stop" "restart" "status")

EXITFLAG=0

while [ $EXITFLAG -eq 0 ]
do
	index=1
	clear 
	echo "========="

	for file in $SYSTEMDPATH/*.service
	do
   		echo $index `basename $file`
   
   		#echo $index
   		SERVICES_ARRAY[$index]=`basename $file`
   		index=$((index+1))
   		#echo ${SERVICES_ARRAY[$index]}
	done
	
	echo "?========"
	
	read x
	
	if [ $x -eq 0 ]
		then
		echo "exit with 0"
		EXITFLAG=1
		
	elif [ $x -le $numServices ]
		then
		## SELECT A FUNCTION 
		clear
		indexFunction=0
		echo "========="
		for i in "${SERVICES_FUNCTION[@]}"
		do
			tempindexFunction=$(($indexFunction + 1))
			echo $tempindexFunction ${SERVICES_FUNCTION[$indexFunction]}
			indexFunction=$(($indexFunction+1))
		done
		echo "?========"
		read y
		
		if [ $y -eq 0 ]
		then
			echo "exit"
			sleep 1
		elif [ $y -le $indexFunction ]
		then 
			echo sudo systemctl ${SERVICES_FUNCTION[$y-1]} ${SERVICES_ARRAY[$x]}
			sudo systemctl ${SERVICES_FUNCTION[$y-1]} ${SERVICES_ARRAY[$x]}
			sleep 1
		else 	
			echo "other"
			sleep 1
	fi		
		
	
		#sudo systemctl start 'basename ${SERVICES_ARRAY[$x]'}	
	else
		echo "other"	
	fi
	
done		 	