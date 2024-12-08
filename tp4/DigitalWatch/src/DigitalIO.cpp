#include "DigitalIO.h"

void DigitalIO::initPins() {
    pinMode(SET_BUTTON, INPUT_PULLUP);
    pinMode(STARTSTOP_BUTTON, INPUT_PULLUP);
    pinMode(LIGHT_BUTTON, INPUT_PULLUP);
    pinMode(MODE_BUTTON, INPUT_PULLUP);

    pinMode(LIGHT, OUTPUT);
}

bool DigitalIO::isSetButtonPressed() {
    return (digitalRead(SET_BUTTON) == LOW);
}

bool DigitalIO::isStartStopButtonPressed() {
    return (digitalRead(STARTSTOP_BUTTON) == LOW);
}

bool DigitalIO::isLightButtonPressed() {
    return (digitalRead(LIGHT_BUTTON) == LOW);
}

bool DigitalIO::isModeButtonPressed() {
    return (digitalRead(MODE_BUTTON) == LOW);
}

void DigitalIO::turnLightOn() {
    digitalWrite(LIGHT, HIGH); // light on
}

void DigitalIO::turnLightOff() {
    digitalWrite(LIGHT, LOW); // light off
}

void DigitalIO::toggleLight() {
    digitalWrite(LIGHT, !digitalRead(LIGHT)); // Toggle light
}
