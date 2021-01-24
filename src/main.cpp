#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "settings.h"

void startWifi();
void startServer();
ESP8266WebServer server(80);

void setup() {
    Serial.begin(9600);
    Serial.print("\n\n\n");

    startWifi();
    startServer();
}

void loop() {
// write your code here
    server.handleClient();
}


void startWifi() {
    Serial.println("Connecting to: ");
    Serial.println(ssid);

    WiFi.hostname(hostName);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.print("\nSuccessfully connected to: ");
    Serial.println(ssid);
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

void test(){
    server.send(200, "text/html", "Manuel");
}

void startServer(){
    server.on("/", test);
    server.begin();
}