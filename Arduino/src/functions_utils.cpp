
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
void togglePinWithDelay(uint8_t pin, uint16_t delaymS) {
    lnprintf("%stoggling pin: %d:\n", BLANK_4, pin);
    lnprintf("%sturning ON\n", BLANK_6);
    digitalWrite(pin, ON);
    delay(delaymS);
    lnprintf("%sturning OFF\n", BLANK_6);
    digitalWrite(pin, OFF);
}


// ==================================
// - Comanda il pulsante del sOnOff il quale si attiva sul rilascio.
// - Il comando è intermediato da un relay.
// ==================================
void PressControl_Toggle() {
    lnprintf("  toggling Press-Control button\n");
    digitalWrite(PRESSCONTROL_BUTTON_pin, ON);
    lnprintf("      Pushed\n");
    delay(500);
    digitalWrite(PRESSCONTROL_BUTTON_pin, OFF);
    lnprintf("      Released\n");
}


void testAlarm() {
    lnprintf("TEST_ALARM_PIN detected\n");
    int _duration=500;
    int _frequency=500;
    lnprintf("%srunning buzzer\n", BLANK_2);
    lnprintf("%sincrease buzzer tone\n", BLANK_2);
    for (int i=1;i<=5;i++) {
        tone(BUZZER_pin, _frequency*i, _duration);
        delay(_duration*1.1);

    }
    lnprintf("%sdecrease buzzer tone\n", BLANK_2);
    for (int i=5;i>0;i--) {
        tone(BUZZER_pin, _frequency*i, _duration);
        delay(_duration*1.1);
    }
    noTone(BUZZER_pin);

    lnprintf("%sturning Horn ON\n", BLANK_2);
    togglePinWithDelay(HORN_pin, 4000);
    delay(2000);
    lnprintf("%sturning PressControl ON\n", BLANK_2);
    togglePinWithDelay(PRESSCONTROL_BUTTON_pin, 500); // switch press control state
    delay(2000);
    lnprintf("%sturning PressControl OFF\n", BLANK_2);
    togglePinWithDelay(PRESSCONTROL_BUTTON_pin, 500); // switch press control state
    delay(2000);
    lnprintf("TEST_ALARM_PIN completed\n");
    return;
}