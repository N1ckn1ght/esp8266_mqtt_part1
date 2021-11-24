#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void handleRoot() {
	server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
}

void handleLED() {
	digitalWrite(led_pin, !digitalRead(led_pin));
	server.sendHeader("Location", "/");
	server.send(303);
  Serial.println("debug, handled LED:");
  Serial.println(!digitalRead(led_pin));
}

void server_init() {
	server.on("/", HTTP_GET, handleRoot);
	server.on("/LED", HTTP_POST, handleLED);
	server.begin();
	Serial.println("HTTP server started!");
}
