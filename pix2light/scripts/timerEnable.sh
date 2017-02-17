#!/bin/bash
# refresh services
echo ">>>> STARTING" $0 "on" $HOSTNAME ">>>>" 
sudo systemctl enable pix2light
sudo systemctl restart pix2light
sudo systemctl enable pix2light_shuffle.timer
sudo systemctl start pix2light_shuffle.timer
sudo systemctl enable pix2light_nextImage.timer
sudo systemctl start pix2light_nextImage.timer
sudo systemctl enable pix2light_screenShot.timer
sudo systemctl start pix2light_screenShot.timer
sudo systemctl enable pix2light_fadeOut.timer
sudo systemctl start pix2light_fadeOut.timer
sudo systemctl enable pix2light_fadeIn.timer
sudo systemctl start pix2light_fadeIn.timer
echo "<<<<< FINISH" $0 "on" $HOSTNAME "<<<<"   
