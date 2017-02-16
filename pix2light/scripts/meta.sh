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

EXITSERVICES=0
while [ $EXITSERVICES -le 0 ]
do
	INDEXSERVICE=1
	clear 
	echo "========="

	for file in $SYSTEMDPATH/*.service
	do
   		echo $INDEXSERVICE `basename $file`
   
   		#echo $index
   		SERVICES_ARRAY[$INDEXSERVICE]=`basename $file`
   		INDEXSERVICE=$((INDEXSERVICE+1))
   		#echo ${SERVICES_ARRAY[$index]}
	done
	
	echo "?========"
	
	read INPUTSERVICE
	
	if [ $INPUTSERVICE -eq 0 ]
		then
		EXITSERVICES=1
		
	elif [ $INPUTSERVICE -le $numServices ]
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
		read INPUTFUNCTION
		
		if [ $INPUTFUNCTION -eq 0 ]
		then
			echo "<-"
			sleep 1
		elif [ $INPUTFUNCTION -le $indexFunction ]
		then 
			echo sudo systemctl ${SERVICES_FUNCTION[$INPUTFUNCTION-1]} ${SERVICES_ARRAY[$INPUTSERVICE]}
			sudo systemctl ${SERVICES_FUNCTION[$INPUTFUNCTION-1]} ${SERVICES_ARRAY[$INPUTSERVICE]}
			sleep 1
		else 	
			echo "!?"
			sleep 1
	fi		
		
	
		#sudo systemctl start 'basename ${SERVICES_ARRAY[$x]'}	
	else
		echo "other"	
	fi
	
done		 	