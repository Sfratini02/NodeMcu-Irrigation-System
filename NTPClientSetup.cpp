#include <NTPClient.h>
#include <WiFiUdp.h>
#include "NTPClientSetup.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600 * 2, 60000);

void setupNTPClient() {
    timeClient.begin();
    timeClient.update();
    Serial.println("Client NTP avviato nel setup:");
    Serial.println(timeClient.getFormattedTime());
}

void updateNTPClient() {
    timeClient.update();
}

String getFormattedTime() {
    return timeClient.getFormattedTime();
}

