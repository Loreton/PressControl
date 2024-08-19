# PressControl
Arduino - Gestione pompa ed allarme in caso di lunga apertura





___________________________________________________________________________________________________________________________________________________
    |                   |                   |                   |                   |                   |                   |
    |                   |                   |                   |                   |                   |                   |
    |                   |                   |                   |                   |                   |                   |

    ph1                 ph2                 ph3                 ph4                 ph5                 ph6                 ph_end
    pump_ON                                                                                                                 pressControl_OFF

per ogni phase diminuiamo il valore della sua durata in secondi del 10% circa in modo da avere degli allarmi buzzer
sempre più incalzanti....



    step_down 0.91%
    phase_1_len: 60 seconds
    phase_2_len: 54 seconds
    phase_3_len: 49 seconds
    phase_4_len: 44 seconds
    phase_5_len: 40 seconds
    total seconds: 247


ref: https://www.programiz.com/online-compiler/42EHaNdSRfMUF

    void calculatePhasesLength() {
        float step_down=91.0/100;
        //float step_down=.91;
        printf("step_down %.2f%%\n", step_down);
        int len=60;
        int result=len;

        int total=0;
        for (int i=1; i<=5; i++) {
            printf("phase_%d_len: %d seconds\n", i, result);
            total+=result;
            result=result*step_down;
        }
        printf("total seconds: %d", total);
    }






