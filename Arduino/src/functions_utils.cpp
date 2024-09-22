
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




// #########################################
// #
// #########################################
bool bounce2(unsigned long last_touch, uint16_t touchDelay) {
    bool fdetected = false;
    if (millis() - last_touch > touchDelay) { // bounce
        fdetected = true;
    }
    return fdetected;
}

// #########################################
// #
// #########################################
// bool bounce(uint8_t pin, unsigned long last_touch, uint16_t touchDelay) {
//     bool fdetected = false;

//     uint8_t state = digitalRead(pin);
//     if (state == ON) {
//         if (millis() - last_touch > touchDelay) { // bounce
//             fdetected = true;
//         }
//     }
//     return fdetected;
// }

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

#if 0

// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long lastButtonState;

// #########################################
// #
// #########################################
bool bounce_pin(uint8_t buttonPin) {
    // read the state of the switch into a local variable:
    unsigned long now=millis();
    int reading = digitalRead(buttonPin);

    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) {
        lastDebounceTime = now; // reset the debouncing timer
    }

    if ((now - lastDebounceTime) > debounceDelay) {
        // if the button state has changed:
        if (reading != buttonState) {
            buttonState = reading;
        }

    }
    return buttonState;
}


void readShortLongPress() {
    const uint8_t BUTTON_PIN = 2;
    const unsigned long DEBOUNCE_DELAY = 50ul;
    const unsigned long LONG_PRESS_LIMIT = 400ul;

    // static variables are used to presere their data between function calls
    static bool pressed = false;
    static bool released = false;
    static unsigned long  pressedMillis = 0ul;

    // pull-up, reversed logic needed
    static uint8_t buttonState = HIGH;
    static uint8_t lastButtonState = HIGH;
    static unsigned long lastDebounceTime = 0ul;

    // gather current state
    int reading = digitalRead(BUTTON_PIN);
    unsigned long now = millis();

    if (reading != lastButtonState) {
        lastDebounceTime = now;
    }

    if ((now - lastDebounceTime) > DEBOUNCE_DELAY ) {
        if (reading != buttonState) {
            buttonState = reading;

            if (buttonState == LOW) {
                pressed = true;
                pressedMillis = now;
            }
            else {
                released = true;
            }
        }
    }

    // button was pressed, but not anymore
    if (pressed && released) {
        // compare current millis with the timestamp of the last press
        if ((now - pressedMillis) >= LONG_PRESS_LIMIT ) {
            longButtonPress = true;
        }
        else {
            shortButtonPress = true;
        }

        // flip them back
        pressed = false;
        released = false;
    }

    lastButtonState = reading;
}
#endif



// ################################################################
// # b->pressed can be LOW or HIGH
// # so you can check for normally closed/opened button
// # return:
// #      0 no action:
// #      1 short press detected:
// #      2 long press detected:
// ################################################################

uint8_t readShortLongPress(bounce_button_t *b, uint8_t buzzer_pin) {
    unsigned long now=millis();
    unsigned long elapsed;
    int state = digitalRead(b->pin);    // If the switch changed, due to noise or pressing:
    uint8_t retValue=0;

    // button changing state
    if (state != b->lastState) {
        b->lastState = state;
        if (state == b->pressed) {
            b->pressedMillis = now; // reset pressed millis
            b->long_notify=true;
            b->short_notify=true;
        }

        else {
            // button has been released, calculate elapsed time
            elapsed = now - b->pressedMillis;
            b->pressedMillis = now; // reset the pressed timer
            if (elapsed > b->longButtonPress) {
                retValue = 2;
                lnprintf("[LONG] - button released [%d] after %lu millis\n", state, elapsed);
            }
            else if (elapsed > b->shortButtonPress) {
                retValue = 1;
                lnprintf("[SHORT] - button released [%d] after %lu millis\n", state, elapsed);
            }
        }
    }

    // serve solo per segnalare limite short/long
    if ( (buzzer_pin) && (state == b->pressed) ) {
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
    return retValue;
} // end function

