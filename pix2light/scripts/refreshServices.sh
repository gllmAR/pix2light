#!/bin/bash
# refresh services

#!/bin/bash
echo ">>>> STARTING" $0 "on" $HOSTNAME ">>>>"
echo "Script : git pull";
cd /home/artificiel/src/of/apps/pix2light && git pull ;
echo "Script : ln services et timer vers /etc/systemd/system";
sudo ln -s /home/artificiel/src/of/apps/pix2light/pix2light/systemd/*  /etc/systemd/system/ ;
echo "Script :daemon-reload";
sudo systemctl daemon-reload ;
echo "<<<<< FINISH" $0 "on" $HOSTNAME "<<<<" 
