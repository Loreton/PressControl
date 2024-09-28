//
// updated by ...: Loreto Notarantonio
// Date .........: 30-07-2024 12.04.08
//
#ifndef PROTOTYPES_H_
    #define PROTOTYPES_H_


// ----------- F U N C T I O N S  -------------------

    // void lnprint(const char *msg, const unsigned long value=SKIP_PRINT_VALUE, const char *s2="\n");

    // void displayValues(void);
    void setPhase(uint8_t phase_nr);
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
    void togglePinWithDelay(uint8_t pin, uint16_t toogle_delay=100, const char *name="");
    void togglePinWithDelay(out_pin_t *pin, uint16_t delaymS=100);
    void checkPumpState();
    void soundOff();
    // void buzzerPumpOn();
    // void buzzerPumpOff();
    void pumpOnNotification();
    void pumpOffNotification();
    // void checkPassiveBuzzer();
    // void checkToneBuzzer(bool fStart=false);
    // void pumpAlarm(bool fStart=false);
    void pumpAlarm(uint8_t action);
    void pumpAlarmCheck(void);

    // bool check_pumpState_pin(uint8_t pin, uint16_t touchDelay=300);
    // bool check_pressControlState_pin(uint8_t pin);
    // void readShortLongPress(bounced_pin_t *butt);
    void    toggleBuzzer(uint8_t pin, uint16_t delaymS) ;

    void    configBouncedPin(bounced_pin_t *p, uint8_t pin_nr, uint8_t mode, bool press_level, const char *name);
    uint8_t readShortLongPress(bounced_pin_t *b, uint8_t buzzer_pin=0); // buzzer pin per indicare la ricezione del tasto

    void    configInputPin(input_pin_t *p, uint8_t nr, uint8_t mode, bool press_level, const char *name);
    bool    readPin(input_pin_t *p);

    void    configOutPin(out_pin_t *p,      uint8_t pin_nr, bool on_level, const char *name);
    void    writePin(out_pin_t *out_pin,    uint8_t level);

#endif