#include <Arduino.h>
#include <config.h>  

int timerCount = MAX_TIMER_COUNT;  
hw_timer_t *timer = NULL;         

void IRAM_ATTR onTimerInterrupt();  
void SystemConfig();          
void InitApplication();      

void IRAM_ATTR onTimerInterrupt() {
  timerCount--; 
  if (timerCount == 0) {
    digitalWrite(LED_PIN, HIGH);  
    timerCount = MAX_TIMER_COUNT; 
  }
  else {
    digitalWrite(LED_PIN, LOW);  
  }
}
void SystemConfig() {
  pinMode(LED_PIN, OUTPUT);    
  digitalWrite(LED_PIN, LOW);  
  timerCount = MAX_TIMER_COUNT;  
  timer = timerBegin(0, 80, true); 
  timerAttachInterrupt(timer, &onTimerInterrupt, true);
  timerAlarmWrite(timer, TIMER_INTERVAL_US, true);  
  timerAlarmEnable(timer);  // activate timer
}

void InitApplication() {
  Serial.begin(115200);  
  Serial.println("Initializing...");  
}

void setup() {
  SystemConfig();  
  InitApplication();  
}

void loop() {
  Serial.print("LED State: ");
  Serial.println(digitalRead(LED_PIN));  // display LED state
  delay(500);  // 500ms
}
