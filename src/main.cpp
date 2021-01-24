#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <bits/stdc++.h>
using std::string;

#include "settings.h"

void startWifi();
void startServer();
void pressButton(const string& btnName);

ESP8266WebServer server(80);

// buttons on remote and their pin number
std::map<string, int> buttons {
        {"up", 16}, //D0 = GPIO16
        {"down", 14}, //D5 = GPIO14
        {"top", 12}, //D6 = GPIO12
        {"mid", 13}, //D7 = GPIO13
        {"bot", 15} //D8 = GPIO15
};

void setup() {
    Serial.begin(9600);
    Serial.print("\n\n\n");

    // set all pins from remote buttons to output mode and set them on high
    for (auto& button : buttons) {
        pinMode(button.second, OUTPUT);
        digitalWrite(button.second, HIGH);
    }


    startWifi(); // connects to wifi
    startServer(); // setups and starts server
}

void loop() {
    server.handleClient(); // handle requests
}


void startWifi() {
    Serial.println("Connecting to: ");
    Serial.println(ssid);

    // set hostname and password from settings file
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

void startServer(){
    server.on("/up", []() -> void {
        pressButton("up");
        server.send(200);
    });
    server.on("/down", []() -> void {
        pressButton("down");
        server.send(200);
    });
    server.begin();
}

void pressButton(const string& btnName) {
    const auto & button = buttons.find(btnName);
    digitalWrite(button->second, LOW);
    delay(250);
    digitalWrite(button->second, HIGH);
}