#include "Chronometre.h"

void Chronometre::raz() {
    startTime = 0;
    elapsedTime = 0;
    running = false;
}

bool Chronometre::start() {
    if (!running) {
        startTime = millis() - elapsedTime;
        running = true;
        return true;
    }
    return false;
}

bool Chronometre::stop() {
    if (running) {
        elapsedTime = millis() - startTime;
        running = false;
        return true;
    }
    return false;
}

String Chronometre::toString() {
    unsigned long time = running ? millis() - startTime : elapsedTime;
    int seconds = (time / 1000) % 60;
    int minutes = (time / 60000) % 60;
    int hours = (time / 3600000) % 24;
    return String(hours) + ":" + String(minutes) + ":" + String(seconds);
}
