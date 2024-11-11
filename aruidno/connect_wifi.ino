#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const char* ssid = "binome_CSFA";
const char* password = "TPrt9025";
const char* mqtt_server = "192.168.1.109";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

#define BUTTON_PIN 0 // GPIO0
#define LED_PIN 2 // GPIO2

void setup() {

  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au réseau WiFi...");
  }
  Serial.println("Connecté au réseau WiFi");


  pinMode(BUTTON_PIN, INPUT_PULLUP);


  pinMode(LED_PIN, OUTPUT);


  mqttClient.setCallback(mqttCallback);

  mqttClient.setServer(mqtt_server, 1883);
  while (!mqttClient.connected()) {
    Serial.println("Connexion au broker MQTT...");
    if (mqttClient.connect("ESP8266Client")) {
      mqttClient.subscribe("carte2");
      Serial.println("Connecté au broker MQTT");
    } else {
      Serial.print("Échec de la connexion au broker MQTT, code d'erreur : ");
      Serial.println(mqttClient.state());
      delay(5000);
    }
  }
}

void loop() {
  
  mqttClient.loop();

  int buttonState = digitalRead(BUTTON_PIN);


  if (buttonState == LOW) {
    digitalWrite(LED_PIN, LOW);
  } else {
    digitalWrite(LED_PIN, HIGH);
  }

}

