#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h> // the LCD library

class Afficheur {
public:
    enum DisplayState {
        SHOW_TIME,
        SHOW_TIME_SETTING,
        SHOW_STOPWATCH,
        SHOW_BLINK_HOUR,
        SHOW_BLINK_MINUTES,
        SHOW_BLINK_SECONDS
    };

    Afficheur();
    void update(DisplayState state, String message);

private:
    LiquidCrystal_I2C lcd; // LCD instance
    void displayTime(String message);
    void displayTimeSetting(String message);
    void displayStopwatch(String message);
    void blinkHour(String message);
    void blinkMinutes(String message);
    void blinkSeconds(String message);
};

#endif
