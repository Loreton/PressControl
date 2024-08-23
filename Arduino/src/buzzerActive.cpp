
//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"



#if ACTIVE_BUZZER == true

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
//# Suona un active buzzer
//##########################################################
void buzzerPumpOn(uint8_t pin) {
    lnprintf("running buzzer on pin: %d\n", pin);

    for (int i=1; i<=5; i++) {
        uint16_t _delay=200;
        togglePinWithDelay(pin, _delay);
        delay(200);
    }
}

//##########################################################
//# Suona un active buzzer
//##########################################################
void buzzerPumpOff(uint8_t pin) {
    lnprintf("running buzzer on pin: %d\n", pin);
    for (int i=2; i>=1; i--) {
        uint16_t _delay=200;
        togglePinWithDelay(pin, _delay);
        delay(200);
    }
}


#endif

