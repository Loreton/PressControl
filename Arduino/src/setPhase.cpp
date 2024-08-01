//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"




// ==================================
// -
// ==================================
void setPhase(int count) {

    phase=count;

    if (phase==0) noTone(BUZZER_PIN);
    if (phase>PHASE_ALARM_THRESHOLD_NUMBER) {
        fALARM=true;
        phase=PHASE_ALARM_THRESHOLD_NUMBER;
    }


    // - defaults....
    buzzer_frequency = BUZZER_FREQUENCY;
    led_duration     = LED_DURATION;
    led_interval     = LED_INTERVAL;
    buzzer_volume    = 9;


    if ((phase*PHASE_STEP_DOWN) > PHASE_INTERVAL) // controllo di salvaguardia
        phase_interval=PHASE_MIN_INTERVAL;
    else
        phase_interval = PHASE_INTERVAL - (phase*PHASE_STEP_DOWN); // ogni phase diminuiamo l'intervallo

    lnprintf("phase_interval %d\n", phase_interval);
    if (fALARM) {
        lnprintf("siamo in Alarm \n");
        phase_interval = PHASE_ALARM_INTERVAL;  // secondi

        horn_interval = PHASE_ALARM_THRESHOLD_NUMBER*500;
        // horn_duration = PHASE_ALARM_THRESHOLD_NUMBER*1000*2; // suona per il 50% dell'intervllo
        horn_duration = horn_interval*4; // suona per il 80% del ciclo

        led_duration = LED_DURATION/6;
        led_interval = LED_INTERVAL/4;

        // Serial.println("Siamo in ALLARME!!!!");
    }

    else if (fPUMP) {
        lnprintf("Pump is ON\n");
        led_duration = LED_DURATION/4;
        led_interval = LED_INTERVAL/4;
        horn_interval = phase_interval;
        horn_duration = (phase+2)*1000;

    }


    buzzer_duration = (phase+1)*1000;
    if (buzzer_duration>phase_interval) buzzer_duration=phase_interval/3;

    phase_start_time = now;
    printStatus();
}


