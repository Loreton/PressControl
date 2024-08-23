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
        digitalWrite(PASSIVE_BUZZER_pin, OFF);
    }

    if (phase_nr > PHASE_ALARM_THRESHOLD_NUMBER) {
        fALARM=true;
        phase_nr = PHASE_ALARM_THRESHOLD_NUMBER;
    }


    // - defaults....
    buzzer_frequency = BUZZER_FREQUENCY;
    led_duration     = LED_DURATION;
    led_interval     = LED_INTERVAL;
    buzzer_volume    = 9;


    if ( (phase_nr*PHASE_STEP_DOWN) > PHASE_INTERVAL) // controllo di salvaguardia
        phase_interval=PHASE_MIN_INTERVAL;
    else
        phase_interval = PHASE_INTERVAL - (phase_nr*PHASE_STEP_DOWN); // ogni phase diminuiamo l'intervallo


    if (fALARM) {
        lnprintf("siamo in Alarm \n");
        phase_interval = PHASE_ALARM_INTERVAL;  // secondi

        horn_interval = PHASE_ALARM_THRESHOLD_NUMBER*500;
        horn_duration = horn_interval*4; // suona per il 80% del ciclo

        led_duration = LED_DURATION/6;
        led_interval = LED_INTERVAL/4;
    }

    else if (fPUMP) {
        lnprintf("siamo con Pump == ON\n");
        led_duration = LED_DURATION/4;
        led_interval = LED_INTERVAL/4;
        horn_interval = phase_interval;
        horn_duration = (phase_nr+2)*1000;

    }


    buzzer_duration = (phase_nr+1)*1000;
    if (buzzer_duration>phase_interval) buzzer_duration=phase_interval/3;

    phase_start_time = now;
    printStatus();
}

