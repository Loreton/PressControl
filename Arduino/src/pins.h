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


    #define ACTIVE_BUZZER_pin           D02 // OUTPUT
    #define PASSIVE_BUZZER_pin          D03 // OUTPUT - PWM



    #define PRESSCONTROL_STATE_pin      D06 // INPUT_PULLUP
    #define PUMP_STATE_pin              D07 // INPUT_PULLUP
    #define HORN_pin                    D09 // OUTPUT NOT USED

    #define PRESSCONTROL_BUTTON_pin     D11  // INPUT_PULLUP
    #define TEST_ALARM_pin              D12  // INPUT_PULLUP
    #define LED_pin                     D13  // OUTPUT quello incorporato
    // #define ELETTROVALVOLA_PIN          D05   // NOT USED chiusura acqua a caduta.... da implementare

    // #define BUZZER_PIN                 ACTIVE_BUZZER_pin // OUTPUT


#endif