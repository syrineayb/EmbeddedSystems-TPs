#include "VehicleParkingLogic.h"
#include <Arduino.h>

VehicleParkingLogic::VehicleParkingLogic()
    : currentState(VEHICLE_ABSENT), lastActionTime(0), orangeLEDState(false), 
      greenLightState(false), redLightState(true), barrierState(false), orangeLEDLastChangeTime(0) {}

void VehicleParkingLogic::updateState(bool vehicleDetected, bool buttonPressed, bool vehicleExited, unsigned long currentTime) {
    switch (currentState) {
        case VEHICLE_ABSENT:
            if (vehicleDetected) {
                currentState = VEHICLE_PRESENT;
                redLightState = false;
                greenLightState = false;
            }
            break;
        case VEHICLE_PRESENT:
            if (buttonPressed) {
                currentState = BUTTON_PRESSED;
                greenLightState = true;
                barrierState = true;
                lastActionTime = currentTime;
            } else if (vehicleExited) {
                currentState = VEHICLE_EXITED;
                redLightState = true;
                barrierState = false;
            }
            break;
        case BUTTON_PRESSED:
            if (currentTime - lastActionTime > 20000) { // 20 seconds of inactivity
                currentState = INACTIVE;
                redLightState = false;
                greenLightState = false;
            }
            break;
        case VEHICLE_EXITED:
            if (!vehicleDetected) {
                currentState = VEHICLE_ABSENT;
                redLightState = true;
                greenLightState = false;
                barrierState = false;
            }
            break;
        case INACTIVE:
            toggleOrangeLED(); // Blink orange LED when inactive
            break;
    }
}

void VehicleParkingLogic::toggleOrangeLED() {
    unsigned long currentTime = millis();
    if (currentTime - orangeLEDLastChangeTime >= ORANGE_BLINK_FREQ) {
        orangeLEDState = !orangeLEDState;
        orangeLEDLastChangeTime = currentTime;
    }
}

bool VehicleParkingLogic::isRedLightOn() const {
    return redLightState;
}

bool VehicleParkingLogic::isOrangeLightBlinking() const {
    return orangeLEDState;
}

bool VehicleParkingLogic::isGreenLightOn() const {
    return greenLightState;
}

bool VehicleParkingLogic::isBarrierOpen() const {
    return barrierState;
}
