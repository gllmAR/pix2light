#!/bin/bash
# get the absoluth path
pushd `dirname $0` > /dev/null
SCRIPTPATH=`pwd -P`
popd > /dev/null



# set systemdpath
cd $SCRIPTPATH


#echo "systemD " $SYSTEMDPATH

# how many .service file in the folder
#echo $numServices

DESTINATIONADDRESS="127.0.0.1"
DESTINATIONPORT="9999"

SCRIPT_FUNCTION=( "/lol/cat i 1" "/lol/cats f 1.2" "/lol/cat/ i 12")


EXITSCRIPT=0
while [ $EXITSCRIPT -le 0 ]
do
	INDEXSERVICE=0
	clear 
	echo "========="

	for file in "${SCRIPT_FUNCTION[@]}"
	do
   		echo $((INDEXSERVICE + 1))" "${SCRIPT_FUNCTION[$INDEXSERVICE]}
   		INDEXSERVICE=$((INDEXSERVICE+1))
   
	done
	
	echo "?========"
	
	read USERINPUT
	
	if [ $USERINPUT -eq 0 ]
		then
		EXITSCRIPT=1
	
		
	elif [ $USERINPUT -le $((INDEXSERVICE)) ]
		then
		clear	
		echo  "sendosc" $DESTINATIONADDRESS $DESTINATIONPORT ${SCRIPT_FUNCTION[$((USERINPUT-1))]}
		echo `pwd`
		sendosc  $DESTINATIONADDRESS $DESTINATIONPORT ${SCRIPT_FUNCTION[$((USERINPUT-1))]}
		sleep 1	
	
		#sudo systemctl start 'basename ${SERVICES_ARRAY[$x]'}	
	else
		echo "other"	
	fi
	
done		 	