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
    Serial.println("pushing PressControl button");
    digitalWrite(sonoff_emergency_pin, LOW);
    delay(1000);
    Serial.println("releasing PressControl button");
    digitalWrite(sonoff_emergency_pin, HIGH);
}
