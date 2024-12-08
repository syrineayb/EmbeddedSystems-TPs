#ifndef PARKINGMANAGER_H
#define PARKINGMANAGER_H

#include "VehicleParkingLogic.h"
#include "HardwareController.h"

class ParkingManager {  //  Gère la logique globale du système.
public:
    ParkingManager();

    // Initialize the parking system, setting up LEDs and the barrier
    void initialize();

    // Handle sensor data and update the parking logic state
    void handleSensorData(bool vehicleDetected, bool buttonPressed, bool vehicleExited);

    // Update the LEDs based on parking logic
    void updateLEDs();

    // Update the barrier based on parking logic
    void updateBarrier();

    // Toggle the orange LED
    void toggleOrangeLED();

    // Getters for LED and barrier states
    bool isRedLightOn();
    bool isGreenLightOn();
    bool isOrangeLightBlinking();
    bool isBarrierOpen();

private:
    VehicleParkingLogic parkingLogic;
    HardwareController hardwareController;

    const int RED_LED_PIN = 26;
    const int ORANGE_LED_PIN = 27;
    const int GREEN_LED_PIN = 14;
    const int BARRIER_PIN = 25;
};

#endif
