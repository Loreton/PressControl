//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#ifndef __MAIN_H__
    #define __MAIN_H__

    #include "pins.h"




    #define MAX_PHASES              3
    #define PHASE_INTERVAL          15*1000L    // number of mseconds between Buzzer
    #define PHASE_ALARM_INTERVAL    PHASE_INTERVAL/5
    #define PHASE_MIN_INTERVAL      1*1000    // minimo intervallo di Buzzer
    #define PHASE_STEP_DOWN         PHASE_INTERVAL/30    // step con cui deve scendere l'intervallo per ogni fase




    #ifdef _I_AM_MAIN_CPP__
        const char *BLANK_2 = {"  "};
        const char *BLANK_4 = {"    "};
        const char *BLANK_6 = {"      "};
        const char *BLANK_8 = {"        "};
        bool fPUMP;         // status della pompa
        bool fALARM=false;    // siamo in allarme. La pompa è rimasta accesa oltre i tempi previsti
        int phase_nr=0;
        unsigned long   now;
        // unsigned long   buzzer_duration, buzzer_frequency, buzzer_volume;
        unsigned long   phase_interval, next_phase_time, phase_start_time;

        out_pin_t emergency_S, relay_S, led_S, passiveBuzzer_S, activeBuzzer_S, horn_S;
        out_pin_t *emergency = &emergency_S, *relay=&relay_S, *led = &led_S, *passiveBuzzer = &passiveBuzzer_S, *activeBuzzer=&activeBuzzer_S, *horn=&horn_S;

        input_pin_t pumpState_S, pressControlState_S;
        input_pin_t *pumpState = &pumpState_S, *pressControlState = &pressControlState_S;

        bounced_pin_t start_PControl_S;
        bounced_pin_t *start_PControl = &start_PControl_S;


    #else
        extern const char *BLANK_2;
        extern const char *BLANK_4;
        extern const char *BLANK_6;
        extern const char *BLANK_8;
        extern bool fPUMP;         // status della pompa
        extern bool fALARM;    // siamo in allarme. La pompa è rimasta accesa oltre i tempi previsti
        extern int phase_nr;

        extern unsigned long   now;
        extern unsigned long   buzzer_duration; // , buzzer_frequency, buzzer_volume;
        extern unsigned long   phase_interval, phase_start_time;

        extern uint32_t alarm_time_duration;
        extern uint32_t alarm_start_time;

        extern out_pin_t *emergency, *relay, *led, *passiveBuzzer, *activeBuzzer, *horn;
        extern input_pin_t *pumpState, *pressControlState;
        extern bounced_pin_t *start_PControl;

    #endif







// int BEEP[] = { // phase, delaySec, frequency, duration)
//                    0,       5,         2000,     500,
//                    1,      10,         2000,    1000,
//                    2,      10,         2000,    1000,
//                    3,      10,         2000,    1000,
//                    4,      10,         2000,    1000,
//                    5,      10,         2000,    1000,
//                    6,      10,         2000,    1000,
//                    7,      10,         2000,    1000,
//                    8,      10,         2000,    1000,
//                    9,      10,         2000,    1000,
//                   10,      10,         2000,    1000,
//             };



    // Arduino non possidede __FILENAME__ ne Serial.printf()
    #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
    #define SerialPrintf(fmt, ...)     _SerialPrintf(PSTR(fmt), ##__VA_ARGS__)  // definita in printFunctions()

    #define _MAIN_SERIAL_PRINT
    #ifdef _MAIN_SERIAL_PRINT
        #define lnprintf(...)          SerialPrintf("[%-20s:%04d] ", __FILENAME__, __LINE__);SerialPrintf( __VA_ARGS__, __VA_ARGS__)

    #else
        #define lnprintf(...)
    #endif


    // ignore the following macros
    #define x_lnprintf(...)



    #include "prototypes.h"

#endif