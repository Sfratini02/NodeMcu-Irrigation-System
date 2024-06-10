#include <SD.h>
#include "NTPClientSetup.h"
#include "SDCard.h"
#include "Utilities.h"

const int chipSelect = 5;
File file;

void setupSDCard() {
    if (!SD.begin(chipSelect)) {
        Serial.println("Errore di inizializzazione della SD");
        return;
    }
    Serial.println("SD inizializzata.");
}

void writeCSV(const String &dataLine) {
    file = SD.open("/irrigation_log.csv", FILE_APPEND);
    if (file) {
        file.println(dataLine);
        file.close();
    } else {
        Serial.println("Errore nell'apertura del file");
    }
}

void logData(int sensorIndex, int beforeMoisture, int afterMoisture, float litersUsed, float externalTemperature) {
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

