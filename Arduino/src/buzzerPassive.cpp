
//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"
#define BUZZER_FREQ 400

uint32_t    alarm_time_duration = 0;
uint32_t    alarm_start_time = 0;
bool        fBuzzerAlarm = false;


//##########################################################
//# toneBuzzer
//##########################################################
void pumpAlarm(uint8_t action) {
    alarm_start_time = now;
    alarm_time_duration = phase_nr * 2000;
    lnprintf("start alarm time Buzzer - duration: %ld mS\n", alarm_time_duration);
    if (action == ON) {
        digitalWrite(activeBuzzer_pin, BUZZ_ON);
    } else {
        digitalWrite(activeBuzzer_pin, BUZZ_OFF);
    }
    fBuzzerAlarm = true;
}

//##########################################################
//# toneBuzzer
//##########################################################
void pumpAlarmCheck() {
    if (fBuzzerAlarm) {
        unsigned long alarm_elapsed = now-alarm_start_time;  // elapsed: duration
        if (alarm_elapsed >= alarm_time_duration) { // se stiamo suonando, portiamolo a termine
            lnprintf("stop alarm time Buzzer - elapsed: %ld mS\n", alarm_elapsed);
            digitalWrite(activeBuzzer_pin, BUZZ_OFF);
            fBuzzerAlarm = false;
        }
    }
}


//##########################################################
//# Suona un passive buzzer
//##########################################################
void buzzerPumpOn() {
    lnprintf("%sincreasing buzzer tone on pin %d\n", BLANK_2, passiveBuzzer_pin);
    int _duration=500;
    int _frequency=BUZZER_FREQ;
    for (int i=1; i<=5; i++) {
        tone(passiveBuzzer_pin, _frequency*i, _duration);
        delay(_duration*1.1);
    }
    noTone(passiveBuzzer_pin);
    // delay(500);
    // digitalWrite(passiveBuzzer_pin, OFF);
}

//##########################################################
//# Suona un passive buzzer
//##########################################################
void buzzerPumpOff() {
    lnprintf("%sdecreasing buzzer tone on pin %d\n", BLANK_2, passiveBuzzer_pin);
    int _duration=500;
    int _frequency=BUZZER_FREQ;
    for (int i=5; i>0; i--) {
        tone(passiveBuzzer_pin, _frequency*i, _duration);
        delay(_duration*1.1);
    }
    noTone(passiveBuzzer_pin);
    // delay(500);
    // digitalWrite(passiveBuzzer_pin, OFF);
}


//##########################################################
//#  buzzer OFF
//##########################################################
void buzzerOff() {
    noTone(passiveBuzzer_pin);
    digitalWrite(activeBuzzer_pin, BUZZ_OFF);
}

