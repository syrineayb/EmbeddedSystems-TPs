#ifndef VEHICLEPARKINGLOGIC_H
#define VEHICLEPARKINGLOGIC_H

class VehicleParkingLogic { // Logique FSM
public:
    enum State {
        VEHICLE_ABSENT,
        VEHICLE_PRESENT,
        BUTTON_PRESSED,
        VEHICLE_EXITED,
        INACTIVE
    };

    VehicleParkingLogic();

    void updateState(bool vehicleDetected, bool buttonPressed, bool vehicleExited, unsigned long currentTime);
    void toggleOrangeLED();

    bool isRedLightOn() const;
    bool isOrangeLightBlinking() const;
    bool isGreenLightOn() const;
    bool isBarrierOpen() const;

private:
    State currentState;
    unsigned long lastActionTime;
    bool orangeLEDState;
    bool greenLightState;
    bool redLightState;
    bool barrierState;
    unsigned long orangeLEDLastChangeTime;
    static const int ORANGE_BLINK_FREQ = 1000; // 1 second blink 
};

#endif
