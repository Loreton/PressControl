progetto Pump_Alarm

Frutto del Press-Control é composto da:
    -. Pulsante per accendere spegnere il Press-Control. Di fatto comanda, tramite un relay,
        il pulsante di un sOnOff che permette l'accensione del PC anche tramite l'app eWeLink.
    -. Led PCState    - Press-Control acceso.
    -. Led PumpState  - Pompa accesa.
    -. Buzzer che si accende, suono continuo, insieme al PumpState.
        Si può attivare/disattivare tramite un jumper interno al frutto.

    L'alimentazione dei questo frutto è presa localmente al quandro elettrico di casa, ma in caso
    di necessità può essere prelevata dai 5Volt presenti nel vano pompe utiizzando il filo arancione.


Frutto con Arduino:
    -. BlinkingLED
        - Lampeggio lento (2 sec circa) in condizioni di pompa spenta
        - Lampeggio veloce (3 al secondo) in condizioni di pompa accesa
    -. Buzzer che emette un suono quando la pompa risulta accesa.
       La frequenza dei beep aumenta man mano che passa il tempo.