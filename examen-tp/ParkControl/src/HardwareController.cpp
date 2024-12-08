#include "HardwareController.h"
#include <Arduino.h>

HardwareController::HardwareController() {}

bool HardwareController::readVehiclePresence() {
    return digitalRead(32); 
}

bool HardwareController::readButtonPress() {
    return digitalRead(33); 
}

bool HardwareController::readVehicleExit() {
    return digitalRead(34);
}

void HardwareController::setLEDState(int ledPin, bool state) {
    digitalWrite(ledPin, state ? HIGH : LOW);
}

void HardwareController::controlBarrier(bool state) {
    digitalWrite(25, state ? HIGH : LOW); 
}
