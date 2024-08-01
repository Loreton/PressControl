//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#include "main.h"


// ==================================
// -
// ==================================
void printStatus() {
    lnprintf("now %d - phase # : %d\n", now, phase);
    if (fALARM) {
        lnprintf("      ALARM ON\n");
    }
    if (fPUMP) {
        lnprintf("      phase_interval  : %d mSec\n", phase_interval);
        lnprintf("      buzzer_duration : %d mSec\n", buzzer_duration);
        lnprintf("      buzzer_frequency: %d Hz\n",    buzzer_frequency);
        lnprintf("      horn_interval   : %d mSec\n", horn_interval);
        lnprintf("      horn_duration   : %d mSec\n", horn_duration);
    }

}


/*
 * Define a REAL printf since Arduino doesn't have one
 *
 * SerialPrintf() will automatically put the format string in AVR program space
 * https://forum.arduino.cc/t/add-serial-printf-using-va_args-and-vprinf/51846/11
 */
// #define SerialPrintf(fmt, ...) _SerialPrintf(PSTR(fmt), ##__VA_ARGS__)

extern "C" {
    int serialputc(char c, FILE *fp) {
        if(c == '\n')
            Serial.write('\r');
        Serial.write(c);
        return 0;
    }
}


void _SerialPrintf(const char *fmt, ...) {
FILE stdiostr;
va_list ap;

  fdev_setup_stream(&stdiostr, serialputc, NULL, _FDEV_SETUP_WRITE);

  va_start(ap, fmt);
  vfprintf_P(&stdiostr, fmt, ap);
  va_end(ap);
}
