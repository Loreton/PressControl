//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"


// ==================================
// - Comanda il pulsante del sOnOff il quale si attiva sul rilascio.
// - Il comando è intermediato da un relay.
// ==================================
void PressControl_Toggle() {
    lnprintf("toggling Press-Control button...\n");
    digitalWrite(PRESSCONTROL_BUTTON_PIN, LOW);
    lnprintf("Pushed...\n");
    delay(500);
    digitalWrite(PRESSCONTROL_BUTTON_PIN, HIGH);
    lnprintf("Released...\n");
}


void testAlarm() {
    lnprintf("TEST_ALARM_PIN started...\n");
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
    lnprintf("TEST_ALARM_PIN completed...\n");
    return;
}