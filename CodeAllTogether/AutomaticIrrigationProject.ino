#include <Arduino.h>
#include "WiFiSetup.h"
#include "NTPClientSetup.h"
#include "SensorsActuators.h"
#include "SDCard.h"
#include "Utilities.h"

void setup() {
    Serial.begin(115200);
    delay(1000);

    setupWiFi();
    setupNTPClient();
    setupServos();
    setupPump();
    setupSDCard();
}

void loop() {
    updateNTPClient();
    String formattedTime = getFormattedTime();
    Serial.println("Ora aggiornata: " + formattedTime);

    float litersUsed = 0.0;
    float externalTemperature = readTemperature();

    for (int i = 0; i < numSensors; i++) {
        int beforeMoisture = SensorMedia(i);
        int afterMoisture;

        Serial.print("Umidità sensore ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(beforeMoisture);

        if (beforeMoisture < moistureMin[i]) {
            Serial.println("Terreno troppo asciutto. Attivazione irrigazione...");
            positionServos(i);
            int pumpTime = 0;

            while (beforeMoisture < moistureMin[i]) {
                delay(1000);
                digitalWrite(pumpPin, HIGH);
                delay(5000);
                digitalWrite(pumpPin, LOW);
                pumpTime += 5;
                delay(10000);
                beforeMoisture = SensorMedia(i);
                Serial.print("Umidità sensore ");
                Serial.print(i);
                Serial.print(": ");
                Serial.println(beforeMoisture);
            }

            afterMoisture = SensorMedia(i);
            logData(i, beforeMoisture, afterMoisture, litersUsed, externalTemperature);
        } else {
            Serial.println("Terreno sufficientemente umido");
            afterMoisture = analogRead(sensorPins[i]);
            logData(i, beforeMoisture, afterMoisture, litersUsed, externalTemperature);
        }
    }

    delay(60000);
}

