
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
void togglePinWithDelay(uint8_t pin, uint16_t delaymS, const char *name) {
    lnprintf("%stoggling pin: %s [%d]:\n", BLANK_4, pin, name);
    lnprintf("%sturning ON\n", BLANK_6);
    digitalWrite(pin, ON);
    delay(delaymS);
    lnprintf("%sturning OFF\n", BLANK_6);
    digitalWrite(pin, OFF);
}


// #########################################
// #
// #########################################
void togglePinWithDelay(out_pin_t *p, uint16_t delaymS) {
    lnprintf("%stoggling pin: %s [%d]:\n", BLANK_2, p->name, p->pin);
    lnprintf("%sturning ON\n", BLANK_4);
    digitalWrite(p->pin, p->ON);
    delay(delaymS);
    lnprintf("%sturning OFF\n", BLANK_4);
    digitalWrite(p->pin, p->OFF);
}

// #########################################
// #
// #########################################
void configOutPin(out_pin_t *p, uint8_t nr, bool on_level, const char *name) {
    p->name = name;
    p->pin = nr;
    p->ON = on_level;
    p->OFF = !on_level;
    digitalWrite(p->pin, p->OFF);
    pinMode(p->pin, p->mode);
}


// #########################################
// #
// #########################################
void configInputPin(input_pin_t *p, uint8_t nr, uint8_t mode, bool press_level, const char *name) {
    p->name = name;
    p->pin = nr;
    p->press_level = press_level;
    // p->OFF = !on_level;
    p->mode = mode;
    pinMode(p->pin, p->mode);
}

// #########################################
// #
// #########################################
void configBouncedPin(bounced_pin_t *p, uint8_t nr, uint8_t mode, bool press_level, const char *name) {
    p->name = name;
    p->pin = nr;
    p->press_level = press_level;
    p->mode = mode;
    pinMode(p->pin, p->mode);
}

// #########################################
// #
// #########################################
void writePin(out_pin_t *p, uint8_t level) {
    if (level == OFF) {
        level = p->OFF;
    } else {
        level = p->ON;
    }

    digitalWrite(p->pin, level);
    p->state = level;
    lnprintf("setting pin: %s [%d] -> %d:\n", p->name, p->pin, level);
}

// #########################################
// #
// #########################################
bool readPin(input_pin_t *p) {
    uint8_t level = digitalRead(p->pin);
    if (level == p->press_level) {
        level = LOW;
    } else {
        level = HIGH;
    }
    p->state = level;
    lnprintf("pin: %s [%d] has level %d:\n", p->name, p->pin, level);
    return level;
}



// #########################################
// #
// #########################################
bool check_pumpState_pin(uint8_t pin, uint16_t touchDelay) {
    static unsigned long last_touch;
    // uint16_t touchDelay = 300; // millis
    bool fdetected = false;

    uint8_t state = digitalRead(pin);
    if (state == ON) {
        if (millis() - last_touch > touchDelay) { // bounce
            fdetected = true;
        }
    }

    last_touch = millis();
    return fdetected;
}

// #########################################
// #
// #########################################
bool check_pressControlState_pin(uint8_t pin) {
    static unsigned long last_touch = 0;
    static bool fdetected = false;
    uint16_t touchDelay = 300; // millis
    unsigned long now=millis();

    if ( fdetected ) {
        /* alsready on */
    }
    else if ( (digitalRead(pin) == ON) && (last_touch == 0) ) {
        last_touch = now;
        fdetected = false;
        lnprintf("start last_touch: %lu %lu\n", now, last_touch);
    }
    else if (digitalRead(pin) == ON)  {
        lnprintf("cont last_touch: %lu %lu\n", now, last_touch);
        if (millis() - last_touch > touchDelay) { // bounce
            fdetected = true;
            lnprintf("detected\n");
        }

    }
    else {
        last_touch = 0;
    }

    return fdetected;
}




// ################################################################
// # b->pressed can be LOW or HIGH
// # so you can check for normally closed/opened button
// # return:
// #      0 no action:
// #      1 short press detected:
// #      2 long press detected:
// ################################################################

uint8_t readShortLongPress(bounced_pin_t *b, uint8_t buzzer_pin) {
    unsigned long now=millis();
    unsigned long elapsed;
    int state = digitalRead(b->pin);    // If the switch changed, due to noise or pressing:
    uint8_t press_time=0;

    // button changing state
    if (state != b->lastState) {
        b->lastState = state;
        if (state == b->press_level) {
            b->pressedMillis = now; // reset pressed millis
            b->long_notify=true;
            b->short_notify=true;
        }

        else {
            // button has been released, calculate elapsed time
            elapsed = now - b->pressedMillis;
            b->pressedMillis = now; // reset the pressed timer
            if (elapsed > b->longButtonPress) {
                press_time = LONG_PRESS;
                lnprintf("[LONG] - button released [%d] after %lu millis\n", state, elapsed);
            }
            else if (elapsed > b->shortButtonPress) {
                press_time = SHORT_PRESS;
                lnprintf("[SHORT] - button released [%d] after %lu millis\n", state, elapsed);
            }
        }
    }

    // -------------------------------------------------
    // serve solo per segnalare  short/long press button
    // -------------------------------------------------
    if ( (buzzer_pin) && (state == b->press_level) ) {
        elapsed = now - b->pressedMillis;
        if ( (elapsed > b->longButtonPress) && (b->long_notify) ){
            toggleBuzzer(buzzer_pin, 500);
            b->long_notify=false; // suona solo una volta
        }
        else if ( (elapsed > b->shortButtonPress) && (b->short_notify) ) {
            b->short_notify=false; // suona solo una volta
            toggleBuzzer(buzzer_pin, 100);
            b->short_notify=false; // suona solo una volta
        }
    }
    return press_time;
} // end function

