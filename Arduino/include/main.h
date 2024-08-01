//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//

#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

// #if defined(ARDUINO) && ARDUINO >= 100
//   #include "Arduino.h"
// #else
//   #include "WConstants.h"
// #endif


//  ARDUINO NANO pins
    #define D00       0         // pin.30 D00 - RS232:RXD
    #define D01       1         // pin.31 D01 - RS232:TXD

    #define D02       2         // pin.32 - D02 -           -
    #define D03       3         // pin.01 - D03 -           - PWM
    #define D04       4         // pin.02 - D04 - I2C:SDA
    #define D05       5         // pin.09 - D05 - I2C:SCL   - PWM
    #define D06       6         // pin.10 - D06 -           - PWM
    #define D07       7         // pin.11 - D07 -           -
    #define D08       8         // pin.12 - D08 -           -
    #define D09       9         // pin.13 - D09 -           - PWM
    #define D10      10         // pin.14 - D10 - SPI:SS    - PWM
    #define D11      11         // pin.15 - D11 - SPI:MOSI  - PWM
    #define D12      12         // pin.16 - D12 - SPI:MISO  -
    #define D13      13         // pin.17 - D13 - SCK       - R1K + LED

    #define A00      A00        // pin.19 - A00-D14 - Analog or Digital
    #define A01      A01        // pin.20 - A01-D15 - Analog or Digital
    #define A02      A02        // pin.21 - A02-D16 - Analog or Digital
    #define A03      A03        // pin.22 - A03-D17 - Analog or Digital
    #define A04      A04        // pin.23 - A04-D18 - Analog or Digital
    #define A05      A05        // pin.24 - A05-D19 - Analog or Digital

    #define A06      A06        // pin.25 - A06         - Analog exclusive pins
    #define A07      A07        // pin.26 - A06         - Analog exclusive pins
    #define RESET             // pin.26 - A06         - Analog exclusive pins

    #define PHASE_INTERVAL          60*1000L    // number of mseconds between Buzzer
    #define PHASE_ALARM_INTERVAL    PHASE_INTERVAL/5
    #define PHASE_MIN_INTERVAL      1*1000    // minimo intervallo di Buzzer
    #define PHASE_STEP_DOWN         PHASE_INTERVAL/30    // step con cui deve scendere l'intervallo per ogni fase
    #define BUZZER_FREQUENCY        2000          // default: 2000 Buzzer frequency

    #define PHASE_ALARM_THRESHOLD_NUMBER      10 // default:10


    #define LED_DURATION            2000
    #define LED_INTERVAL            1000



    #define PUMP_STATE_PIN              D02
    #define PRESSCONTROL_BUTTON_PIN     D03
    #define HORN_PIN                    D04   // NOT USED
    #define ELETTROVALVOLA_PIN          D05   // NOT USED chiusura acqua a caduta.... da implementare
    #define TEST_ALARM_PIN              D06   // NOT USED
    #define BUZZER_PIN                  D12
    #define LED_PIN                     D13  // quello incorporato



    // enum enumState    {ON=LOW, OFF=HIGH};
    enum enum_levels {
                    ON=HIGH,
                    OFF=LOW,
                    HORN_ON=LOW,
                    HORN_OFF=HIGH
                };
    // enum enumState2    {HORN_ON=HIGH, HORN_OFF=LOW};




    // Arduino non possidede __FILENAME__ ne Serial.printf()
    #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
    #define SerialPrintf(fmt, ...)     _SerialPrintf(PSTR(fmt), ##__VA_ARGS__)  // definita in printFunctions()

    #define _MAIN_SERIAL_PRINT
    #ifdef _MAIN_SERIAL_PRINT
        #define lnprintf(...)                  SerialPrintf("[%-20s:%04d] ", __FILENAME__, __LINE__);SerialPrintf( __VA_ARGS__, __VA_ARGS__)

    #else
        #define lnprintfx(...)
    #endif


    // ignore the following macros
    #define X_lnprintf(...)

            // http://www.keywild.com/arduino/gallery/Nano_PinOut.png
    #ifdef _I_AM_PUMP_ALARM_CPP__

        int phase=0;
        unsigned long   now, next_beep_time;
        unsigned long   led_duration, led_interval;
        unsigned long   buzzer_duration, buzzer_frequency, buzzer_volume, buzzerOffTime;
        bool            buzzer_ON;
        bool            fTestAlarm;
        unsigned long   horn_duration, horn_interval;
        unsigned long   phase_interval, next_phase_time, phase_start_time;

        bool fPrint_BEEP    = true;
        bool fPrint_HORN    = true;
        bool fPrint_TONE    = false;
        bool fPrint_LED     = false;
        bool fPrint_VERBOSE = false;

        byte fPUMP;         // status della pompa
        bool fALARM=false;    // siamo in allarme. La pompa è rimasta accesa oltre i tempi previsti




    #else
        extern byte fPUMP;         // status della pompa
        extern bool fPrint_BEEP;
        extern bool fPrint_HORN;
        extern bool fPrint_TONE;
        extern bool fPrint_LED;
        extern bool fPrint_VERBOSE;

        extern bool fALARM;    // siamo in allarme. La pompa è rimasta accesa oltre i tempi previsti


        extern const int Buzzer;
        // extern const int blinkingLED;

        extern int phase;
        extern unsigned long   now, next_beep_time;
        extern unsigned long   led_duration, led_interval;
        extern unsigned long   buzzer_duration, buzzer_frequency, buzzer_volume, buzzerOffTime;
        extern bool            buzzer_ON;
        extern bool            fTestAlarm;
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

// ----------- F U N C T I O N S  -------------------

    // void lnprint(const char *msg, const unsigned long value=SKIP_PRINT_VALUE, const char *s2="\n");
    void setPhase(int);
    void checkPumpState(void);
    void checkLed(void);
    void checkHorn(void);
    void PressControl_Toggle(void);
    void printStatus(void);
    void testAlarm(void);
    void _SerialPrintf(const char *fmt, ...);
#endif