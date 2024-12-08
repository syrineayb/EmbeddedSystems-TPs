#include <Arduino.h>
#include "Montre.h"
#include "DigitalIO.h"

Montre montre;

void setup() {
    Serial.begin(115200);
    Serial.println("Montre Program Started");
    DigitalIO::initPins();
}

void loop() {
    montre.FsmMontre();

    delay(100);
}
