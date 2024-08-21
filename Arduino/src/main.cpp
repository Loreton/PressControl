//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//

#include <Arduino.h>

#define _I_AM_MAIN_CPP__
#include "main.h"



//######################################################
//# Calculate phases length (seconds) reducing each
//# pahse by 10% baout
//######################################################
int calculatePhasesLength(void) {
    float step_down=91.0/100;
    lnprintf("----- Setup phase\n");
    /* ---- per convertire float string
            ref: https://forum.arduino.cc/t/float-double-and-other-any-type-with-sprintf/688692
        dtostrf( step_down, 4, 2, floatBuffer ); // dtostrf(float_value, min_width, decimal_digits, buffer)
        sprintf(floatBuffer, "%s", String(step_down, 5).c_str());
        sprintf(floatBuffer, "%d.%02d", (int)step_down, (int)(step_down * 100) % 100); quella che consuma meno memoria
    */

    sprintf(floatBuffer, "%d.%02d", (int)step_down, (int)(step_down * 100) % 100); // quella che consuma meno memoria
    lnprintf("step_down %s%%\n", floatBuffer);

    int ph_length=60; // vale per la prima fase
    int total=0;
    for (int ph=1; ph < MAX_PHASES; ph++) {
        lnprintf("  phase_%d_len: %d seconds\n", ph, ph_length);
        total+=ph_length;
        ph_length=ph_length*step_down;
        PHASE[ph] = ph_length;
    }
    lnprintf("total seconds: %d\n", total);
     return total;
}





//######################################################
//#
//######################################################
void setup() {
    Serial.begin(115200);
    delay(1000);

    max_pump_time = calculatePhasesLength();

    // ------ setup PINs
    pinMode(PUMP_STATE_pin,         INPUT_PULLUP);
    pinMode(TEST_ALARM_pin,         INPUT_PULLUP);
    pinMode(PRESSCONTROL_STATE_pin, INPUT_PULLUP);

    /*
        You can use digitalWrite(pin, HIGH) before use pinMode(pin, OUTPUT)
        per evitare problemi con risorse esterne al momento dell'accensione
        conviene forzare l'output a livello desiderato prima di impostarlo come output
    */
    digitalWrite(PRESSCONTROL_BUTTON_pin, OFF); pinMode(PRESSCONTROL_BUTTON_pin, OUTPUT);
    digitalWrite(LED_pin,                 OFF); pinMode(LED_pin                , OUTPUT);
    digitalWrite(BUZZER_pin,              OFF); pinMode(BUZZER_pin             , OUTPUT);
    digitalWrite(HORN_pin,           HORN_OFF); pinMode(HORN_pin               , OUTPUT);

    displayValues();
    lnprintf("Starting...\n");
}

void loop() {
    if (digitalRead(TEST_ALARM_pin) == ON) {
        testAlarm();
    }
    uint8_t pump_state = digitalRead(PUMP_STATE_pin);

    if (pump_state == ON) {
        if (last_pump_state == OFF) { // verifichiamo lo stato precedente
            last_pump_state = ON;
            start_pump_time = millis()/1000;
            // buzzerStartPump()
        }
        pump_elapsed = millis()/1000 - start_pump_time;
        lnprintf("pump elapsed...%d\n", pump_elapsed);
        uint8_t phase_number = getPhase(pump_elapsed);
        if (phase_number != last_phase_number) {
            buzzerAlarm(phase_number);
            last_phase_number = phase_number;
        }
        // checkPumpState(); // controlla lo status della pompa
    } else {
        if (last_pump_state == ON) { // verifichiamo lo stato precedente
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
            noTone(BUZZER_pin);
            buzzer_ON=false;
        }
    }


    if (fALARM) {
        // PressControl_Toggle();
    }

} // end loop()
