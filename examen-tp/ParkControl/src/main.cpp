#include <Arduino.h>
#include "ParkingManager.h"
#include "HardwareController.h"
#include "esp32-hal-timer.h"  

// Create instances of the controllers
ParkingManager parkingManager;
HardwareController hardwareController;

// Timer interrupt flag
volatile bool timerFlag = false; //

// ISR to handle timer interrupt
void IRAM_ATTR onTimer() {
    timerFlag = true; 
}

void setup() {
    Serial.begin(115200);
    while (!Serial); 
    Serial.println("Initializing Parking System...");
    parkingManager.initialize();

    // Configure the timer interrupt
    timerBegin(0, 80, true);            
    timerAttachInterrupt(0, onTimer, true); 
    timerAlarmWrite(0, 500000, true);    // Set timer alarm to trigger every 500ms 
    timerAlarmEnable(0);                
    Serial.println("Parking System Initialized.");
}

void loop() {
    // Read sensor data
    bool vehicleDetected = hardwareController.readVehiclePresence();
    bool buttonPressed = hardwareController.readButtonPress();
    bool vehicleExited = hardwareController.readVehicleExit();

    // Print sensor data for debugging
    Serial.print("Vehicle Detected: ");
    Serial.println(vehicleDetected ? "Yes" : "No");
    Serial.print("Button Pressed: ");
    Serial.println(buttonPressed ? "Yes" : "No");
    Serial.print("Vehicle Exited: ");
    Serial.println(vehicleExited ? "Yes" : "No");

    // Handle sensor data in the parking manager
    parkingManager.handleSensorData(vehicleDetected, buttonPressed, vehicleExited);

    // If the timer interrupt flag is set, toggle the orange LED
    if (timerFlag) {
        Serial.println("Timer Interrupt: Toggling Orange LED");
        parkingManager.toggleOrangeLED();  
        timerFlag = false;          
    }

    // Update LEDs and barrier based on parking logic
    parkingManager.updateLEDs();
    parkingManager.updateBarrier();

    // Print system status to console for debugging
    Serial.print("Red LED: ");
    Serial.println(parkingManager.isRedLightOn() ? "On" : "Off");
    Serial.print("Green LED: ");
    Serial.println(parkingManager.isGreenLightOn() ? "On" : "Off");
    Serial.print("Orange LED: ");
    Serial.println(parkingManager.isOrangeLightBlinking() ? "Blinking" : "Off");
    Serial.print("Barrier: ");
    Serial.println(parkingManager.isBarrierOpen() ? "Open" : "Closed");

    delay(100);  // Delay 
}
