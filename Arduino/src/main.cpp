//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//

#include <Arduino.h>
#define _I_AM_PUMP_ALARM_CPP__

#include "main.h"







void setup() {
    Serial.begin(115200);
    delay(1000);
    pinMode(PUMP_STATE_PIN, INPUT_PULLUP);
    pinMode(TEST_ALARM_PIN, INPUT_PULLUP);

    // You can use digitalWrite(pin, HIGH) before use pinMode(pin, OUTPUT).
    // Per evitare problemi con risorse esterne al momento dell'accensione
    // conviene forzare l'output a livello desiderato prima di impostarlo come output
    digitalWrite(PRESSCONTROL_BUTTON_PIN, HIGH); pinMode(PRESSCONTROL_BUTTON_PIN, OUTPUT);
    digitalWrite(HORN_PIN,                HIGH); pinMode(HORN_PIN               , OUTPUT);
    digitalWrite(BUZZER_PIN,              HIGH); pinMode(BUZZER_PIN             , OUTPUT);
    digitalWrite(LED_PIN,                 HIGH); pinMode(LED_PIN                , OUTPUT);

    lnprintf("Starting...\n");
    lnprintf("PHASE_INTERVAL               : %d\n", PHASE_INTERVAL);
    lnprintf("PHASE_ALARM_INTERVAL         : %d\n", PHASE_ALARM_INTERVAL);
    lnprintf("PHASE_ALARM_THRESHOLD_NUMBER : %d\n", PHASE_ALARM_THRESHOLD_NUMBER);
    lnprintf("PHASE_MIN_INTERVAL           : %d\n", PHASE_MIN_INTERVAL);
    lnprintf("PHASE_STEP_DOWN              : %d\n", PHASE_STEP_DOWN);

    setPhase(0);
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
    fTestAlarm = digitalRead(TEST_ALARM_PIN);
    if (fTestAlarm == LOW) {
        testAlarm();
    }

    now = millis();
    checkPumpState();
    checkLed();
    checkHorn();


    if (buzzer_ON) {
        unsigned long elapsed = now-phase_start_time;  // elapsed: duration
        if (elapsed>=buzzer_duration) { // se stiamo suonando, portiamolo a termine
            lnprintf("Beep OFF - elapsed: %d mS\n", elapsed);
            noTone(BUZZER_PIN);
            buzzer_ON=false;
        }
    }


    if (fALARM)
        PressControl_Toggle();

} // end loop()
