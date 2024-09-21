//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#include <Arduino.h>

#ifndef __MAIN_H__
    #define __MAIN_H__

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



    // #define PHASE_ALARM_THRESHOLD_NUMBER      3 // default:10


    #define MAX_PHASES              3
    #define PHASE_INTERVAL          15*1000L    // number of mseconds between Buzzer
    #define PHASE_ALARM_INTERVAL    PHASE_INTERVAL/5
    #define PHASE_MIN_INTERVAL      1*1000    // minimo intervallo di Buzzer
    #define PHASE_STEP_DOWN         PHASE_INTERVAL/30    // step con cui deve scendere l'intervallo per ogni fase

    enum enum_levels {
                    ON  = LOW,
                    OFF = HIGH,
                    // PUMP_ON  = LOW,
                    // PUMP_OFF = HIGH,
                    BUZZ_ON  = HIGH,
                    BUZZ_OFF = LOW,
                    // LED_ON   = LOW,
                    // LED_OFF  = HIGH,
                    // BUTTON_ON   = LOW,
                    // BUTTON_OFF  = HIGH,
                    // INP_ON   = LOW,
                    // INP_OFF  = HIGH,
                    // HORN_ON  = LOW,
                    // HORN_OFF = HIGH
                };




    typedef struct  {
        const char   *name;
        uint8_t pin;
        uint8_t mode = INPUT_PULLUP;
        bool longPress = false;
        bool shortPress = false;
        uint8_t pressed = LOW;
        uint8_t released = HIGH;
        uint8_t currState = HIGH;
        uint8_t lastState = HIGH;
        unsigned long lastDebounceTime = 0ul;
        unsigned long pressedMillis = 0ul;
        const unsigned long debounceDelay = 20ul;
        const unsigned long longPressLimit = 400ul;
    } bounce_button_t;







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




// ----------- F U N C T I O N S  -------------------

    // void lnprint(const char *msg, const unsigned long value=SKIP_PRINT_VALUE, const char *s2="\n");

    // void displayValues(void);
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
    // uint8_t getPhase(uint8_t phase_nr, uint8_t pump_time);
    void buzzerAlarm(uint8_t pin, uint8_t phase_num);



    // void buzzerPumpOn(uint8_t pin);
    // void buzzerPumpOff(uint8_t pin);

    // int initializePhases(void);
    void togglePinWithDelay(uint8_t pin, uint16_t toogle_delay=100);
    void checkPumpState();
    void buzzerOff();
    void buzzerPumpOn();
    void buzzerPumpOff();
    // void checkPassiveBuzzer();
    // void checkToneBuzzer(bool fStart=false);
    // void pumpAlarm(bool fStart=false);
    void pumpAlarm(uint8_t action);
    void pumpAlarmCheck(void);

    bool check_pumpState_pin(uint8_t pin, uint16_t touchDelay=300);
    bool check_pressControlState_pin(uint8_t pin);
    void readShortLongPress(bounce_button_t *butt);

#endif