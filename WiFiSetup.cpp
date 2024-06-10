#include <WiFiManager.h>
#include "WiFiSetup.h"

void setupWiFi() {
    WiFiManager wifiManager;
    if (!wifiManager.autoConnect("ConfigESP")) {
        Serial.println("Connessione fallita e timeout raggiunto");
        delay(3000);
        ESP.restart();
    }
    Serial.println("Connesso alla Wi-Fi!");
    Serial.println("Indirizzo IP: ");
    Serial.println(WiFi.localIP());
}

