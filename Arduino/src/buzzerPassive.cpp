
//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"


#if ACTIVE_BUZZER == false
//##########################################################
//# Suona il buzzer tante volte quante il phase_number
//##########################################################
void buzzerAlarm(uint8_t pin, uint8_t phase_num) {
    lnprintf("BUZZER [pin: %d] PHASE ALARM phase: %d\n", pin, phase_num);
    for (uint8_t i = 0; i <= phase_num; ++i) {
        togglePinWithDelay(pin, 2000);
    }
}


//##########################################################
//# Suona un passive buzzer
//##########################################################
void buzzerPumpOn(uint8_t pin) {
    lnprintf("running buzzer on pin: %d\n", pin);
    int _duration=500;
    int _frequency=500;
    lnprintf("%sincrease buzzer tone\n", BLANK_2);
    for (int i=1;i<=5;i++) {
        tone(pin, _frequency*i, _duration);
        delay(_duration*1.1);

    }
    noTone(pin);
    digitalWrite(pin, OFF);
}

//##########################################################
//# Suona un passive buzzer
//##########################################################
void buzzerPumpOff(uint8_t pin) {
    lnprintf("running buzzer on pin: %d\n", pin);
    int _duration=500;
    int _frequency=500;
    lnprintf("%sdecrease buzzer tone\n", BLANK_2);
    for (int i=5;i>0;i--) {
        tone(pin, _frequency*i, _duration);
        delay(_duration*1.1);
    }
    noTone(pin);
    digitalWrite(pin, OFF);
}

#endif

