#!/bin/bash
# get the absoluth path
pushd `dirname $0` > /dev/null
SCRIPTPATH=`pwd -P`
popd > /dev/null

echo "scriptIsHere " $SCRIPTPATH

cd $SCRIPTPATH
cd ../systemd

SYSTEMDPATH=`pwd`

echo "systemD " $SYSTEMDPATH
