
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





void readShortLongPress(bounce_button_t *button) {
    unsigned long now=millis();

    int state = digitalRead(button->pin);    // If the switch changed, due to noise or pressing:
    x_lnprintf("processing button on pin: %d name: %s state: %d\n", button->pin, button->name, state);

    if (state != button->lastState) {
        button->lastDebounceTime = now; // reset the debouncing timer
        lnprintf("changed state\n");
    }


    if ((now - button->lastDebounceTime) > button->debounceDelay ) {
        lnprintf("debounceDelay reached\n");
        if (state != button->currState) {
            lnprintf("updating state\n");
            button->currState = state;

            if (button->currState == button->pressed) {
                button->pressed = true;
                button->pressedMillis = now;
            }
            else {
                button->released = true;
            }
        }
    }


    #if 0
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
    #endif



    x_lnprintf("state: current %d last: %d\n\n", button->currState, button->lastState);
}