#!/bin/bash
# refresh services
echo ">>>> STARTING" $0 "on" $HOSTNAME ">>>>"
sudo systemctl disable pix2light
sudo systemctl stop pix2light
sudo systemctl disable pix2light_shuffle.timer
sudo systemctl stop pix2light_shuffle.timer
sudo systemctl disable pix2light_nextImage.timer
sudo systemctl stop pix2light_nextImage.timer
sudo systemctl disable pix2light_screenShot.timer
sudo systemctl stop pix2light_screenShot.timer
sudo systemctl disable pix2light_fadeOut.timer
sudo systemctl stop pix2light_fadeOut.timer
sudo systemctl disable pix2light_fadeIn.timer
sudo systemctl stop pix2light_fadeIn.timer
echo "<<<<< FINISH" $0 "on" $HOSTNAME "<<<<"
