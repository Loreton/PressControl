//
// updated by ...: Loreto Notarantonio
// Date .........: 22-08-2024 11.20.08
//

#include <Arduino.h>

#define _I_AM_MAIN_CPP__
#include "main.h"






//######################################################
//#
//######################################################
void setup() {
    Serial.begin(115200);
    delay(1000);


    max_pump_time = initializePhases();


    /* ------ setup PINs
        You can use digitalWrite(pin, HIGH) before use pinMode(pin, OUTPUT)
        per evitare problemi con risorse esterne al momento dell'accensione
        conviene forzare l'output a livello desiderato prima di impostarlo come output
    */
    pinMode(PUMP_STATE_pin,         INPUT_PULLUP);
    pinMode(TEST_ALARM_pin,         INPUT_PULLUP);
    pinMode(PRESSCONTROL_STATE_pin, INPUT_PULLUP);

    digitalWrite(PRESSCONTROL_BUTTON_pin, OFF); pinMode(PRESSCONTROL_BUTTON_pin, OUTPUT);
    digitalWrite(LED_pin,                 OFF); pinMode(LED_pin                , OUTPUT);
    digitalWrite(PASSIVE_BUZZER_pin,      OFF); pinMode(PASSIVE_BUZZER_pin     , OUTPUT);
    digitalWrite(ACTIVE_BUZZER_pin,       OFF); pinMode(ACTIVE_BUZZER_pin      , OUTPUT);
    digitalWrite(HORN_pin,           HORN_OFF); pinMode(HORN_pin               , OUTPUT);

    displayValues();
    lnprintf("Starting...\n");
}




uint32_t seconds, last_second=0;
bool turn_second;
uint8_t phase_number=0;
uint8_t last_phase_number=0;
uint8_t pump_state=0;
uint8_t last_pump_state ;


void loop() {
    while(digitalRead(TEST_ALARM_pin) == ON) {
        lnprintf("TEST_ALARM [pin: %d] detected\n", TEST_ALARM_pin);
        testAlarm();
    }


    seconds = millis()/1000;
    if (last_second < seconds) {
        last_second = seconds;
        turn_second = true;
        lnprintf("pump_state: %d - phase_number: %d - pump_elapsed: %d\n", pump_state, phase_number, pump_elapsed);
        // lnprintf("last_pump_state:      %d\n", last_pump_state);
        // lnprintf("last_phase_number:    %d\n", last_phase_number);
    } else {
        turn_second = false;
    }




    pump_state = digitalRead(PUMP_STATE_pin);
    if (pump_state == PUMP_ON) {
        if (last_pump_state == PUMP_OFF) { // verifichiamo lo stato precedente
            last_pump_state = pump_state;
            start_pump_time = seconds;
            lnprintf("pump is ON\n");
            buzzerPumpOn(ACTIVE_BUZZER_pin);
        }
        pump_elapsed = seconds - start_pump_time;

        last_phase_number = phase_number;
        phase_number = getPhase(phase_number, pump_elapsed);
        if (phase_number != last_phase_number) {
            lnprintf("phase_number has been chnged to: %d\n", phase_number);
            buzzerAlarm(ACTIVE_BUZZER_pin, phase_number);
            // last_phase_number = phase_number;
        }
    } else {
        if (last_pump_state == ON) { // verifichiamo lo stato precedente
            lnprintf("pump is OFF\n");
            last_pump_state = OFF;
            last_phase_number = 0;
            phase_number = 0;
            // buzzerStopPump()
        }
        // last_pump_state = OFF;
        // start_pump_time = millis()/1000;

    }
}




// ==================================
// - per gestire l'overflow di millis()
// - bisogna operare come segue:
//      if all your time calculations are done as:
//      if  ((later_time - earlier_time ) >=duration ) {action}
//      then the rollover does generally not come into play.
//      For ease of understanding think in bytes ( 0.. 255 ), instead of unsigned longs.
//     Example: If your old time was at 250 and now you're at 5, 
//          you calculate (5 - 250) and interpret the result as an unsigned byte, the result is 11.      
//          then the rollover does generally not come into play.
// - vedi anche: https://arduino.stackexchange.com/questions/12587/how-can-i-handle-the-millis-rollover
// ==================================
void loopx() {

    now = millis();
    // checkLed();
    // checkHorn();


    if (buzzer_ON) {
        unsigned long elapsed = now-phase_start_time;  // elapsed: duration
        if (elapsed>=buzzer_duration) { // se stiamo suonando, portiamolo a termine
            lnprintf("Beep OFF - elapsed: %d mS\n", elapsed);
            noTone(PASSIVE_BUZZER_pin);
            buzzer_ON=false;
        }
    }


    if (fALARM) {
        // PressControl_Toggle();
    }

} // end loop()
