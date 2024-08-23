//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"



// ==================================
// - Suona la sirena con tempi
// - horn_duration: ON
// - horn_inerval: OFF
// ==================================
void checkHorn() {
static unsigned long HORN_lastChangeTime;
byte hornState;
unsigned long elapsed;

    hornState=digitalRead(HORN_pin);
    elapsed = now-HORN_lastChangeTime;
    if (fPUMP) {
        switch(hornState) {
            case HORN_ON:
                if (elapsed >= horn_duration) {
                    digitalWrite(HORN_pin, HORN_OFF);
                    HORN_lastChangeTime += horn_duration;
                    // NOTE: The previous line could alternatively be
                    //              HORN_lastChangeTime = now
                    //        which is the style used in the BlinkWithoutDelay example sketch
                    //        Adding on the interval is a better way to ensure that succesive periods are identical
                    lnprintf("Horn will be OFF for %d Sec.\n", horn_interval/1000);
                }
                break;

            case HORN_OFF:
                if (elapsed >= horn_interval) {
                    digitalWrite(HORN_pin, HORN_ON);
                    HORN_lastChangeTime += horn_interval;
                    lnprintf("Horn will be ON for %d Sec.\n", horn_duration/1000);
                }
                break;
        } // end switch
    }
    else {
        if (hornState==HORN_ON) {
            digitalWrite(HORN_pin, HORN_OFF);
        }
        HORN_lastChangeTime=now; // ??? ma serve?
    }


}
