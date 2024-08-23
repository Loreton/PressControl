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
    lnprintf("now %ld - phase # : %d\n", now, phase_nr);
    if (fALARM) {
        lnprintf("      ALARM ON\n");
    }
    if (fPUMP) {
        lnprintf("      phase_interval  : %ld mSec\n", phase_interval);
        lnprintf("      buzzer_frequency: %ld Hz\n",   buzzer_frequency);
        lnprintf("      buzzer_duration : %ld mSec\n", buzzer_duration);
        lnprintf("      horn_interval   : %ld mSec\n", horn_interval);
        lnprintf("      horn_duration   : %ld mSec\n", horn_duration);
    }

}
// ==================================
// -
// ==================================
void testPrint() {
    #define lnprintf_for_test(...)    SerialPrintf( __VA_ARGS__, __VA_ARGS__)

    int             int_value   = -32768;
    unsigned int    uint_value  = 32769;
    long            long_value  = -2147483648l;
    unsigned long   ulong_value = 3147483647l;

    Serial.print(int_value);    lnprintf_for_test("  %d\n", int_value);
    Serial.print(uint_value);   lnprintf_for_test("  %u\n", uint_value);
    Serial.print(long_value);   lnprintf_for_test("  %ld\n", long_value);
    Serial.print(ulong_value);  lnprintf_for_test("  %lu\n", ulong_value);
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




/*
    %u per long ???
    %d per int
*/
void _SerialPrintf(const char *fmt, ...) {
FILE stdiostr;
va_list ap;

  fdev_setup_stream(&stdiostr, serialputc, NULL, _FDEV_SETUP_WRITE);

  va_start(ap, fmt);
  vfprintf_P(&stdiostr, fmt, ap);
  va_end(ap);
}

