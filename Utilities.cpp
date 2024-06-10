#include <TimeLib.h>
#include "Utilities.h"

String getFormattedDate(NTPClient &timeClient) {
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

