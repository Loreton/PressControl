//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"



void displayValues(void) {
    lnprintf( " MAX_PHASES:                     %d\n", MAX_PHASES);
    // lnprintf( " PHASE_INTERVAL (mS):       %ld\n", PHASE_INTERVAL_l);
    // lnprintf( " PHASE_MIN_INTERVAL (mS):      %d\n", PHASE_MIN_INTERVAL);
    // lnprintf( " PHASE_LENGTH:                   %d\n", PHASE_LENGTH_l);
    lnprintf( " PHASE_ALARM_INTERVAL (mS):    %ld\n", PHASE_ALARM_INTERVAL_l);
    // lnprintf( " PHASE_STEP_DOWN (mS):              %d\n", PHASE_STEP_DOWN_l);
    // lnprintf( " PHASE_ALARM_THRESHOLD_NUMBER:   %d\n", PHASE_ALARM_THRESHOLD_NUMBER);
    for (int i = 0; i < MAX_PHASES; ++i) {
        lnprintf(" PHASE[%d]                    %d seconds\n", i, PHASE[i]);
    }
}


// ==================================
// -
// ==================================
uint8_t getPhase(void) {
    // uint phase_numbers = (MAX_PUMP_TIME/PHASE_LENGTH);
    uint8_t phase_number = 0;

    for (int i = MAX_PHASES; i > 0; i--) {
        lnprintf("[%d] - phase_time: %ld - current_pump_time: %ld \n", i, PHASE[i], current_pump_time);
        if (current_pump_time >= PHASE[i]) {
            phase_number = i;
            break;
        }
    }

    // Phases_t Phases;
    // switch (current_pump_time) {

    //     case 0 ... PHASE_1:
    //         phase_number = 0;
    //         break;

    //     case  PHASE_1+1 ... PHASE_2:
    //         phase_number = 1;
    //         break;

    //     case  PHASE_2+1 ... PHASE_3:
    //         phase_number = 2;
    //         break;

    //     case  PHASE_3+1 ... PHASE_4:
    //         phase_number = 3;
    //         break;

    //     case  PHASE_4+1 ... PHASE_5:
    //         phase_number = 4;
    //         break;

    //     default:
    //         phase_number = 5;
    //         break;
    // }

    lnprintf("phase_number %d\n", phase_number);

    return phase_number;
}

// ==================================
// -
// ==================================
void setPhase(int phase_number) {

    int phase = phase_number;

    if (phase==0) {
        noTone(BUZZER_pin);
    }

    if (phase > PHASE_ALARM_THRESHOLD_NUMBER) {
        fALARM=true;
        phase = PHASE_ALARM_THRESHOLD_NUMBER;
    }


    // - defaults....
    buzzer_frequency = BUZZER_FREQUENCY;
    led_duration     = LED_DURATION;
    led_interval     = LED_INTERVAL;
    buzzer_volume    = 9;


    if ( (phase*PHASE_STEP_DOWN_l) > PHASE_INTERVAL_l) // controllo di salvaguardia
        phase_interval=PHASE_MIN_INTERVAL;
    else
        phase_interval = PHASE_INTERVAL_l - (phase*PHASE_STEP_DOWN_l); // ogni phase diminuiamo l'intervallo

    lnprintf("phase_interval %d\n", phase_interval);
    if (fALARM) {
        lnprintf("siamo in Alarm \n");
        phase_interval = PHASE_ALARM_INTERVAL_l;  // secondi

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


