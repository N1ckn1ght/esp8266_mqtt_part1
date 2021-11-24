#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifimulti;
WiFiClient wificlient;

String ip = "IP UNSET"; 

String id() {
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  return macID;
}

bool startAP() {
  WiFi.disconnect();
  IPAddress apIP(192, 168, 4, 1);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP((ssidAP + " " + id()).c_str(), passwordAP.c_str());
  Serial.println("WIFI AP start " + ssidAP + " " + id());
  return true;
}

bool startCLI() {
  wifimulti.addAP(ssidCLI.c_str(), passwordCLI.c_str());
  while (wifimulti.run() != WL_CONNECTED) {
    Serial.println("please help");
    delay(1000);
  }
  return true;
}

void WIFI_init(bool mode_ap) {
  if (mode_ap){
    startAP();
    ip = WiFi.softAPIP().toString();
  } else {
    startCLI();
    ip = WiFi.localIP().toString();
  }
  Serial.println("IP Address: ");
  Serial.println(ip);
}
