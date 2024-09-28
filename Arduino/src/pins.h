//
// updated by ...: Loreto Notarantonio
// Date .........: 22-08-2024 11.18.42
//

#ifndef PINS_H
    #define PINS_H_


//  ARDUINO NANO pins
    // http://www.keywild.com/arduino/gallery/Nano_PinOut.png

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


    // #define ACTIVE_BUZZER_pin           D05 // OUTPUT
    // #define PASSIVE_BUZZER_pin          D06 // OUTPUT - PWM



    // #define PRESSCONTROL_STATE_pin      D10 // INPUT_PULLUP
    // #define PUMP_STATE_pin              D09 // INPUT_PULLUP

    // #define PRESSCONTROL_BUTTON_pin     D11  // INPUT_PULLUP
    // #define START_PCONTROL_pin          D11  // INPUT_PULLUP
    // #define TEST_ALARM_pin              D12  // INPUT_PULLUP
    // #define ELETTROVALVOLA_PIN          D05   // NOT USED chiusura acqua a caduta.... da implementare

    // #define BUZZER_PIN                 ACTIVE_BUZZER_pin // OUTPUT

    // #define sonoff_PControl_pin         D03  // OUTPUT
    // #define xxx2                        D08  // not used

    #define HORN_pin                    D04  // OUTPUT
    #define relay_PControl_pin          D05  // OUTPUT
    #define passiveBuzzer_pin           D06  // OUTPUT
    #define activeBuzzer_pin            D07  // OUTPUT
    #define pumpState_pin               D08  // INPUT PULLUP
    #define pressControlState_pin       D09  // INPUT PULLUP
    #define sonoff_emergency_pin        D10  // OUTPUT
    #define start_PControl_pin          D11  // INPUT PULLUP
    // #define TestAlarm_pin               D12  // INPUT PULLUP

    #define LED_pin                     D13  // OUTPUT quello incorporato


    enum enum_levels {
                    PC_ON = 0,
                    PC_OFF = 1,
                    OFF = LOW,
                    ON  = HIGH,
                    BUZZ_ON  = HIGH,
                    BUZZ_OFF = LOW,
                };


    #define SHORT_PRESS 1
    #define LONG_PRESS  2

    typedef struct  {
        const char   *name;
        uint8_t pin                          = 0;
        uint8_t mode                         = INPUT_PULLUP;
        bool    lastState                    = HIGH;
        bool    long_notify                  = true;         // flag to avoid ripetitive buzzer notification
        bool    short_notify                 = true;         // flag to avoid ripetitive buzzer notification
        bool    press_level                  = LOW;          // set level for pressed
        uint8_t press_time                   = 0;         // SHORT_PRESS, LONG_PRESS
        unsigned long pressedMillis          = 0ul;
        const unsigned long shortButtonPress = 400ul;
        const unsigned long longButtonPress  = 3000ul;
    } bounced_pin_t;

    typedef struct  {
        const char   *name;
        uint8_t pin                          = 0;
        uint8_t mode                         = OUTPUT;
        bool    state                        = HIGH;
        bool    lastState                    = HIGH;
        bool    ON                           = LOW;
        bool    OFF                          = HIGH;
    } out_pin_t;


    typedef struct  {
        const char   *name;
        uint8_t pin                          = 0;
        uint8_t mode                         = OUTPUT;
        bool    state                        = HIGH;
        bool    lastState                    = HIGH;
        bool    press_level                  = LOW;
        bool    OFF                          = HIGH;
    } input_pin_t;



#endif