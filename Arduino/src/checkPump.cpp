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
int _duration=500;
int _frequency=500;

    uint8_t pump_state = digitalRead(PUMP_STATE_pin);  // logica inversa. PumpON->LowLevel
    switch(pump_state) {
        case PUMP_ON:
            fPUMP = true;
            if (phase_nr==0) {
                lnprintf("Pump status: ON\n");
                // buzzerPumpOn(PASSIVE_BUZZER_pin);

                for (int i=1; i<=4; i++) {
                    tone(PASSIVE_BUZZER_pin, _frequency*i, _duration);
                    delay(_duration*1.1);
                }
                noTone(PASSIVE_BUZZER_pin);
                setPhase(1);
            }

            elapsed = now-phase_start_time;
            if (elapsed >= phase_interval)  {
                setPhase(++phase_nr);
                printStatus();
                // emissione BEEP
                buzzer_ON=true;
                lnprintf("Buzzer ON for: %d mS\n", buzzer_duration);
                tone(PASSIVE_BUZZER_pin, buzzer_frequency, buzzer_duration);

            }
            break;


        default:
            fALARM=false; // allarme rientrato
            fPUMP = false;
            if (phase_nr>0) {
                lnprintf("Pump status: OFF\n");
                setPhase(0);
                // buzzerPumpOff(PASSIVE_BUZZER_pin);
                for (int i=3;i>0;i--) {
                    tone(PASSIVE_BUZZER_pin, _frequency*i, _duration);
                    delay(_duration*1.1);
                }
                noTone(PASSIVE_BUZZER_pin);
            }
            break;
    }
    // digitalWrite(PASSIVE_BUZZER_pin, OFF); // quando uso il passive_pin con un active_buzzer

}

