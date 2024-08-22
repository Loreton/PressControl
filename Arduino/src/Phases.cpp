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
    // lnprintf( " PHASE_ALARM_INTERVAL (mS):    %ld\n", PHASE_ALARM_INTERVAL_l);
    // lnprintf( " PHASE_STEP_DOWN (mS):              %d\n", PHASE_STEP_DOWN_l);
    // lnprintf( " PHASE_ALARM_THRESHOLD_NUMBER:   %d\n", PHASE_ALARM_THRESHOLD_NUMBER);
    for (int i = 0; i < MAX_PHASES; ++i) {
        lnprintf(" PHASE[%d]                    %d seconds\n", i, PHASE[i]);
    }
}


//######################################################
//# Calculate phases length (seconds) reducing each
//# pahse by 10% baout
//######################################################
int initializePhases(void) {
    float step_down=91.0/100;
    lnprintf("----- Setup phase\n");
    /* ---- per convertire float string
            ref: https://forum.arduino.cc/t/float-double-and-other-any-type-with-sprintf/688692
        dtostrf( step_down, 4, 2, floatBuffer ); // dtostrf(float_value, min_width, decimal_digits, buffer)
        sprintf(floatBuffer, "%s", String(step_down, 5).c_str());
        sprintf(floatBuffer, "%d.%02d", (int)step_down, (int)(step_down * 100) % 100); quella che consuma meno memoria
    */

    sprintf(floatBuffer, "%d.%02d", (int)step_down, (int)(step_down * 100) % 100); // quella che consuma meno memoria
    lnprintf("step_down %s%%\n", floatBuffer);

    int ph_length=60; // vale per la prima fase
    int total=0;
    for (int ph=1; ph < MAX_PHASES; ph++) {
        lnprintf("  phase_%d_len: %d seconds\n", ph, ph_length);
        ph_length=ph_length*step_down;
        total+=ph_length;
        PHASE[ph] = total;
    }
    lnprintf("total seconds: %d\n", total);
    return total;
}





// ==================================
// -
// ==================================
uint8_t getPhase(uint8_t phase_nr, uint8_t pump_time) {

    if (pump_time > PHASE[phase_nr]) {
        phase_nr +=1;
    }

    return phase_nr;
}


// ==================================
// -
// ==================================
uint8_t getPhase_(uint8_t pump_time) {
    uint8_t phase_number = 0;

    X_lnprintf("pump_time: %d\n", pump_time);
    for (int i = 0; i<MAX_PHASES; i++) {
        X_lnprintf("[%d] - phase_time: %d - current_pump_time: %d \n", i, PHASE[i], pump_time);
        if (pump_time < PHASE[i]) {
            phase_number = i;
            break;
        }
    }

    // lnprintf("phase_number %d\n", phase_number);

    return phase_number;
}

// ==================================
// -
// ==================================
uint8_t getPhase__(uint8_t pump_time) {
    uint8_t phase_number = 0;

    X_lnprintf("pump_time: %d\n", pump_time);
    for (int i = MAX_PHASES; i > 0; i--) {
        X_lnprintf("[%d] - phase_time: %d - current_pump_time: %d \n", i, PHASE[i], pump_time);
        if (pump_time >= PHASE[i]) {
            phase_number = i;
            break;
        }
    }

    X_lnprintf("phase_number %d\n", phase_number);

    return phase_number;
}



#if 0
// ==================================
// -
// ==================================
void setPhase(int phase_number) {

    int phase = phase_number;

    if (phase==0) {
        noTone(PASSIVE_BUZZER_pin);
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

#endif
