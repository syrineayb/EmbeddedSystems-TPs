#ifndef CHRONOMETRE_H
#define CHRONOMETRE_H

#include <Arduino.h>

class Chronometre {
public:
    void raz();
    bool start();
    bool stop();
    String toString();

private:
    unsigned long startTime = 0;
    unsigned long elapsedTime = 0;
    bool running = false;
};

#endif
