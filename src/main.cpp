#include <Arduino.h>
#include <WiFi.h>
#include "secrets.h"

void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.println("Hola Mundo - EQX");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Conectando a WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("Conectado! IP: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    Serial.println("Hola Mundo desde EQX");
    delay(2000);
}
