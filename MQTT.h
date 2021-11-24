#include <PubSubClient.h>

PubSubClient mqtt_client(wificlient);

void callback(char* topic, byte* payload, unsigned int len) {
  Serial.println(topic);
  for (int i = 0; i < len; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
}

void MQTT_init() {
  mqtt_client.setServer(mqtt_broker, mqtt_port);
  mqtt_client.setCallback(callback);
  String client_id = "esp8266-" + String(WiFi.macAddress());
  while (!mqtt_client.connected()) {
    if(mqtt_client.connect(client_id.c_str())) {
      Serial.println("MQTT connected with id:");
      Serial.println(client_id);
    } else{
      Serial.println("MQTT failed");
    }
  }
}
