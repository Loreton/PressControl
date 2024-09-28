//
// updated by ...: Loreto Notarantonio
// Date .........: 22-08-2024 11.20.08
//

#include <Arduino.h>

#define _I_AM_MAIN_CPP__
#include "main.h"




// bounced_pin_t actionButton;

void displayPinState() {
    // lnprintf("HORN_pin:              %d\n" , digitalRead(HORN_pin));
    lnprintf("relay_PControl_pin:    %d\n" , !digitalRead(relay_PControl_pin));
    // lnprintf("passiveBuzzer_pin:     %d\n" , digitalRead(passiveBuzzer_pin));
    // lnprintf("activeBuzzer_pin:      %d\n" , digitalRead(activeBuzzer_pin));
    lnprintf("pumpState_pin:         %d\n" , !digitalRead(pumpState_pin));
    lnprintf("pressControlState_pin: %d\n" , !digitalRead(pressControlState_pin));
    // lnprintf("sonoff_emergency_pin:  %d\n" , digitalRead(sonoff_emergency_pin));
    // lnprintf("start_PControl_pin:    %d\n" , digitalRead(start_PControl_pin));
}


//######################################################
//#
//######################################################
void setup() {
    Serial.begin(115200);
    delay(1000);

    // actionButton.name = "pressControlButton";
    // actionButton.pin = start_PControl_pin;
    // actionButton.mode = INPUT_PULLUP;

    // bounce_button TestAlarm;
    // emergency.name = "TestAlarm";
    // emergency.pin = TestAlarm_pin;
    // emergency.mode = INPUT_PULLUP;
    // pinMode(actionButton.pin, actionButton.mode);


    /* ------ setup PINs
        You can use digitalWrite(pin, HIGH) before use pinMode(pin, OUTPUT)
        per evitare problemi con risorse esterne al momento dell'accensione
        conviene forzare l'output a livello desiderato prima di impostarlo come output
    */
    // pinMode(pumpState_pin,         INPUT_PULLUP);
    // pinMode(pressControlState_pin, INPUT_PULLUP);

    // pinMode(TestAlarm_pin,         INPUT_PULLUP);
    configInputPin(pressControlState, pressControlState_pin,  INPUT_PULLUP,   LOW, "PressControl relay State");
    configInputPin(pumpState,         pumpState_pin,          INPUT_PULLUP,   LOW, "Pump relay State");


    //        out_pin,      pin_nr,                on_level, *name);
    configOutPin(emergency,        sonoff_emergency_pin,   LOW,   "PressControl button");
    configOutPin(relay,            relay_PControl_pin,     HIGH,    "Alternative PressControl Relay");
    configOutPin(led,              LED_pin,                LOW,   "Led");
    configOutPin(passiveBuzzer,    passiveBuzzer_pin,      HIGH,   "passiveBuzzer");
    configOutPin(activeBuzzer,     activeBuzzer_pin,       HIGH,   "activeBuzzer");
    configOutPin(horn,             HORN_pin,               LOW,   "Horn");

    configBouncedPin(start_PControl,    start_PControl_pin,  INPUT_PULLUP,   LOW,   "start_PControl button");


    // digitalWrite(sonoff_emergency_pin, OFF); pinMode(sonoff_emergency_pin, OUTPUT);
    // digitalWrite(LED_pin,              OFF); pinMode(LED_pin                , OUTPUT);
    // // digitalWrite(passiveBuzzer_pin, BUZZ_OFF);
    // noTone(passiveBuzzer_pin);                 pinMode(passiveBuzzer_pin     , OUTPUT);
    // digitalWrite(activeBuzzer_pin,  BUZZ_OFF); pinMode(activeBuzzer_pin      , OUTPUT);
    // digitalWrite(HORN_pin,           OFF); pinMode(HORN_pin               , OUTPUT);

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

uint8_t curr_PressControlState=0;
void loop() {
    static unsigned long last_second=0;
    // static uint8_t last_PressControlState;
    static unsigned long elapsed;
    unsigned long seconds;
    now = millis();
    // curr_PressControlState = digitalRead(pressControlState_pin);
    readPin(pressControlState);


    uint8_t pressedButton = readShortLongPress(start_PControl, activeBuzzer_pin);

    /*
        long press -> test action
        esegue i test per verificare che tutte le funzionalitù siano attive
    */
    if (pressedButton == LONG_PRESS) {
        displayPinState();
        lnprintf("TEST button has been detected\n");
        // ----  reset  all
        if (digitalRead(pressControlState_pin == ON) ) {
            // digitalWrite(sonoff_emergency_pin, ON);
            // togglePinWithDelay(sonoff_emergency_pin, 500, "Emergency"); // switch press control state
            // togglePinWithDelay(emergency, 2000); // switch press control state
            writePin(emergency, OFF); // switch press control state
        }

        // digitalWrite(pressControlState_pin, OFF);
        displayPinState();
        // delay(5000);
        // pumpOffNotification();
        // soundOff();
        // setPhase(0);
        // pumpAlarm(OFF);
        lnprintf("\n");

        // start test
        // testAlarm();
    }

    if (pressedButton == SHORT_PRESS) {
        // displayPinState();
        // delay(1000);
        // if (curr_PressControlState == ON) ) {
        //     writePin(emergency, OFF); // switch press control state
        // } else {
        //     writePin(emergency, ON); // switch press control state
        // }
        // displayPinState();

    }
    // lnprintf("last_PressControlState %d  - curr_PressControlState %d\n", last_PressControlState, curr_PressControlState);
    // if (curr_PressControlState != last_PressControlState) {
    //     lnprintf("Press Control  State has changed form %d to %d\n", last_PressControlState, curr_PressControlState);
    //     last_PressControlState = curr_PressControlState;
    // }
    return; // simula il continue

    // --- controllo pompa
    if (digitalRead(pumpState_pin) == ON) { // logica inversa. PumpON->LowLevel
    // if (check_pumpState_pin(pumpState_pin, 300) ) {

        fPUMP = true;
        if (phase_nr==0) {
            lnprintf("Pump status: ON\n");
            pumpOnNotification();
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
            soundOff();
            setPhase(0);
            pumpOffNotification();
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



