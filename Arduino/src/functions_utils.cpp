
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

