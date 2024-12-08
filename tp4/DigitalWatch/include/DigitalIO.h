#ifndef DIGITALIO_H
#define DIGITALIO_H

#include <Arduino.h>

class DigitalIO {
public:
    static const int SET_BUTTON = 32;
    static const int STARTSTOP_BUTTON = 33;
    static const int LIGHT_BUTTON = 25;
    static const int MODE_BUTTON = 26;

    static const int LIGHT = 23;

    static const long QUARTER_SECOND = 250000;
    static const long HALF_SECOND = 500000;
    static const long ONE_SECOND = HALF_SECOND * 2;
    static const long TWO_SECOND = ONE_SECOND * 2;
    static const long TWO_MINUTE = ONE_SECOND * 60 * 2;

    static void initPins();

    static bool isSetButtonPressed();
    static bool isStartStopButtonPressed();
    static bool isLightButtonPressed();
    static bool isModeButtonPressed();

    // Light Control
    static void turnLightOn();
    static void turnLightOff();
    static void toggleLight();
};

#endif