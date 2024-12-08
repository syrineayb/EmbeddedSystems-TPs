#ifndef HARDWARECONTROLLER_H
#define HARDWARECONTROLLER_H

class HardwareController { //   S’occupe des interactions avec les LEDs et la barrière
public:
    HardwareController();
    
    bool readVehiclePresence();
    bool readButtonPress();
    bool readVehicleExit();
    
    void setLEDState(int ledPin, bool state);
    void controlBarrier(bool state);
};

#endif
