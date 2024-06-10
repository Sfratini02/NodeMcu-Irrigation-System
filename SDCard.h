#ifndef SDCARD_H
#define SDCARD_H

void setupSDCard();
void writeCSV(const String &dataLine);
void logData(int sensorIndex, int beforeMoisture, int afterMoisture, float litersUsed, float externalTemperature);

#endif // SDCARD_H

