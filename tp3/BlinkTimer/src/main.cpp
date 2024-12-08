#include <Arduino.h>
#include "config.h"  
#include "chenillard.h" 

hw_timer_t *cycle_timer = NULL;  
hw_timer_t *blink_timer = NULL;   
portMUX_TYPE cycleTimerMux = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE blinkTimerMux = portMUX_INITIALIZER_UNLOCKED;

ChenillardStates chenillardState = CycleA;  
LedStates ledState = LedOff;                

volatile bool blinkFlag = false;
volatile bool cycleFlag = false;

void SystemConfig();
void TimerConfig();
void DigitalIoConfig();
void ApplicationConfig();
void FsmChenillard();
void FsmBlink();

void IRAM_ATTR OnCycleEnd() {
  portENTER_CRITICAL(&cycleTimerMux);
  cycleFlag = true;  
  portEXIT_CRITICAL(&cycleTimerMux);
}

void IRAM_ATTR OnBlinkEnd() {
  portENTER_CRITICAL(&blinkTimerMux);
  blinkFlag = true;  
  portEXIT_CRITICAL(&blinkTimerMux);
}

void setup() {
  SystemConfig(); 
  ApplicationConfig();  
}

void loop() {
  FsmChenillard();  
  FsmBlink(); 
  delay(5); 
}

void SystemConfig() {
  Serial.begin(115200);  
  TimerConfig();  
  DigitalIoConfig();  
}

void TimerConfig() {
  cycle_timer = timerBegin(0, 80, true);  
  timerAttachInterrupt(cycle_timer, &OnCycleEnd, true); 
  timerAlarmWrite(cycle_timer, THIRTY_SECOND, true);  
  timerAlarmEnable(cycle_timer);  

  blink_timer = timerBegin(1, 80, true);  
  timerAttachInterrupt(blink_timer, &OnBlinkEnd, true); 
  timerAlarmWrite(blink_timer, ONE_HZ, true); 
  timerAlarmEnable(blink_timer);  
}

void DigitalIoConfig() {
  pinMode(LED_PIN, OUTPUT); 
}

void ApplicationConfig() {
  Serial.println("Initializing Application...");
  digitalWrite(LED_PIN, LED_OFF);  
  Serial.println("End of Init.");
}

void FsmChenillard() {
  switch (chenillardState) {
    case CycleA:
      if (cycleFlag) {
        cycleFlag = false;  
        chenillardState = CycleB;  
        timerAlarmDisable(blink_timer);  // Disable the previous blink timer
        timerAlarmWrite(blink_timer, TEN_HZ, true);  // Set blink frequency to 10 Hz
        timerAlarmEnable(blink_timer);  // Enable the blink timer
        Serial.println("Cycle B");
      }
      break;
    case CycleB:
      if (cycleFlag) {
        cycleFlag = false;
        chenillardState = CycleC;
        timerAlarmDisable(blink_timer);
        timerAlarmWrite(blink_timer, FIFTY_HZ, true);  // Set blink frequency to 50 Hz
        timerAlarmEnable(blink_timer);
        Serial.println("Cycle C");
      }
      break;
    case CycleC:
      if (cycleFlag) {
        cycleFlag = false;
        chenillardState = CycleA;
        timerAlarmDisable(blink_timer);
        timerAlarmWrite(blink_timer, ONE_HZ, true);  // Set blink frequency back to 1 Hz
        timerAlarmEnable(blink_timer);
        Serial.println("Cycle A");
      }
      break;
  }
}

void FsmBlink() {
  switch (ledState) {
    case LedOn:
      if (blinkFlag) {
        blinkFlag = false;
        digitalWrite(LED_PIN, LED_OFF);  
        ledState = LedOff; 
        Serial.println("LED Off");
      }
      break;
    case LedOff:
      if (blinkFlag) {
        blinkFlag = false;
        digitalWrite(LED_PIN, LED_ON); 
        ledState = LedOn; 
        Serial.println("LED On");
      }
      break;
  }
}
