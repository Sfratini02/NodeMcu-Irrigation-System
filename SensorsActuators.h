#ifndef SENSORS_ACTUATORS_H
#define SENSORS_ACTUATORS_H

extern const int sensorPins[];
extern const int numSensors;
extern const int moistureMin[];
extern const int moistureMax[];

void setupServos();
void setupPump();
void positionServos(int sensorIndex);
float readTemperature();
int SensorMedia(int sensorIndex);

#endif // SENSORS_ACTUATORS_H

