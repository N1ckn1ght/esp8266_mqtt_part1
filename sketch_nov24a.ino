#include <ESP8266WiFi.h>
#include "Config.h"
#include "Server.h"
#include "WiFi.h"
#include "MQTT.h"

void setup() {
    Serial.begin(115200);
    pinMode(led_pin, OUTPUT);
    WIFI_init(MODE_AP);
    server_init();
    MQTT_init();
    String unique_topic = "foo";
    mqtt_client.publish((unique_topic + String("/state")).c_str(), "hello");
    mqtt_client.subscribe((unique_topic + String("/command")).c_str());
}

void loop() {
  server.handleClient();
  mqtt_client.loop();
}
