# pix2light

Projet entourant la conversion de pixels extrait d'une image en intensités lumineuse.

Développé en C++ via [openframeworks](http://openframeworks.cc)
En collaboration avec [ÆLAB](http://aelab.com/wp/?portfolio=irradier-irradiate-v2)



## Pré-requis : 
Installer Openframeworks et s'assurer qu'un exemple compile adéquatement.
sur macOs, suivre ce tutoriel : http://openframeworks.cc/setup/xcode/
* au temps de l'écriture, la dernière version stable était 0.9.4.
Sur RaspberryPi, suivre ce tutoriel : http://openframeworks.cc/setup/raspberrypi/raspberry-pi-getting-started-archlinux/ 
* je favorise  l'usage d'archlinux de manière à limiter le nombre de logiciel inutile installé d'avance.  	
 
 
## Add-on
Dans le dossier addon de OF ajouter ces dépendences 

* https://github.com/kylemcdonald/ofxDmx


## Composantes : 

Le projet est conçu de manière décentralisé  de sorte à ce que chaque logiciel ce concentre sur une fonction spécifique.

### dmxServer 
dmxServer est une application (headless) qui transforme une liste de données vers une interface USB DMX. 

* Compatible avec la Enttec pro dmx
* Compatible avec linux et macOs
* La liste doit être constitué de chiffre pouvant comporter jusqu'à 512 élements 
* la valeurs des élements dans la liste doit être entre 0 et 255 

requiert le addon : https://github.com/kylemcdonald/ofxDmx
		  
### pix2osc
pix2osc est une application graphique qui échantillone une ou des sous-section d'images afin d'envoyer une liste d'intensité.

### manitou
Application servant à controller le comportement temporelle  



## Déploiement 





créer un utilisateur sur le 


installer les services lié au déploiment 
```
sudo ln -s /home/artificiel/aur/of/apps/pix2light/services/*  /etc/systemd/system/ 
```
activer les services 
```
sudo systemctl daemon-reload && sudo systemctl enable dmxServer && sudo systemctl enable pix2light
```



## todo :
[x] pourquoi faut rouler l'application en sudo sur le pi pour avoir accès au seriel..?
```
sudo gpasswd --add artificiel uucp
```
[] orbit : http://www.physics.csbsju.edu/orbit/orbit.2d.html		
[X] slideshow d;images
[] artnet
?[] dmx serveur : command line argument de config
?[] dmx serveur : windowless app.
[] asservissement / master / timeline quotidien
[] améliorer le trait dans le dessin.
[] bug : long terme sur osx Memory Leak? 