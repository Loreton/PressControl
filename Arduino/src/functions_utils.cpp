
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
void pushPin(uint8_t pin, uint16_t delaymS) {
    lnprintf("toggling pin: %d:\n", pin);
    lnprintf("    pushing\n");
    digitalWrite(pin, ON);
    delay(delaymS);
    lnprintf("    releasing\n");
    digitalWrite(pin, OFF);
}


// ==================================
// - Comanda il pulsante del sOnOff il quale si attiva sul rilascio.
// - Il comando è intermediato da un relay.
// ==================================
void PressControl_Toggle() {
    lnprintf("toggling Press-Control button...\n");
    digitalWrite(PRESSCONTROL_BUTTON_pin, ON);
    lnprintf("Pushed...\n");
    delay(500);
    digitalWrite(PRESSCONTROL_BUTTON_pin, OFF);
    lnprintf("Released...\n");
}


void testAlarm() {
    lnprintf("TEST_ALARM_PIN started...\n");
    int _duration=500;
    int _frequency=500;
    for (int i=1;i<=5;i++) {
        tone(BUZZER_pin, _frequency*i, _duration);
        delay(_duration*1.1);

    }
    for (int i=5;i>0;i--) {
        tone(BUZZER_pin, _frequency*i, _duration);
        delay(_duration*1.1);
    }
    noTone(BUZZER_pin);

    digitalWrite(HORN_pin, HORN_ON); delay(4000); digitalWrite(HORN_pin, HORN_OFF);
    delay(4000);
    digitalWrite(HORN_pin, HORN_ON); delay(4000); digitalWrite(HORN_pin, HORN_OFF);
    pushPin(PRESSCONTROL_BUTTON_pin, 500); // switch press control state
    delay(2000);
    pushPin(PRESSCONTROL_BUTTON_pin, 500); // switch press control state
    delay(2000);
    lnprintf("TEST_ALARM_PIN completed...\n");
    return;
}