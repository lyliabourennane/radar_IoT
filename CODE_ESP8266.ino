#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid     = "iPhone";
const char* password = "zahra000";
const char* mqttHost = "3e58230b148543c38efa9f7ddb0e873d.s1.eu.hivemq.cloud";
const int   mqttPort = 8883;
const char* mqttUser = "radar_user";
const char* mqttPass = "Lylia2005";

WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  espClient.setInsecure();
  client.setServer(mqttHost, mqttPort);
  while (!client.connect("ESP8266Radar", mqttUser, mqttPass)) delay(1000);
}

void loop() {
  if (!client.connected()) {
    while (!client.connect("ESP8266Radar", mqttUser, mqttPass)) delay(1000);
  }
  client.loop();

  if (Serial.available()) {
    String data = Serial.readStringUntil('.');
    int comma = data.indexOf(',');
    if (comma > 0) {
      int angle = data.substring(0, comma).toInt();
      int dist  = data.substring(comma + 1).toInt();
      StaticJsonDocument<64> doc;
      doc["angle"] = angle;
      doc["dist"]  = dist;
      char buf[64];
      serializeJson(doc, buf);
      client.publish("radar/data", buf);
    }
  }
}