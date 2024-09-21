
//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"




void testAlarm() {
    buzzerPumpOn();
    delay(2000);
    buzzerPumpOff();
    return;
    delay(2000);

    lnprintf("%sturning Horn ON\n", BLANK_2);
    togglePinWithDelay(HORN_pin, 4000);
    delay(2000);

    lnprintf("%sturning PressControl ON\n", BLANK_2);
    togglePinWithDelay(sonoff_emergency_pin, 500); // switch press control state
    delay(2000);

    lnprintf("%sturning PressControl OFF\n", BLANK_2);
    togglePinWithDelay(sonoff_emergency_pin, 500); // switch press control state
    delay(2000);
    lnprintf("TEST_ALARM_PIN completed\n");
}


