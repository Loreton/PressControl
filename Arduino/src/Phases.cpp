//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"


// ==================================
// -
// ==================================
void setPhase(int phase_number) {

    phase_nr = phase_number;

    if (phase_nr==0) {
        noTone(PASSIVE_BUZZER_pin);
        // digitalWrite(PASSIVE_BUZZER_pin, OFF);
    }

    if (phase_nr > MAX_PHASES) {
        fALARM=true;
        pumpAlarm(ON);
    } else if ( (phase_nr*PHASE_STEP_DOWN) > PHASE_INTERVAL) { // controllo di salvaguardia
        phase_interval=PHASE_MIN_INTERVAL;
    } else {
        phase_interval = PHASE_INTERVAL - (phase_nr*PHASE_STEP_DOWN); // ogni phase diminuiamo l'intervallo
    }


    // - defaults....
    // buzzer_frequency = BUZZER_FREQUENCY;
    // led_duration     = LED_DURATION;
    // led_interval     = LED_INTERVAL;
    // buzzer_volume    = 9;

    if (fALARM) {
        lnprintf("siamo in Alarm \n");
        phase_nr = MAX_PHASES;
        phase_interval = PHASE_ALARM_INTERVAL;  // secondi
    } else if (fPUMP) {
        lnprintf("siamo con Pump == ON\n");
    }


    // buzzer_duration = (phase_nr+1)*1000;
    // if (buzzer_duration>phase_interval) buzzer_duration=phase_interval/3;

    phase_start_time = now;
    // printStatus();
}

