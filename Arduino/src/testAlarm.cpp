
//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"




void testAlarm() {
    pumpOnNotification();
    delay(2000);
    pumpOffNotification();
    delay(2000);

    togglePinWithDelay(horn, 4000);
    delay(2000);

    togglePinWithDelay(emergency, 500); // switch press control state
    delay(2000);
    togglePinWithDelay(relay, 500); // switch press control state
    delay(2000);

    lnprintf("TEST_ALARM_PIN completed\n");
}


