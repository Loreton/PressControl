//
// updated by ...: Loreto Notarantonio
// Date .........: 22-08-2024 11.20.08
//

#include <Arduino.h>

#define _I_AM_MAIN_CPP__
#include "main.h"






//######################################################
//#
//######################################################
void setup() {
    Serial.begin(115200);
    delay(1000);

    /* ------ setup PINs
        You can use digitalWrite(pin, HIGH) before use pinMode(pin, OUTPUT)
        per evitare problemi con risorse esterne al momento dell'accensione
        conviene forzare l'output a livello desiderato prima di impostarlo come output
    */
    pinMode(PUMP_STATE_pin,         INPUT_PULLUP);
    pinMode(TEST_ALARM_pin,         INPUT_PULLUP);
    pinMode(PRESSCONTROL_STATE_pin, INPUT_PULLUP);

    digitalWrite(PRESSCONTROL_BUTTON_pin, OFF); pinMode(PRESSCONTROL_BUTTON_pin, OUTPUT);
    digitalWrite(LED_pin,                 OFF); pinMode(LED_pin                , OUTPUT);
    digitalWrite(PASSIVE_BUZZER_pin,      OFF); pinMode(PASSIVE_BUZZER_pin     , OUTPUT);
    digitalWrite(ACTIVE_BUZZER_pin,       OFF); pinMode(ACTIVE_BUZZER_pin      , OUTPUT);
    digitalWrite(HORN_pin,           HORN_OFF); pinMode(HORN_pin               , OUTPUT);

    // displayValues();
    lnprintf("Starting...\n");
}



// ==================================
// - per gestire l'overflow di millis()
// - bisogna operare come segue:
//      if all your time calculations are done as:
//      if  ((later_time - earlier_time ) >=duration ) {action}
//      then the rollover does generally not come into play.
//      For ease of understanding think in bytes ( 0.. 255 ), instead of unsigned longs.
//     Example: If your old time was at 250 and now you're at 5,
//          you calculate (5 - 250) and interpret the result as an unsigned byte, the result is 11.
//          then the rollover does generally not come into play.
// - vedi anche: https://arduino.stackexchange.com/questions/12587/how-can-i-handle-the-millis-rollover
// ==================================
void loop() {
    static unsigned long last_second=0;
    static unsigned long elapsed;
    unsigned long seconds;
    now = millis();

    while (digitalRead(TEST_ALARM_pin) == ON) {
        lnprintf("TEST_ALARM [pin: %d] detected\n", TEST_ALARM_pin);
        testAlarm();
    }


    // --- controllo pompa
    if (digitalRead(PUMP_STATE_pin) == ON) { // logica inversa. PumpON->LowLevel

        fPUMP = true;
        if (phase_nr==0) {
            lnprintf("Pump status: ON\n");
            buzzerPumpOn();
            setPhase(1);
        }

        elapsed = now-phase_start_time;
        if (elapsed >= phase_interval)  {
            setPhase(phase_nr+1);
            pumpAlarm(ON);
        }
    }
    else {
        fALARM = false; // allarme rientrato
        fPUMP = false;
        if (phase_nr>0) {
            lnprintf("Pump status: OFF\n");
            buzzerOff();
            setPhase(0);
            buzzerPumpOff();
            pumpAlarm(OFF);
        }
    }

    pumpAlarmCheck(); // nel caso fosse attivo il buzzer di alarm
    // checkLed();
    // checkHorn();

    seconds = now/1000;
    x_lnprintf("now: %ld - seconds: %ld - last_second: %ld\n", now, seconds, last_second);
    if (seconds > last_second) {
        last_second = seconds;
        if (fPUMP) {
            lnprintf("phase_nr: %d - phase_interval: %ld - phase_start_time: %ld - elapsed: %ld\n", phase_nr, phase_interval, phase_start_time, now-phase_start_time);
            lnprintf("phase_nr: %d - phase_interval: %ld - phase_start_time: %ld - remaining: %ld\n", phase_nr, phase_interval, phase_start_time, now-phase_start_time);
        } else {
            lnprintf("elapsed seconds: %ld\n", seconds);
        }
    }



    // --- forse non posso farlo altrimenti accendo e spengo,
    //    però la prima volta dovrebbe spegnere il pressControl e l'allarme dovrebbe rientrare
    //    da verificare
    if (fALARM) PressControl_Toggle();


}



