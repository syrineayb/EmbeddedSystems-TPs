#include "Afficheur.h"

Afficheur::Afficheur() : lcd(0x27, 16, 2) { 
    lcd.init();      
    lcd.backlight();  
    lcd.clear();       
    lcd.setCursor(0, 0);
    lcd.print("LCD Ready!"); 
}


void Afficheur::update(DisplayState state, String message) {
    lcd.clear();
    switch (state) {
        case SHOW_TIME:
            displayTime(message);
            break;
        case SHOW_TIME_SETTING:
            displayTimeSetting(message);
            break;
        case SHOW_STOPWATCH:
            displayStopwatch(message);
            break;
        case SHOW_BLINK_HOUR:
            blinkHour(message);
            break;
        case SHOW_BLINK_MINUTES:
            blinkMinutes(message);
            break;
        case SHOW_BLINK_SECONDS:
            blinkSeconds(message);
            break;
    }
}

void Afficheur::displayTime(String message) {
    lcd.setCursor(0, 0);
    lcd.print("Time:");
    lcd.setCursor(0, 1); 
    lcd.print(message); 
}

void Afficheur::displayTimeSetting(String message) {
    lcd.setCursor(0, 0);
    lcd.print("Set Time:");
    lcd.setCursor(0, 1);
    lcd.print(message);
}

void Afficheur::displayStopwatch(String message) {
    lcd.setCursor(0, 0);
    lcd.print("Stopwatch:");
    lcd.setCursor(0, 1);
    lcd.print(message);
}

void Afficheur::blinkHour(String message) {
    lcd.setCursor(0, 0);
    lcd.print("Blink Hour:");
    lcd.setCursor(0, 1);
    lcd.print(message);
}

void Afficheur::blinkMinutes(String message) {
    lcd.setCursor(0, 0);
    lcd.print("Blink Min:");
    lcd.setCursor(0, 1);
    lcd.print(message);
}

void Afficheur::blinkSeconds(String message) {
    lcd.setCursor(0, 0);
    lcd.print("Blink Sec:");
    lcd.setCursor(0, 1);
    lcd.print(message);
}
