# pix2light

Projet entourant la conversion de pixels en intensités lumineuse.

Développé avec [openframeworks](http://openframeworks.cc)
En collaboration avec [ÆLAB](http://aelab.com/wp/?portfolio=irradier-irradiate-v2)

installer les services

sudo ln -s /home/artificiel/aur/of/apps/pix2light/services/*  /etc/systemd/system/ 


sudo systemctl daemon-reload && sudo systemctl enable dmxServer && sudo systemctl enable pix2light


todo :
[x] pourquoi faut rouler l'application en sudo sur le pi pour avoir accès au seriel..?
```
sudo gpasswd --add artificiel uucp
```
		
[] slideshow d;images
[] artnet
[] dmx serveur : command line argument de config
[] dmx serveur : windowless app.
[] asservissement / master / timeline quotidien
[] améliorer le trait dans le dessin.