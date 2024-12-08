#ifndef MONTRE_H
#define MONTRE_H

#include "afficheur.h"
#include "heure.h"
#include "Chronometre.h"

enum MontreStates {
    ModeAffichage,
    ModeChrono,
    ModeReglage,
};
enum LightStates {
    LightOn,
    LightOff,
};
enum ModeChronoStates {
    Started,
    Stopped,
};
enum ModeReglageStates {
    SecondSetting,
    MinuteSetting,
    HourSetting
};

class Montre {
private:
    bool flagAffichage = false;
    
public:
    MontreStates MontreState;
    LightStates LightState;
    ModeChronoStates ChronoState;
    ModeReglageStates ReglageState;
    Afficheur afficheur;
    Heure heure;
    Chronometre chrono;
    volatile bool flagTimerLight = false;
    hw_timer_t *timeUpdateTimer = NULL; 
    static Montre *instance;
    unsigned long lightStartMillis = 0; 

    bool IsMode();
    bool IsLight();
    bool IsStartStop();
    bool IsSet();

    void FsmMontre();
    void FsmModeChrono();
    void FsmModeLight();
    void FsmModeReglage();
    void FsmModeAffichage();
    
    void ActivateLight();
    void DeactivateLight();
    
    void StartTimerLight2s();
    void StopTimerLight2s();
    bool IsEndTimerLight2s();
    
    void ArmerTimerMajHeure1s();

    static void IRAM_ATTR timerISR();

    Montre(); 
};

#endif
