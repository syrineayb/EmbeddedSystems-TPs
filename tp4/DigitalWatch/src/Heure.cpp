#include "Heure.h"

void Heure::razSeconds() {
    seconds = 0;
}

void Heure::incMinutes() {
    minutes++;
    if (minutes >= 60) {
        minutes = 0;
        incHeure();
    }
}

void Heure::incHeure() {
    hours++;
    if (hours >= 24) {
        hours = 0;
    }
}

String Heure::toString() {
    String hourStr = String(hours);
    String minuteStr = String(minutes);
    String secondStr = String(seconds);

    if (hours < 10) hourStr = "0" + hourStr;
    if (minutes < 10) minuteStr = "0" + minuteStr;
    if (seconds < 10) secondStr = "0" + secondStr;

    return hourStr + ":" + minuteStr + ":" + secondStr;
}
