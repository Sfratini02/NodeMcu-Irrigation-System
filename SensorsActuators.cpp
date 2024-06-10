#include <Arduino.h>
#include <Servo.h>
#include "SensorsActuators.h"

const int sensorPins[] = {32, 33, 34, 35, 36};
const int numSensors = sizeof(sensorPins) / sizeof(sensorPins[0]);
const int moistureMin[] = {500, 450, 480, 510, 530};
const int moistureMax[] = {500, 450, 480, 510, 530};

const int servoPin1 = 9;
const int servoPin2 = 10;
Servo servo1;
Servo servo2;

const int pumpPin = 25;

void setupServos() {
    servo1.attach(servoPin1);
    servo2.attach(servoPin2);
}

void setupPump() {
    pinMode(pumpPin, OUTPUT);
    digitalWrite(pumpPin, LOW);
}

void positionServos(int sensorIndex) {
    int positions[] = {45, 90};
    int pos = (sensorIndex < sizeof(positions) / sizeof(positions[0])) ? positions[sensorIndex] : 0;
    servo1.write(pos);
    servo2.write(pos);
    delay(1000);
}

float readTemperature() {
    return 25.0;
}

int SensorMedia(int sensorIndex) {
    int total = 0;
    for (int i = 0; i < 10; i++) {
        total += analogRead(sensorPins[sensorIndex]);
        delay(500);
    }
    return total / 10;
}

