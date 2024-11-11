# Configuration de l'ESP8266 pour le Projet Minecraft avec Gant Connecté

Ce guide détaille les étapes pour configurer l'ESP8266 dans l'IDE Arduino, installer les bibliothèques nécessaires, et se connecter à la borne Wi-Fi Linksys.

## 1. Pré-requis

- **Matériel** : ESP8266
- **IDE Arduino** : Téléchargez et installez [l'IDE Arduino](https://www.arduino.cc/en/software) si ce n'est pas déjà fait.
- **Connexion Wi-Fi** : Un réseau configuré sur une borne Linksys (SSID et mot de passe fournis dans les étapes suivantes).

---

## 2. Configuration de l'IDE Arduino pour ESP8266

1. **Ajouter le support de l'ESP8266** :
   - Ouvrez l'IDE Arduino.
   - Allez dans `Fichier` > `Préférences`.
   - Dans le champ `URL de gestionnaire de cartes supplémentaires`, ajoutez l'URL suivante :
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
   - Cliquez sur **OK** pour enregistrer.

2. **Installer le package ESP8266** :
   - Allez dans `Outils` > `Type de carte` > `Gestionnaire de cartes`.
   - Recherchez "ESP8266" et installez le package `ESP8266 by ESP8266 Community`.

3. **Sélectionner la carte ESP8266** :
   - Allez dans `Outils` > `Type de carte` et sélectionnez votre modèle d'ESP8266 (par exemple, `NodeMCU 1.0 (ESP-12E Module)`).

---

## 3. Installation des Bibliothèques Nécessaires

1. **Installer la bibliothèque WiFi** :
   - La bibliothèque WiFi est incluse par défaut dans le package ESP8266. Elle sera utilisée pour connecter l'ESP8266 au réseau.

2. **Installer la bibliothèque PubSubClient** pour MQTT :
   - Allez dans `Croquis` > `Inclure une bibliothèque` > `Gérer les bibliothèques`.
   - Recherchez "PubSubClient" et installez-la. Cette bibliothèque sera utilisée pour gérer la communication MQTT.

---

## 4. Configuration du Réseau Wi-Fi

Connectez l'ESP8266 au réseau Wi-Fi de la borne Linksys en modifiant les informations réseau dans votre code Arduino.

### Exemple de Code pour la Connexion Wi-Fi

Dans les fichiers `.ino` (par exemple, `connect_wifi.ino`), ajoutez les informations Wi-Fi suivantes :

```cpp
#include <ESP8266WiFi.h>

const char* ssid = "binome_CSFA";        // Nom de votre réseau Wi-Fi
const char* password = "tpRT9025";       // Mot de passe du réseau Wi-Fi

void setup() {
  Serial.begin(115200);

  // Connexion au réseau Wi-Fi
  WiFi.begin(ssid, password);

  Serial.print("Connexion à ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connecté");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Reste de votre code
}
