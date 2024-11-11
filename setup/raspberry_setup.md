# Configuration du Raspberry Pi pour le Projet Minecraft avec Gant Connecté

Ce guide vous expliquera comment installer et configurer le Raspberry Pi pour le projet, y compris l’installation de Mosquitto pour la communication MQTT.

---

## 1. Préparation de la Carte SD

1. **Téléchargez l'image du système d'exploitation** :
   - Utilisez le fichier suivant : `2023-12-23-raspios-bullseye-ARM64.img.xz`.
   - Vous pouvez le télécharger à partir du [site officiel de Raspberry Pi](https://www.raspberrypi.com/software/operating-systems/).

2. **Gravez l’image sur la carte SD** :
   - Téléchargez et installez **Raspberry Pi Imager** ([disponible ici](https://www.raspberrypi.com/software/)).
   - Insérez la carte SD dans votre ordinateur et ouvrez Raspberry Pi Imager.
   - Sélectionnez l’image `2023-12-23-raspios-bullseye-ARM64.img.xz`.
   - Choisissez votre carte SD et cliquez sur **Écrire**.

3. **Insérez la carte SD dans le Raspberry Pi** :
   - Connectez le Raspberry Pi à un écran, un clavier et une souris.
   - Alimentez-le pour démarrer le système d’exploitation.

---

## 2. Configuration Initiale du Raspberry Pi

1. **Connexion Wi-Fi et Mise à Jour** :
   - Connectez votre Raspberry Pi au réseau Wi-Fi de la borne Linksys (SSID : `binome_CSFA`, mot de passe : `tpRT9025`).
   - Ouvrez un terminal et mettez à jour le Raspberry Pi :
     ```bash
     sudo apt update && sudo apt upgrade -y
     ```

2. **Vérifiez l’adresse IP** de votre Raspberry Pi :
   - Tapez `hostname -I` dans le terminal pour obtenir l'adresse IP de votre Raspberry Pi. Notez cette adresse, car elle sera nécessaire pour la configuration MQTT.

---

## 3. Installation de Mosquitto (Serveur MQTT)

Pour permettre la communication entre le Raspberry Pi et les ESP8266 via MQTT, installez Mosquitto et ses outils en ligne de commande.

1. **Installez Mosquitto et ses clients** :
   ```bash
   sudo apt-get install mosquitto mosquitto-clients
   ```

2. **Vérifiez que Mosquitto fonctionne** :
   - Pour vérifier si Mosquitto est en cours d’exécution, tapez :
     ```bash
     sudo service mosquitto status
     ```
   - Vous devriez voir quelque chose comme :
     ```
     ● mosquitto.service - LSB: mosquitto MQTT v3.1 message broker
        Loaded: loaded (/etc/init.d/mosquitto)
        Active: active (running) since [date] [time]; [time] ago
     ```

3. **Commandes de Gestion de Mosquitto** :
   - Démarrer Mosquitto :
     ```bash
     sudo service mosquitto start
     ```
   - Arrêter Mosquitto :
     ```bash
     sudo service mosquitto stop
     ```
   - Redémarrer Mosquitto :
     ```bash
     sudo service mosquitto restart
     ```

---

## 4. Configuration du Serveur Mosquitto

1. **Configurer Mosquitto pour démarrer automatiquement** :
   ```bash
   sudo systemctl enable mosquitto
   ```

2. **Configuration de la Sécurité MQTT** (optionnel) :
   - Par défaut, Mosquitto permet des connexions sans authentification. Vous pouvez configurer des noms d'utilisateur et mots de passe pour plus de sécurité.
   - Créez un fichier de mots de passe MQTT :
     ```bash
     sudo mosquitto_passwd -c /etc/mosquitto/passwd votre_utilisateur
     ```
   - Activez l’authentification dans le fichier de configuration Mosquitto :
     ```bash
     sudo nano /etc/mosquitto/mosquitto.conf
     ```
     Ajoutez ces lignes :
     ```
     allow_anonymous false
     password_file /etc/mosquitto/passwd
     ```

3. **Redémarrez Mosquitto pour appliquer les modifications** :
   ```bash
   sudo service mosquitto restart
   ```

---

## 5. Tests de Communication MQTT

1. **Vérifiez la connexion MQTT entre les appareils** :
   - **Sur le Raspberry Pi**, ouvrez un terminal et abonnez-vous à un topic MQTT :
     ```bash
     mosquitto_sub -h localhost -t "test/topic"
     ```
   - **Depuis un autre terminal ou appareil** (par exemple, un ESP8266), publiez un message pour tester la connexion :
     ```bash
     mosquitto_pub -h localhost -t "test/topic" -m "Hello, MQTT!"
     ```
   - Si tout fonctionne, vous devriez voir le message `Hello, MQTT!` dans le terminal où vous êtes abonné.

---

## 6. Installation de Python et des Bibliothèques MQTT pour les Scripts

Pour exécuter les scripts de gestion des gants et des actions de jeu :

1. **Installer Python et la bibliothèque `paho-mqtt`** :
   ```bash
   sudo apt install python3-pip
   pip3 install paho-mqtt
   ```

2. **Exécuter le Script Python pour Détecter les Actions des Gants** :
   - Naviguez dans le dossier contenant `detectBouton.py` et lancez-le :
     ```bash
     python3 detectBouton.py
     ```

---

## 7. Dépannage

- **Mosquitto ne démarre pas** : Vérifiez si un autre processus utilise le port 1883. Utilisez `sudo netstat -tuln | grep 1883` pour vérifier.
- **Problèmes de connexion Wi-Fi** : Assurez-vous que le Raspberry Pi est bien connecté au SSID `binome_CSFA` et que le mot de passe est correct.
- **Messages MQTT non reçus** : Vérifiez les adresses IP et assurez-vous que tous les appareils sont sur le même réseau.

---

Votre Raspberry Pi est maintenant prêt et configuré pour le projet Minecraft avec les gants connectés. Vous pouvez maintenant tester les interactions entre le Raspberry Pi et les ESP8266 via MQTT.
``` 

Ce guide complet devrait vous permettre de configurer votre Raspberry Pi pour la communication MQTT et pour gérer les actions des gants connectés dans le jeu Minecraft.

2. **Vérifiez que Mosquitto fonctionne** :
   - Pour vérifier si Mosquitto est en cours d’exécution, tapez :
     ```bash
     sudo service mosquitto status
     ```
   - Vous devriez voir quelque chose comme :
     ```
     ● mosquitto.service - LSB: mosquitto MQTT v3.1 message broker
        Loaded: loaded (/etc/init.d/mosquitto)
        Active: active (running) since [date] [time]; [time] ago
     ```

3. **Commandes de Gestion de Mosquitto** :
   - Démarrer Mosquitto :
     ```bash
     sudo service mosquitto start
     ```
   - Arrêter Mosquitto :
     ```bash
     sudo service mosquitto stop
     ```
   - Redémarrer Mosquitto :
     ```bash
     sudo service mosquitto restart
     ```

---

## 4. Configuration du Serveur Mosquitto

1. **Configurer Mosquitto pour démarrer automatiquement** :
   ```bash
   sudo systemctl enable mosquitto
   ```

2. **Configuration de la Sécurité MQTT** (optionnel) :
   - Par défaut, Mosquitto permet des connexions sans authentification. Vous pouvez configurer des noms d'utilisateur et mots de passe pour plus de sécurité.
   - Créez un fichier de mots de passe MQTT :
     ```bash
     sudo mosquitto_passwd -c /etc/mosquitto/passwd votre_utilisateur
     ```
   - Activez l’authentification dans le fichier de configuration Mosquitto :
     ```bash
     sudo nano /etc/mosquitto/mosquitto.conf
     ```
     Ajoutez ces lignes :
     ```
     allow_anonymous false
     password_file /etc/mosquitto/passwd
     ```

3. **Redémarrez Mosquitto pour appliquer les modifications** :
   ```bash
   sudo service mosquitto restart
   ```

---

## 5. Tests de Communication MQTT

1. **Vérifiez la connexion MQTT entre les appareils** :
   - **Sur le Raspberry Pi**, ouvrez un terminal et abonnez-vous à un topic MQTT :
     ```bash
     mosquitto_sub -h localhost -t "test/topic"
     ```
   - **Depuis un autre terminal ou appareil** (par exemple, un ESP8266), publiez un message pour tester la connexion :
     ```bash
     mosquitto_pub -h localhost -t "test/topic" -m "Hello, MQTT!"
     ```
   - Si tout fonctionne, vous devriez voir le message `Hello, MQTT!` dans le terminal où vous êtes abonné.

---

## 6. Installation de Python et des Bibliothèques MQTT pour les Scripts

Pour exécuter les scripts de gestion des gants et des actions de jeu :

1. **Installer Python et la bibliothèque `paho-mqtt`** :
   ```bash
   sudo apt install python3-pip
   pip3 install paho-mqtt
   ```

2. **Exécuter le Script Python pour Détecter les Actions des Gants** :
   - Naviguez dans le dossier contenant `detectBouton.py` et lancez-le :
     ```bash
     python3 detectBouton.py
     ```

---

## 7. Dépannage

- **Mosquitto ne démarre pas** : Vérifiez si un autre processus utilise le port 1883. Utilisez `sudo netstat -tuln | grep 1883` pour vérifier.
- **Problèmes de connexion Wi-Fi** : Assurez-vous que le Raspberry Pi est bien connecté au SSID `binome_CSFA` et que le mot de passe est correct.
- **Messages MQTT non reçus** : Vérifiez les adresses IP et assurez-vous que tous les appareils sont sur le même réseau.

---

Votre Raspberry Pi est maintenant prêt et configuré pour le projet Minecraft avec les gants connectés. Vous pouvez maintenant tester les interactions entre le Raspberry Pi et les ESP8266 via MQTT.
``` 

Ce guide complet devrait vous permettre de configurer votre Raspberry Pi pour la communication MQTT et pour gérer les actions des gants connectés dans le jeu Minecraft.