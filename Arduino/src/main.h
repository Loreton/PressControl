//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#ifndef MAIN_H
#define MAIN_H

#include "pins.h"

// #if defined(ARDUINO) && ARDUINO >= 100
//   #include "Arduino.h"
// #else
//   #include "WConstants.h"
// #endif

// typedef unsigned int uint;
// typedef unsigned long ulong;


// valid typedef
// int8_t   int16_t     int32_t
// uint8_t  uint16_t    uint32_t




    #define PHASE_ALARM_THRESHOLD_NUMBER      10 // default:10
    #define MAX_PHASES                        6

    // #define PHASE_INTERVAL_l          60*1000L    // number of mSeconds between Buzzer
    // #define PHASE_ALARM_INTERVAL_l    PHASE_INTERVAL_l/5
    // #define PHASE_MIN_INTERVAL        1*1000    // minimo intervallo di Buzzer
    // #define PHASE_STEP_DOWN_l         PHASE_INTERVAL_l/30    // step con cui deve scendere l'intervallo per ogni fase
    // #define BUZZER_FREQUENCY          2000          // default: 2000 Buzzer frequency
    // #define PHASE_LENGTH_l            60000L  // mSec 60 secondi



    #define LED_DURATION            2000
    #define LED_INTERVAL            1000

    #define ACTIVE_BUZZER false



    // enum enumState    {ON=LOW, OFF=HIGH};
    enum enum_levels {
                    PUMP_ON=0,
                    PUMP_OFF=1,
                    ON=LOW,
                    OFF=HIGH,
                    HORN_ON=LOW,
                    HORN_OFF=HIGH
                };
    // enum enumState2    {HORN_ON=HIGH, HORN_OFF=LOW};








    #ifdef _I_AM_MAIN_CPP__
        const char *BLANK_2 = {"  "};
        const char *BLANK_4 = {"    "};
        const char *BLANK_6 = {"      "};
        const char *BLANK_8 = {"        "};
        char floatBuffer[10]; // Arduino non supporta il print del float quindi bisogna convertirlo in string.... dotostr()

        // uint8_t     phase_number      = 0;
        // uint8_t     last_phase_number = 0;
        // uint8_t     pump_state        = 0;
        // uint8_t     last_pump_state   = 0;
        uint32_t    start_pump_time   = 0; // sec
        uint32_t    max_pump_time     = 0; // sec
        uint32_t    pump_elapsed      = 0; // sec
        uint16_t    PHASE[MAX_PHASES];
        uint8_t phaseNr=0;




        unsigned long   now;
        // ulong next_beep_time;
        unsigned long   led_interval;
        unsigned long   led_duration;
        unsigned long   buzzer_duration, buzzer_frequency, buzzer_volume, buzzerOffTime;
        bool            buzzer_ON;
        // bool            fTestAlarm;
        unsigned long   horn_duration, horn_interval;
        unsigned long   phase_interval, next_phase_time, phase_start_time;

        // bool fPrint_BEEP    = true;
        // bool fPrint_HORN    = true;
        // bool fPrint_TONE    = false;
        // bool fPrint_LED     = false;
        // bool fPrint_VERBOSE = false;

        byte fPUMP;         // status della pompa
        bool fALARM=false;    // siamo in allarme. La pompa è rimasta accesa oltre i tempi previsti


    #else
        extern const char *BLANK_2;
        extern const char *BLANK_4;
        extern const char *BLANK_6;
        extern const char *BLANK_8;

        extern char         floatBuffer[];
        // extern uint8_t     phase_number ;
        // extern uint8_t     last_phase_number ;
        // extern uint8_t     pump_state ;
        // extern uint8_t     last_pump_state ;
        extern uint32_t    start_pump_time ; // sec
        extern uint32_t    max_pump_time ; // sec
        extern uint32_t    pump_elapsed ; // sec
        extern uint16_t    PHASE[];

        extern uint8_t phaseNr;


        // extern int PHASE[];
        // extern uint8_t current_phase_number;


        extern byte fPUMP;         // status della pompa
        // extern bool fPrint_BEEP;
        // extern bool fPrint_HORN;
        // extern bool fPrint_TONE;
        // extern bool fPrint_LED;
        // extern bool fPrint_VERBOSE;

        extern bool fALARM;    // siamo in allarme. La pompa è rimasta accesa oltre i tempi previsti


        extern const int Buzzer;
        // extern const int blinkingLED;
        extern int   current_pump_time;

        extern unsigned long   now;
        extern unsigned long   led_interval;
        extern unsigned long   led_duration;
        extern unsigned long   now, next_beep_time;
        extern unsigned long   buzzer_duration, buzzer_frequency, buzzer_volume, buzzerOffTime;
        extern bool            buzzer_ON;
        // extern bool            fTestAlarm;
        extern unsigned long   horn_duration, horn_interval;
        extern unsigned long   phase_interval, next_phase_time, phase_start_time;



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
        #define lnprintfx(...)
    #endif


    // ignore the following macros
    #define X_lnprintf(...)
    #define x_lnprintf(...)




// ----------- F U N C T I O N S  -------------------

    // void lnprint(const char *msg, const unsigned long value=SKIP_PRINT_VALUE, const char *s2="\n");

    void displayValues(void);
    void setPhase(int);
    // uint getPhase(void);
    void heckPumpState(int pump_status);
    void checkLed(void);
    void checkHorn(void);
    void PressControl_Toggle(void);
    void printStatus(void);

    // ---- new
    void testAlarm(void);
    void _SerialPrintf(const char *fmt, ...);
    void testPrint(void);
    // uint8_t getPhase(uint8_t pump_time);
    uint8_t getPhase(uint8_t phase_nr, uint8_t pump_time);
    void buzzerAlarm(uint8_t pin, uint8_t phase_num);



    void buzzerPumpOn(uint8_t pin);
    void buzzerPumpOff(uint8_t pin);

    int initializePhases(void);
    void togglePinWithDelay(uint8_t pin, uint16_t toogle_delay=100);


#endif