#include "Montre.h"
#include "DigitalIO.h"

Montre* Montre::instance = nullptr;

Montre::Montre() {
    MontreState = ModeAffichage;
    LightState = LightOff;
    ChronoState = Stopped;
    ReglageState = HourSetting;
    instance = this;  // Set the instance to the current object
    timeUpdateTimer = timerBegin(0, 80, true);
    timerAttachInterrupt(timeUpdateTimer, &Montre::timerISR, true);
}


void IRAM_ATTR Montre::timerISR() {
    if (instance != nullptr) {
        if (instance->flagTimerLight) {
            if (instance->IsEndTimerLight2s()) {
                instance->DeactivateLight();
            }
        }
    }
}

void Montre::FsmMontre() {
    switch (MontreState) {
        case ModeAffichage:
            FsmModeAffichage();
            break;
        case ModeChrono:
            FsmModeChrono();
            break;
        case ModeReglage:
            FsmModeReglage();
            break;
    }
}

void Montre::FsmModeAffichage() {
    if (IsMode()) {
        MontreState = ModeReglage;
        flagAffichage = false;
    }
    if (!flagAffichage) {
        afficheur.update(Afficheur::SHOW_TIME, heure.toString());
        flagAffichage = true;
    }
}

void Montre::FsmModeChrono() {
    if (IsStartStop()) {
        if (ChronoState == Stopped) {
            chrono.start();
            ChronoState = Started;
        } else {
            chrono.stop();
            ChronoState = Stopped;
        }
    }
    if (ChronoState == Started) {
        afficheur.update(Afficheur::SHOW_STOPWATCH, chrono.toString());
    }
}

void Montre::FsmModeLight() {
    if (IsLight()) {
        if (LightState == LightOff) {
            ActivateLight();
        } else {
            DeactivateLight();
        }
    }
    if (flagTimerLight) {
        if (IsEndTimerLight2s()) {
            DeactivateLight();
        }
    }
}

void Montre::FsmModeReglage() {
    if (IsSet()) {
        switch (ReglageState) {
            case HourSetting:
                heure.incHeure();
                ReglageState = MinuteSetting;
                break;
            case MinuteSetting:
                heure.incMinutes();
                ReglageState = SecondSetting;
                break;
            case SecondSetting:
                heure.razSeconds();
                ReglageState = HourSetting;
                break;
        }
    }
    switch (ReglageState) {
        case HourSetting:
            afficheur.update(Afficheur::SHOW_BLINK_HOUR, heure.toString());
            break;
        case MinuteSetting:
            afficheur.update(Afficheur::SHOW_BLINK_MINUTES, heure.toString());
            break;
        case SecondSetting:
            afficheur.update(Afficheur::SHOW_BLINK_SECONDS, heure.toString());
            break;
    }
}

void Montre::ActivateLight() {
    DigitalIO::turnLightOn();
    LightState = LightOn;
    lightStartMillis = millis(); 
    StartTimerLight2s();
}


void Montre::DeactivateLight() {
    DigitalIO::turnLightOff();
    LightState = LightOff;
    StopTimerLight2s();
}

void Montre::StartTimerLight2s() {
    flagTimerLight = true;
    timerAlarmWrite(timeUpdateTimer, 2000000, false);
    timerAlarmEnable(timeUpdateTimer);
}

void Montre::StopTimerLight2s() {
    flagTimerLight = false;
    timerAlarmDisable(timeUpdateTimer);
}

bool Montre::IsEndTimerLight2s() {
    return (millis() - lightStartMillis >= 2000);
}

void Montre::ArmerTimerMajHeure1s() {
    timerAlarmWrite(timeUpdateTimer, 1000000, true);
    timerAlarmEnable(timeUpdateTimer);
}

bool Montre::IsMode() {
    return DigitalIO::isModeButtonPressed();
}

bool Montre::IsLight() {
    return DigitalIO::isLightButtonPressed();
}

bool Montre::IsStartStop() {
    return DigitalIO::isStartStopButtonPressed();
}

bool Montre::IsSet() {
    return DigitalIO::isSetButtonPressed();
}
