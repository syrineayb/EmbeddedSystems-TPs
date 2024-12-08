#include "ParkingManager.h"
#include <Arduino.h>

ParkingManager::ParkingManager()
    : parkingLogic(), hardwareController() {}

void ParkingManager::initialize() {
    // Initialize LEDs and barrier to default states
    hardwareController.setLEDState(RED_LED_PIN, HIGH);  // Red LED ON
    hardwareController.setLEDState(ORANGE_LED_PIN, LOW);  // Orange LED OFF
    hardwareController.setLEDState(GREEN_LED_PIN, LOW);  // Green LED OFF
    hardwareController.controlBarrier(false);  // Barrière fermée 
}

void ParkingManager::handleSensorData(bool vehicleDetected, bool buttonPressed, bool vehicleExited) {
    // Get the current time
    unsigned long currentTime = millis();

    // Update the parking logic state based on sensor data
    parkingLogic.updateState(vehicleDetected, buttonPressed, vehicleExited, currentTime);
}

void ParkingManager::updateLEDs() {
    hardwareController.setLEDState(RED_LED_PIN, parkingLogic.isRedLightOn());  // Red LED
    hardwareController.setLEDState(ORANGE_LED_PIN, parkingLogic.isOrangeLightBlinking());  // Orange LED blinking
    hardwareController.setLEDState(GREEN_LED_PIN, parkingLogic.isGreenLightOn());  // Green LED
}

void ParkingManager::updateBarrier() {
    hardwareController.controlBarrier(parkingLogic.isBarrierOpen());  // Open or close the barrier
}

void ParkingManager::toggleOrangeLED() {
    parkingLogic.toggleOrangeLED();  
}

bool ParkingManager::isRedLightOn() {
    return parkingLogic.isRedLightOn();
}

bool ParkingManager::isGreenLightOn() {
    return parkingLogic.isGreenLightOn();
}

bool ParkingManager::isOrangeLightBlinking() {
    return parkingLogic.isOrangeLightBlinking();
}

bool ParkingManager::isBarrierOpen() {
    return parkingLogic.isBarrierOpen();
}
