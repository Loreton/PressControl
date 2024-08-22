
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



//##########################################################
//# Suona il buzzer tante volte quante il phase_number
//##########################################################
void buzzerAlarm(uint8_t pin, uint8_t phase_num) {
    lnprintf("BUZZER [pin: %d] PHASE ALARM phase: %d\n", pin, phase_num);
    for (uint8_t i = 0; i <= phase_num; ++i) {
        togglePinWithDelay(pin, 2000);
    }
}


void testAlarmPassiveBuzzer() {
    int _duration=500;
    int _frequency=500;
    lnprintf("%srunning buzzer on pin: %d\n", PASSIVE_BUZZER_pin);
    lnprintf("%sincrease buzzer tone\n", BLANK_2);
    for (int i=1;i<=5;i++) {
        tone(PASSIVE_BUZZER_pin, _frequency*i, _duration);
        delay(_duration*1.1);

    }
    lnprintf("%sdecrease buzzer tone\n", BLANK_2);
    for (int i=5;i>0;i--) {
        tone(PASSIVE_BUZZER_pin, _frequency*i, _duration);
        delay(_duration*1.1);
    }
    noTone(PASSIVE_BUZZER_pin);

    lnprintf("%sturning Horn ON\n", BLANK_2);
    togglePinWithDelay(HORN_pin, 4000);
    delay(2000);
    lnprintf("%sturning PressControl ON\n", BLANK_2);
    togglePinWithDelay(PRESSCONTROL_BUTTON_pin, 500); // switch press control state
    delay(2000);
    lnprintf("%sturning PressControl OFF\n", BLANK_2);
    togglePinWithDelay(PRESSCONTROL_BUTTON_pin, 500); // switch press control state
    delay(2000);
    lnprintf("TEST_ALARM_PIN completed\n");
    return;
}




#if ACTIVE_BUZZER == true
    //##########################################################
    //# Suona un active buzzer
    //##########################################################
    void buzzerPumpOn(uint8_t pin) {
        lnprintf("running buzzer on pin: %d\n", pin);

        for (int i=1; i<=5; i++) {
            uint16_t _delay=200;
            togglePinWithDelay(pin, _delay);
            delay(200);
        }
    }

    //##########################################################
    //# Suona un active buzzer
    //##########################################################
    void buzzerPumpOff(uint8_t pin) {
        lnprintf("running buzzer on pin: %d\n", pin);
        for (int i=2; i>=1; i--) {
            uint16_t _delay=200;
            togglePinWithDelay(pin, _delay);
            delay(200);
        }
    }

#else
    //##########################################################
    //# Suona un passive buzzer
    //##########################################################
    void buzzerPumpOn(uint8_t pin) {
        lnprintf("running buzzer on pin: %d\n", pin);
        int _duration=500;
        int _frequency=500;
        lnprintf("%sincrease buzzer tone\n", BLANK_2);
        for (int i=1;i<=5;i++) {
            tone(pin, _frequency*i, _duration);
            delay(_duration*1.1);

        }
        noTone(pin);
        digitalWrite(pin, OFF);
    }

    //##########################################################
    //# Suona un passive buzzer
    //##########################################################
    void buzzerPumpOff(uint8_t pin) {
        lnprintf("running buzzer on pin: %d\n", pin);
        int _duration=500;
        int _frequency=500;
        lnprintf("%sdecrease buzzer tone\n", BLANK_2);
        for (int i=5;i>0;i--) {
            tone(pin, _frequency*i, _duration);
            delay(_duration*1.1);
        }
        noTone(pin);
        digitalWrite(pin, OFF);
    }

#endif


// //##########################################################
// //# Suona un passive buzzer
// //##########################################################
// void passiveBuzzer(uint8_t pin, bool up) {
//     int _duration=500;
//     int _frequency=500;
//     lnprintf("%srunning buzzer on pin: %d\n", pin);
//     lnprintf("%sincrease buzzer tone\n", BLANK_2);
//     for (int i=1;i<=5;i++) {
//         tone(pin, _frequency*i, _duration);
//         delay(_duration*1.1);

//     }
//     lnprintf("%sdecrease buzzer tone\n", BLANK_2);
//     for (int i=5;i>0;i--) {
//         tone(pin, _frequency*i, _duration);
//         delay(_duration*1.1);
//     }
//     noTone(pin);

// }


// void activeBuzzerIncrease(uint8_t pin) {
//     activeBuzzer(pin, true);
// }

// void activeBuzzerDecrease(uint8_t pin) {
//     activeBuzzer(pin, false);
// }
// void passiveBuzzerIncrease(uint8_t pin) {
//     passiveBuzzer(pin, true);
// }

// void passiveBuzzerDecrease(uint8_t pin) {
//     passiveBuzzer(pin, false);
// }



void testAlarm() {
    buzzerPumpOn(ACTIVE_BUZZER_pin);
    delay(2000);
    buzzerPumpOff(ACTIVE_BUZZER_pin);
    return;
    delay(2000);

    lnprintf("%sturning Horn ON\n", BLANK_2);
    togglePinWithDelay(HORN_pin, 4000);
    delay(2000);

    lnprintf("%sturning PressControl ON\n", BLANK_2);
    togglePinWithDelay(PRESSCONTROL_BUTTON_pin, 500); // switch press control state
    delay(2000);

    lnprintf("%sturning PressControl OFF\n", BLANK_2);
    togglePinWithDelay(PRESSCONTROL_BUTTON_pin, 500); // switch press control state
    delay(2000);
    lnprintf("TEST_ALARM_PIN completed\n");
}


