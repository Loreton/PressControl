//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//

#include <Arduino.h>
#define _I_AM_PUMP_ALARM_CPP__

#include "main.h"


void setup() {
    Serial.begin(9600);
    pinMode(PUMP_STATE_PIN, INPUT_PULLUP);
    pinMode(TEST_ALARM_PIN, INPUT_PULLUP);

    // You can use digitalWrite(pin, HIGH) before use pinMode(pin, OUTPUT).
    // Per evitare problemi con risorse esterne al momento dell'accensione
    // conviene forzare l'output a livello desiderato prima di impostarlo come output
    digitalWrite(PRESSCONTROL_BUTTON_PIN, HIGH); pinMode(PRESSCONTROL_BUTTON_PIN , OUTPUT);
    digitalWrite(HORN_PIN, HIGH);                pinMode(HORN_PIN               , OUTPUT);
    digitalWrite(BUZZER_PIN, HIGH);              pinMode(BUZZER_PIN             , OUTPUT);
    digitalWrite(LED_PIN, HIGH);                 pinMode(LED_PIN        , OUTPUT);

    lnprint(true, "Starting...");
    lnprint(true, "PHASE_INTERVAL               : ", PHASE_INTERVAL);
    lnprint(true, "PHASE_ALARM_INTERVAL         : ", PHASE_ALARM_INTERVAL);
    lnprint(true, "PHASE_ALARM_THRESHOLD_NUMBER : ", PHASE_ALARM_THRESHOLD_NUMBER);
    lnprint(true, "PHASE_MIN_INTERVAL           : ", PHASE_MIN_INTERVAL);
    lnprint(true, "PHASE_STEP_DOWN              : ", PHASE_STEP_DOWN);
    // lnprint(true, "SKIP_PRINT_VALUE         : ", SKIP_PRINT_VALUE+1);
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
    fTestAlarm = !digitalRead(TEST_ALARM_PIN);  // logica inversa.
    if (fTestAlarm) {
        int _duration=500;
        int _frequency=500;
        for (int i=1;i<=5;i++) {
            tone(BUZZER_PIN, _frequency*i, _duration);
            delay(_duration*1.1);
        }
        for (int i=5;i>0;i--) {
            tone(BUZZER_PIN, _frequency*i, _duration);
            delay(_duration*1.1);
        }
        noTone(BUZZER_PIN);

        digitalWrite(HORN_PIN, HORN_ON); delay(4000); digitalWrite(HORN_PIN, HORN_OFF);
        delay(4000);
        digitalWrite(HORN_PIN, HORN_ON); delay(4000); digitalWrite(HORN_PIN, HORN_OFF);
        PressControl_Toggle(); // switch press control state
        delay(2000);
        PressControl_Toggle(); // reset press control state
        delay(2000);
        return;
    }
    now = millis();
    checkPumpState();
    checkLed();
    checkHorn();


    if (buzzer_ON) {
        unsigned long elapsed = now-phase_start_time;  // elapsed: duration
        if (elapsed>=buzzer_duration) { // se stiamo suonando, portiamolo a termine
            lnprint(true, "Beep OFF - elapsed: ", elapsed, " mS\n");
            noTone(BUZZER_PIN);
            buzzer_ON=false;
        }
    }


    if (fALARM)
        PressControl_Toggle();

} // end loop()
