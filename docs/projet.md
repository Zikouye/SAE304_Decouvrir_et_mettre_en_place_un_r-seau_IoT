# Projet Minecraft avec Gants Connectés

## 1. Introduction et Objectifs

Ce projet consiste à intégrer des gants connectés à une partie de Minecraft en réseau, permettant aux joueurs de bénéficier de superpouvoirs et de pièges. Les gants, équipés d'un ESP8266, permettent aux joueurs d'envoyer des actions spécifiques dans le jeu via MQTT.

### Objectifs Stratégiques
- **Structurer efficacement le projet** : Altay et Fatih ont défini les objectifs en tant que "Product Owners", et ont classé les objectifs en fonction de leur importance avec l'équipe de développement (Suha, Altay, Chadi, Fatih).
- **Avancement quotidien avec la méthode agile** : Des jalons ont été attribués chaque jour pour avancer dans les User Stories, favorisant une progression continue.
- **Outils de collaboration** : Discord a été central pour la communication et la gestion de projet, stockant des documents et centralisant l'avancement.

---

## 2. Méthodologie et Avancement du Projet

Un calendrier Niko Niko (méthode agile) a été utilisé pour suivre l'état d'esprit de l'équipe et l'avancement du projet, tandis que Mindview nous a aidés à garder une vision claire de notre progression.

Chaque jour, chaque membre se voyait attribuer un jalon d'une User Story pour assurer une avancée mutuelle sur les quatre User Stories.

---

## 3. Matériel Utilisé

1. **Dispositifs informatiques** : Les ordinateurs personnels pour les rapports et l'IUT pour les tests et la programmation.
2. **Raspberry Pi** : Utilisés pour héberger les scripts de gestion et le broker MQTT, ainsi que pour la session de jeu Minecraft.
3. **ESP8266** : Connectés aux gants pour transmettre les actions dans le jeu.
4. **Borne Wi-Fi Linksys** : Création d'un réseau privé pour connecter tous les dispositifs.
5. **Configuration initiale** : La borne Linksys a été configurée via "wireless" > "Basic Settings" pour permettre à toutes les machines de se connecter au réseau.

---

## 4. Installation et Configuration

### Installation du Système d'Exploitation sur le Raspberry Pi
1. Téléchargez le fichier système d'exploitation `2023-12-23-raspios-bullseye-ARM64.img.xz`.
2. Gravez l'image sur une carte SD, insérez-la dans le Raspberry Pi et démarrez pour confirmer l'installation.

### Connexion et Configuration de l'ESP8266
Dans le programme Arduino, l'ESP8266 doit se connecter à la borne Linksys et au serveur MQTT, permettant ainsi l'envoi de messages aux différents topics liés aux actions des doigts.

---

## 5. Superpouvoirs et Actions de Jeu

Chaque joueur peut activer quatre pouvoirs en appuyant sur les boutons des doigts de son gant, excepté le pouce :

- **Mettre de l'eau** sur l'adversaire (malus)
- **Placer plusieurs blocs** de pierre pour avancer sans tomber (bonus)
- **Créer des trous** dans le damier (malus)
- **Enfermer l'adversaire** dans des blocs de verre (malus)

Ces actions sont exécutées par un programme qui reçoit les messages MQTT et déclenche la fonction correspondante pour chaque pouvoir.

---

## 6. Communication MQTT

### Architecture MQTT
1. Chaque gant est relié à quatre topics spécifiques :
   - Pour le gant 1 : `gant1/index`, `gant1/majeur`, `gant1/auriculaire`, `gant1/annulaire`
   - Pour le gant 2 : `gant2/index`, `gant2/majeur`, `gant2/auriculaire`, `gant2/annulaire`

2. **Test de la connexion MQTT** : Nous avons testé la connexion en publiant et en souscrivant à un topic pour vérifier que le serveur MQTT fonctionne correctement.

### Configuration et Publication
- **Programme Arduino** : Il permet à l'ESP8266 de publier des messages dans les topics MQTT. Par exemple, lorsque la connexion au serveur MQTT est établie, l'ESP8266 publie un message `"hello world"` incrémenté toutes les secondes.
- **Détection de l'état des boutons** : Le bouton est configuré en `INPUT_PULLUP` et son changement d'état déclenche une publication dans le topic associé.

### Enregistreur MQTT
- **MQTT-LOGGER** : Utilisé pour surveiller les publications MQTT. Ce logger nous a aidés à identifier des problèmes tels que des publications répétées en cas d'appui unique.

### Script Python de Détection des Actions : `detectBouton.py`
- Ce script souscrit aux topics `gant1/#` et `gant2/#`. Lorsqu'une publication est reçue dans un topic spécifique, le pouvoir correspondant est activé :
  - Par exemple, une publication dans `gant1/index` déclenche le pouvoir de l'index du gant 1.

---

## 7. Schéma d'Architecture

*Ajoutez ici une image montrant le schéma d'architecture réseau, les connexions entre les Raspberry Pi, les ESP8266 et la borne Linksys.*

---

## 8. Résumé

Grâce à cette organisation de projet, à l'utilisation de Discord et d'outils collaboratifs, et à la méthode agile, nous avons réussi à atteindre les objectifs fixés. Les superpouvoirs des gants ajoutent une dimension immersive au jeu, tout en utilisant des technologies réseau et IoT pour un projet éducatif complet et engageant.
