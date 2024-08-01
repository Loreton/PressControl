//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"



// ==================================
// -
// ==================================
void checkPumpState() {
unsigned long elapsed;

    fPUMP = digitalRead(PUMP_STATE_PIN);

    switch(fPUMP) {
        case LOW:
            if (phase==0) {
                int _duration=500;
                int _frequency=500;
                for (int i=1;i<=4;i++) {
                    tone(BUZZER_PIN, _frequency*i, _duration);
                    delay(_duration*1.1);
                }
                noTone(BUZZER_PIN);
                setPhase(1);
            }

            elapsed = now-phase_start_time;
            if (elapsed >= phase_interval)  {
                setPhase(++phase);
                printStatus();
                // emissione BEEP
                buzzer_ON=true;
                lnprintf("Beep ON for: %d mS\n", buzzer_duration);
                tone(BUZZER_PIN, buzzer_frequency, buzzer_duration);

            }
            break;


        default:
            fALARM=false; // allarme rientrato
            // buzzer_OFF=0;
            if (phase>0) {
                setPhase(0);
                int _duration=500;
                int _frequency=500;
                for (int i=3;i>0;i--) {
                    tone(BUZZER_PIN, _frequency*i, _duration);
                    delay(_duration*1.1);
                }
                noTone(BUZZER_PIN);
            }
            break;
    }

}

