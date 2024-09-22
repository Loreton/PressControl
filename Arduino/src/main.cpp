//
// updated by ...: Loreto Notarantonio
// Date .........: 22-08-2024 11.20.08
//

#include <Arduino.h>

#define _I_AM_MAIN_CPP__
#include "main.h"




bounce_button_t actionButton;

void displayPinState() {
    lnprintf("HORN_pin:              %d\n" , digitalRead(HORN_pin));
    lnprintf("arduino_PControl_pin:  %d\n" , digitalRead(arduino_PControl_pin));
    lnprintf("passiveBuzzer_pin:     %d\n" , digitalRead(passiveBuzzer_pin));
    lnprintf("activeBuzzer_pin:      %d\n" , digitalRead(activeBuzzer_pin));
    lnprintf("pumpState_pin:         %d\n" , digitalRead(pumpState_pin));
    lnprintf("pressControlState_pin: %d\n" , digitalRead(pressControlState_pin));
    lnprintf("sonoff_emergency_pin:  %d\n" , digitalRead(sonoff_emergency_pin));
    lnprintf("start_PControl_pin:    %d\n" , digitalRead(start_PControl_pin));
}


//######################################################
//#
//######################################################
void setup() {
    Serial.begin(115200);
    delay(1000);

    actionButton.name = "pressControlButton";
    actionButton.pin = start_PControl_pin;
    // actionButton.mode = INPUT_PULLUP;

    // bounce_button TestAlarm;
    // emergency.name = "TestAlarm";
    // emergency.pin = TestAlarm_pin;
    // emergency.mode = INPUT_PULLUP;
    pinMode(actionButton.pin, actionButton.mode);


    /* ------ setup PINs
        You can use digitalWrite(pin, HIGH) before use pinMode(pin, OUTPUT)
        per evitare problemi con risorse esterne al momento dell'accensione
        conviene forzare l'output a livello desiderato prima di impostarlo come output
    */
    pinMode(pumpState_pin,         INPUT_PULLUP);
    // pinMode(TestAlarm_pin,         INPUT_PULLUP);
    pinMode(pressControlState_pin, INPUT_PULLUP);



    digitalWrite(sonoff_emergency_pin, OFF); pinMode(sonoff_emergency_pin, OUTPUT);
    digitalWrite(LED_pin,              OFF); pinMode(LED_pin                , OUTPUT);
    // digitalWrite(passiveBuzzer_pin, BUZZ_OFF);
    noTone(passiveBuzzer_pin);                 pinMode(passiveBuzzer_pin     , OUTPUT);
    digitalWrite(activeBuzzer_pin,  BUZZ_OFF); pinMode(activeBuzzer_pin      , OUTPUT);
    digitalWrite(HORN_pin,           OFF); pinMode(HORN_pin               , OUTPUT);

    // displayValues();
    lnprintf("Starting...\n");
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
#define PRESS_CONTROL_BUTTON 1
#define TEST_BUTTON          2

void loop() {
    static unsigned long last_second=0;
    static unsigned long elapsed;
    unsigned long seconds;
    now = millis();

    uint8_t pressedButton = readShortLongPress(&actionButton, activeBuzzer_pin);

    /*
        long press -> test action
        esegue i test per verificare che tutte le funzionalitù siano attive
    */
    if (pressedButton == TEST_BUTTON) {
        displayPinState();
        lnprintf("TEST button has been detected\n");
        // ----  reset  all
        if ( digitalRead(pressControlState_pin == ON) ) {
            // digitalWrite(sonoff_emergency_pin, ON);
            togglePinWithDelay(sonoff_emergency_pin, 500); // switch press control state
        }

        // digitalWrite(pressControlState_pin, OFF);
        // displayPinState();
        // delay(5000);
        // buzzerPumpOff();
        // buzzerOff();
        // setPhase(0);
        // pumpAlarm(OFF);
        // lnprintf("\n");

        // start test
        // testAlarm();
    }

    return; // simula il continue
    if (pressedButton == PRESS_CONTROL_BUTTON) {

    }

    // --- controllo pompa
    if (digitalRead(pumpState_pin) == ON) { // logica inversa. PumpON->LowLevel
    // if (check_pumpState_pin(pumpState_pin, 300) ) {

        fPUMP = true;
        if (phase_nr==0) {
            lnprintf("Pump status: ON\n");
            buzzerPumpOn();
            setPhase(1);
        }

        elapsed = now-phase_start_time;
        if (elapsed >= phase_interval)  {
            setPhase(phase_nr+1);
            pumpAlarm(ON);
        }
    }
    else {
        fALARM = false; // allarme rientrato
        fPUMP = false;
        if (phase_nr>0) {
            lnprintf("Pump status: OFF\n");
            buzzerOff();
            setPhase(0);
            buzzerPumpOff();
            pumpAlarm(OFF);
        }
    }

    pumpAlarmCheck(); // nel caso fosse attivo il buzzer di alarm
    // checkLed();
    // checkHorn();

    seconds = now/1000;
    x_lnprintf("now: %ld - seconds: %ld - last_second: %ld\n", now, seconds, last_second);
    if (seconds > last_second) {
        last_second = seconds;
        if (fPUMP) {
            lnprintf("phase_nr: %d - phase_interval: %ld - phase_start_time: %ld - elapsed: %ld\n", phase_nr, phase_interval, phase_start_time, now-phase_start_time);
            lnprintf("phase_nr: %d - phase_interval: %ld - phase_start_time: %ld - remaining: %ld\n", phase_nr, phase_interval, phase_start_time, now-phase_start_time);
        } else {
            lnprintf("elapsed seconds: %ld\n", seconds);

            // if (digitalRead(pressControlState_pin) == ON) { // logica inversa. PumpON->LowLevel
            //     lnprintf("Press control: ON\n");
            // }
        }
    }



    // --- forse non posso farlo altrimenti accendo e spengo,
    //    però la prima volta dovrebbe spegnere il pressControl e l'allarme dovrebbe rientrare
    //    da verificare
    if (fALARM) PressControl_Toggle();


}



