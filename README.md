# Projet 2A Robocop 

Vous trouverez dans ce git les différents scripts utilisés pour commander notre robot. 

Ceux concernant la carte Arduino Uno: 
 - joystick_filaire.ino : interprète les données envoyées par le joystick relié à la carte arduino pour la commande des moteurs
 

Ceux concernant l'ESP32: 
 - blynk_joystick.ino : interprète les données envoyées via Wifi par le joystick fourni par l'application pour smartphone blynk pour la commande des moteurs
 - SimpleWifiServer_test1.ino : crée un web serveur afin de contrôler les moteurs à distance, se base sur le script donné sur le site suivant https://randomnerdtutorials.com/esp32-web-server-arduino-ide/ .  
 La page http crée est très basique, nous voulions surtout tester et nous nous sommes davantage intéressés à l'application cependant elle peut tout à fait être développée dans le script. 
