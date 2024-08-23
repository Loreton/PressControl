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
    digitalWrite(PRESSCONTROL_BUTTON_pin, LOW);
    Serial.println("Pushing Press-Control switch...");
    delay(500);
    digitalWrite(PRESSCONTROL_BUTTON_pin, HIGH);
    Serial.println("... released Press-Control switch.");
}
