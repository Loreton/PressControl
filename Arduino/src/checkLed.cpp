//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"



// ==================================
// -
// ==================================
void checkLed() {
// bool isLedTime;
static byte ledState;
static unsigned long LED_LastChangeTime;
unsigned long elapsed;

    // mai comparare due tempi
    // while (millis() < start + ms) ;  // BUGGY version
    // and
    // while (millis() - start < ms) ;  // CORRECT version

    elapsed = now-LED_LastChangeTime;
    switch(ledState) {
        case ON:
            // if the LED is on, we must wait for the duration to expire before turning it off
            if (elapsed >= led_duration) {
                // change the state to LOW
                ledState = OFF;
                digitalWrite(LED_pin, ledState);
                // and save the time when we made the change
                LED_LastChangeTime += led_duration;
                // NOTE: The previous line could alternatively be
                //              LED_LastChangeTime = now
                //        which is the style used in the BlinkWithoutDelay example sketch
                //        Adding on the interval is a better way to ensure that succesive periods are identical
            }
            break;

        default:
            // if the LED is off, we must wait for the interval to expire before turning it on
            if (elapsed >= led_interval) {
                // change the state to HIGH
                ledState = ON;
                digitalWrite(LED_pin, ledState);
                // and save the time when we made the change
                LED_LastChangeTime += led_interval;
            }
            break;
    } // end switch

}
