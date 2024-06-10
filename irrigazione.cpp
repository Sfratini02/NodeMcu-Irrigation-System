#include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include <TimeLib.h>
#include <WiFiManager.h>

// Configurazione server NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600 * 2, 60000);

// Pin dei sensori di umidità del terreno
const int sensorPins[] = {32, 33, 34, 35, 36};
const int numSensors = sizeof(sensorPins) / sizeof(sensorPins[0]);
// Soglie di umidità del terreno
const int moistureMin[] = {500, 450, 480, 510, 530};
const int moistureMax[] = {500, 450, 480, 510, 530};

// Pin servo
const int servoPin1 = 9;
const int servoPin2 = 10;
Servo servo1;
Servo servo2;

// Pin pompa di irrigazione
const int pumpPin = 25; // Pin relè o transistor pompa

// Pin CS modulo SD
const int chipSelect = 5;

File file; // Variabile per il file della scheda SD

// Funzione per scrivere i dati su un file CSV
void writeCSV(const String &dataLine)
{
    file = SD.open("/irrigation_log.csv", FILE_APPEND);
    if (file)
    {
        file.println(dataLine);
        file.close();
    }
    else
    {
        Serial.println("Errore nell'apertura del file");
    }
}

// Funzione per configurare la connessione WiFi
void setupWiFi()
{
    WiFiManager wifiManager;
    if (!wifiManager.autoConnect("ConfigESP"))
    {
        Serial.println("Connessione fallita e timeout raggiunto");
        delay(3000);
        ESP.restart();
    }
    Serial.println("Connesso alla Wi-Fi!");
    Serial.println("Indirizzo IP: ");
    Serial.println(WiFi.localIP());
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    setupWiFi();

    // Inizializzazione e avvio del client NTP
    timeClient.begin();
    timeClient.update();
    Serial.println("Client NTP avviato nel setup:");
    Serial.println(timeClient.getFormattedTime());

    // Setup pin per i servomotori
    servo1.attach(servoPin1);
    servo2.attach(servoPin2);

    // Setup pin per la pompa
    pinMode(pumpPin, OUTPUT);
    digitalWrite(pumpPin, LOW);

    // Inizializzazione della scheda SD
    if (!SD.begin(chipSelect))
    {
        Serial.println("Errore di inizializzazione della SD");
        return;
    }
    Serial.println("SD inizializzata.");
}

void loop()
{
    // Aggiornamento dell'ora dal server NTP
    timeClient.update();
    String formattedTime = timeClient.getFormattedTime();
    Serial.println("Ora aggiornata: " + formattedTime);

    float litersUsed = 0.0; // Placeholder per i litri usati
    float externalTemperature = readTemperature(); // Lettura della temperatura esterna

    // Loop attraverso ciascun sensore di umidità
    for (int i = 0; i < numSensors; i++)
    {
        int beforeMoisture = SensorMedia(i); // Lettura media del sensore
        int afterMoisture;

        Serial.print("Umidità sensore ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(beforeMoisture);

        // Controllo dell'umidità del terreno
        if (beforeMoisture < moistureMin[i])
        {
            Serial.println("Terreno troppo asciutto. Attivazione irrigazione...");
            positionServos(i); // Posizionamento dei servomotori
            int pumpTime = 0;

            while (beforeMoisture < moistureMin[i])
            {
                delay(1000);
                digitalWrite(pumpPin, HIGH); // Accensione della pompa
                delay(5000); // Irrigazione per 5 secondi
                digitalWrite(pumpPin, LOW); // Spegnimento della pompa
                pumpTime += 5;
                delay(10000); // Attesa prima di un'altra lettura
                beforeMoisture = SensorMedia(i); // Nuova lettura del sensore
                Serial.print("Umidità sensore ");
                Serial.print(i);
                Serial.print(": ");
                Serial.println(beforeMoisture);
            }

            afterMoisture = SensorMedia(i); // Lettura del sensore dopo l'irrigazione
            logData(i, beforeMoisture, afterMoisture, litersUsed, externalTemperature); // Registrazione dei dati
        }
        else
        {
            Serial.println("Terreno sufficientemente umido");
            afterMoisture = analogRead(sensorPins[i]); // Lettura del sensore
            logData(i, beforeMoisture, afterMoisture, litersUsed, externalTemperature); // Registrazione dei dati
        }
    }

    delay(60000); // Attesa di un minuto prima di ripetere il ciclo
}

// Funzione per posizionare i servomotori
void positionServos(int sensorIndex)
{
    int positions[] = {45, 90}; // Definisci le posizioni dei servomotori per ciascun sensore
    int pos = (sensorIndex < sizeof(positions) / sizeof(positions[0])) ? positions[sensorIndex] : 0;

    servo1.write(pos);
    servo2.write(pos);
    delay(1000); // Tempo per permettere ai servomotori di muoversi
}

// Funzione placeholder per leggere la temperatura
float readTemperature()
{
    return 25.0; // Esempio: ritorna una temperatura fittizia
}

// Funzione per calcolare la media delle letture di un sensore
int SensorMedia(int sensorIndex)
{
    int total = 0;
    for (int i = 0; i < 10; i++)
    {
        total += analogRead(sensorPins[sensorIndex]);
        delay(500);
    }
    return total / 10;
}

// Funzione per ottenere la data formattata
String getFormattedDate(NTPClient &timeClient)
{
    unsigned long epochTime = timeClient.getEpochTime();
    setTime(epochTime);

    int yr = year();
    int mnth = month();
    int dy = day();

    String yearStr = String(yr);
    String monthStr = mnth < 10 ? "0" + String(mnth) : String(mnth);
    String dayStr = dy < 10 ? "0" + String(dy) : String(dy);

    return dayStr + "-" + monthStr + "-" + yearStr;
}

// Funzione per registrare i dati di irrigazione
void logData(int sensorIndex, int beforeMoisture, int afterMoisture, float litersUsed, float externalTemperature)
{
    String currentDate = getFormattedDate(timeClient);
    String currentTime = timeClient.getFormattedTime();
    String dataLine = currentDate + "," +
                      currentTime + "," +
                      String(sensorIndex) + "," +
                      String(beforeMoisture) + "," +
                      String(afterMoisture) + "," +
                      String(litersUsed, 2) + "," +
                      String(externalTemperature, 2);
    writeCSV(dataLine);
}

