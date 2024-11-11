#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define LED_PIN         12
#define BOUTON_ANNULAIRE   4
#define BOUTON_AURICULAIRE  0
#define BOUTON_MAJEUR  5
#define BOUTON_INDEX 12




// Update these with values suitable for your network.

const char* ssid = "binome_CSFA";
const char* password = "TPrt9025";
const char* mqtt_server = "192.168.1.109";
int auriculaire = 0;
int annulaire = 0;
int majeur = 0;
int index_ = 0;
int AncienEtat;
const unsigned long debounceDelay = 100;
unsigned long lastDebounceTime = 0;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (250)
char msg[MSG_BUFFER_SIZE];
int value = 0;
char valeur[10];

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    valeur[i] = (char)payload[i];
  }
  if(valeur[0] == 'O'&& valeur[1] == 'N' ){
    digitalWrite(BUILTIN_LED, LOW);  
  }
  if(valeur[0] == 'O'&& valeur[1] == 'F' && valeur[2] == 'F' ){

    digitalWrite(BUILTIN_LED, HIGH);  
  }
  Serial.println(valeur);
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void ICACHE_RAM_ATTR auriculaireEvent() {
  // Vérifier le délai de rebond
  if (millis() - lastDebounceTime < debounceDelay) {
    return;
  }

  // Mettre à jour le temps du dernier rebond
  lastDebounceTime = millis();

  // Le reste du code de la fonction auriculaireEvent
  auriculaire = !auriculaire;
  Serial.println("Bouton auriculaire : Pouvoir active");
  snprintf (msg, MSG_BUFFER_SIZE, "%ld", auriculaire);
  client.publish("gant1/auriculaire" , msg);
  Serial.print("Publish message: ");
  Serial.println(msg);
}

void ICACHE_RAM_ATTR annulaireEvent() {
    // Vérifier le délai de rebond
  if (millis() - lastDebounceTime < debounceDelay) {
    return;
  }

  // Mettre à jour le temps du dernier rebond
  lastDebounceTime = millis();
  annulaire = !annulaire;
  Serial.println("Bouton annulaire : Pouvoir active");
  snprintf (msg, MSG_BUFFER_SIZE, "%ld", annulaire);
  client.publish("gant1/annulaire" , msg);
  Serial.print("Publish message: ");
  Serial.println(msg);
}

void ICACHE_RAM_ATTR majeurEvent() {
    // Vérifier le délai de rebond
  if (millis() - lastDebounceTime < debounceDelay) {
    return;
  }

  // Mettre à jour le temps du dernier rebond
  lastDebounceTime = millis();

  majeur = !majeur;
  Serial.println("Bouton majeur : Pouvoir active");
  snprintf (msg, MSG_BUFFER_SIZE, "%ld", majeur);
  client.publish("gant1/majeur" , msg);
  Serial.print("Publish message: ");
  Serial.println(msg);
}

void ICACHE_RAM_ATTR indexEvent() {
    // Vérifier le délai de rebond
  if (millis() - lastDebounceTime < debounceDelay) {
    return;
  }

  // Mettre à jour le temps du dernier rebond
  lastDebounceTime = millis();

  index_ = !index_;
  Serial.println("Bouton index : Pouvoir active");
  snprintf (msg, MSG_BUFFER_SIZE, "%ld", index_);
  client.publish("gant1/index" , msg);
  Serial.print("Publish message: ");
  Serial.println(msg);
}



void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(BOUTON_ANNULAIRE, INPUT_PULLUP);
  pinMode(BOUTON_AURICULAIRE, INPUT_PULLUP);
  pinMode(BOUTON_MAJEUR, INPUT_PULLUP);
  pinMode(BOUTON_INDEX, INPUT_PULLUP);
  attachInterrupt(BOUTON_ANNULAIRE, annulaireEvent, RISING);
  attachInterrupt(BOUTON_AURICULAIRE, auriculaireEvent, RISING);
  attachInterrupt(BOUTON_MAJEUR, majeurEvent, RISING);
  attachInterrupt(BOUTON_INDEX, indexEvent, RISING);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
  }
}
