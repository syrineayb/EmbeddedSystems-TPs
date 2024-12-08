#include <Arduino.h>
#include "LedConfig.h"

hw_timer_t *timer = NULL;
volatile bool ledState = false;

void IRAM_ATTR onTimer() {
    ledState = !ledState;
    digitalWrite(LED, ledState ? LED_ON : LED_OFF);
    Serial.println(ledState ? "LED Turned ON" : "LED Turned OFF");
}

void SystemConfig() {
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.println("LED Program Initialized");
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 1000000, true);//1Second    
    timerAlarmEnable(timer);
}

void InitApplication() {
    digitalWrite(LED, LED_OFF);  // LED OFF
    Serial.println("LED Set to OFF");
}

void setup() {
    SystemConfig();
    InitApplication();
}

void loop() {
}