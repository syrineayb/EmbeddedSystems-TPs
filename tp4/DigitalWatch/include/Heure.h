#ifndef HEURE_H
#define HEURE_H

#include <Arduino.h>

class Heure {
public:
    void razSeconds();
    void incMinutes();
    void incHeure();
    String toString();

private:
    int hours = 12;
    int minutes = 0;
    int seconds = 0;
};

#endif
