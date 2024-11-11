# 🧤 Projet Minecraft Gant Connecté 🎮

![Bannière du projet](images/minecraft.jpg)

## 🎯 Objectifs du Projet

Ce projet a pour but de **créer une infrastructure IoT** permettant à deux joueurs de jouer à une partie spéciale de Minecraft, en réseau, avec des **gants connectés** qui leur fournissent des superpouvoirs et pièges pour battre leur adversaire.

## 📋 Description

### User Story 1
Deux joueurs jouent en réseau à Minecraft pour trouver le plus rapidement possible un diamant caché de manière aléatoire.

### User Story 2
Chaque joueur dispose d'un gant connecté qui leur permet d'utiliser des superpouvoirs et des pièges (malus) contre leur adversaire dans le jeu.

### User Story 3
Chaque gant a un bouton sur chaque doigt (sauf le pouce), permettant d'activer différentes actions dans le jeu. Les gants sont autonomes grâce à une batterie connectée.

## 🛠️ Éléments Techniques

Le projet utilise :
- **ESP8266** pour la gestion des boutons sur les gants et la connexion réseau.
- **Raspberry Pi 4** pour gérer la logique de jeu et la connexion au serveur Minecraft.
- **Protocole MQTT** pour la communication entre les ESP8266 et les Raspberry Pi.
- **Routeur Linksys** pour fournir le réseau.

## 📂 Structure du Projet

```plaintext
minecraft-gant-projet/
│
├── README.md                # Description du projet et des objectifs
├── LICENSE                  # Licence du projet
│
├── arduino/
│   ├── bouton.ino           # Code pour gérer les boutons sur ESP8266
│   ├── connect_wifi.ino     # Code pour la connexion Wi-Fi sur ESP8266
│   ├── pub.ino              # Code pour publier les actions via MQTT
│   └── detect_pub.ino       # Code pour détecter et publier les actions spécifiques de chaque bouton
│
├── raspberry_pi/
│   ├── detectBouton.py      # Script Python pour réception des actions via MQTT
│   └── appel_pouvoirs.py    # Script pour exécuter les superpouvoirs et malus
│
├── docs/
│   ├── projet.md            # Objectifs, user stories et détails techniques
│   └── architecture.png     # Diagramme de l'infrastructure réseau et des connexions
│
├── setup/
│   ├── esp8266_setup.md     # Instructions pour configurer les ESP8266
│   ├── raspberry_setup.md   # Instructions pour configurer les Raspberry Pi
│   └── router_setup.md      # Configuration du routeur Linksys et MQTT
│
└── images/
    └── gant_diagram.png     # Schéma du gant avec emplacement des boutons

    
```
## 📜 License

Ce projet est sous licence MIT - voir le fichier [LICENSE](LICENSE) pour plus de détails.

## ✨ Contributeurs

- **Suha Kut** - 
- **Chadi Abouhnaik** -  
- **Fatih Kilic** -
- **Altay Cevik** - 

