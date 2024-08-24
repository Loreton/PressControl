
//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"


uint8_t     BUZZER_pin = PASSIVE_BUZZER_pin;
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
    digitalWrite(BUZZER_pin, action);
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
            digitalWrite(BUZZER_pin, OFF);
            fBuzzerAlarm = false;
        }
    }
}


//##########################################################
//# Suona un passive buzzer
//##########################################################
void buzzerPumpOn() {
    lnprintf("%sincreasing buzzer tone on pin %d\n", BLANK_2, BUZZER_pin);
    int _duration=500;
    int _frequency=500;
    for (int i=1; i<=5; i++) {
        tone(BUZZER_pin, _frequency*i, _duration);
        delay(_duration*1.1);
    }
    noTone(BUZZER_pin);
    delay(500);
    digitalWrite(BUZZER_pin, OFF);
}

//##########################################################
//# Suona un passive buzzer
//##########################################################
void buzzerPumpOff() {
    lnprintf("%sdecreasing buzzer tone on pin %d\n", BLANK_2, BUZZER_pin);
    int _duration=500;
    int _frequency=500;
    for (int i=5; i>0; i--) {
        tone(BUZZER_pin, _frequency*i, _duration);
        delay(_duration*1.1);
    }
    noTone(BUZZER_pin);
    delay(500);
    digitalWrite(BUZZER_pin, OFF);
}


//##########################################################
//#  buzzer OFF
//##########################################################
void buzzerOff() {
    noTone(BUZZER_pin);
    digitalWrite(BUZZER_pin, OFF);
}

