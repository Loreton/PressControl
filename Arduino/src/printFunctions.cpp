//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"


// ==================================
// -
// ==================================
void printStatus() {
    lnprint(fPrint_BEEP, "\nnow: ", now, " - ");
    lnprint(fPrint_BEEP, "phase # : ", phase);
    if (fALARM) {
        lnprint(fPrint_BEEP, "      ALARM ON");
    }
    if (fPUMP) {
        lnprint(fPrint_BEEP, "      phase_interval  : ", phase_interval, " mSec\n");
        lnprint(fPrint_BEEP, "      buzzer_duration : ", buzzer_duration, " mSec\n");
        lnprint(fPrint_BEEP, "      buzzer_frequency: ", buzzer_frequency, " Hz\n");
        lnprint(fPrint_BEEP, "      horn_interval   : ", horn_interval, " mSec\n");
        lnprint(fPrint_BEEP, "      horn_duration   : ", horn_duration, " mSec\n\n");
    }

}

// ==================================
// -
// ==================================
void lnprint(bool fPrint, const char *msg, const unsigned long value, const char *s2) {
    if (fPrint) {
        Serial.print(msg);
        if (value!=SKIP_PRINT_VALUE) Serial.print(value);
        Serial.print(s2);
    }
}