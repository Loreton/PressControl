EESchema Schematic File Version 4
LIBS:Press-Control mgmt-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Allarme per pompa cisterna"
Date "dec. 2019"
Rev ""
Comp ""
Comment1 ""
Comment2 "Esaurito un determinato tempo Arduino provvede direttamente a spegnere la pompa"
Comment3 "Il tutto prosegue fino a che la pompa si spegne"
Comment4 "Quando la pompa si accende Arduino provvede ad emettere dei suoni "
$EndDescr
$Comp
L LnConnectors:CONN_02 J?
U 1 1 5DEBCAE0
P 9500 1300
F 0 "J?" V 9503 1628 60  0001 L CNN
F 1 "220V" V 9400 1400 60  0000 L CNN
F 2 "" H 9500 1300 60  0000 C CNN
F 3 "" H 9500 1300 60  0000 C CNN
	1    9500 1300
	1    0    0    -1  
$EndComp
Wire Notes Line
	10050 3300 10050 3600
Wire Notes Line
	10050 3600 10950 3600
Wire Notes Line
	10950 3600 10950 3300
Wire Notes Line
	10950 3300 10050 3300
Text Notes 10250 3500 0    50   ~ 0
PressControl
Wire Notes Line
	10050 5850 10050 6150
Wire Notes Line
	10050 6150 10950 6150
Wire Notes Line
	10950 6150 10950 5850
Wire Notes Line
	10950 5850 10050 5850
Text Notes 10250 6050 0    50   ~ 0
Pump
Wire Wire Line
	10250 2100 10250 1550
$Comp
L power:GNDA #PWR?
U 1 1 5DF1D0BD
P 9700 3200
F 0 "#PWR?" H 9700 2950 50  0001 C CNN
F 1 "GNDA" H 9800 3100 50  0000 C CNN
F 2 "" H 9700 3200 50  0001 C CNN
F 3 "" H 9700 3200 50  0001 C CNN
	1    9700 3200
	1    0    0    -1  
$EndComp
Text Notes 7400 2350 0    50   ~ 0
Celeste
Text Notes 7400 2450 0    50   ~ 0
Bianco/Celeste
Text Notes 7400 1750 0    50   ~ 0
Marrone
Text Notes 7400 1850 0    50   ~ 0
Bianco/Marrone
Text Notes 7400 2150 0    50   ~ 0
Arancio
Text Notes 7400 2250 0    50   ~ 0
Bianco/Arancio
Text Notes 7400 1950 0    50   ~ 0
Verde
Wire Wire Line
	10700 1050 10500 1050
Wire Wire Line
	9650 1050 9800 1050
Wire Wire Line
	9650 1150 9800 1150
$Comp
L LnDevice:sOnOff_Basic K?
U 1 1 5DEED482
P 10150 1200
F 0 "K?" H 10150 1642 50  0000 C CNN
F 1 "sOnOff_Basic" H 10150 1551 50  0000 C CNN
F 2 "sOnOff" H 10250 975 25  0001 L CNN
F 3 "https://standexelectronics.com/wp-content/uploads/datasheet_reed_relay_DIP.pdf" H 10175 1025 50  0001 C CNN
	1    10150 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 1900 10050 1900
Wire Wire Line
	10050 1900 10050 1550
$Comp
L power:+5VA #PWR?
U 1 1 5DF176AA
P 9500 1600
F 0 "#PWR?" H 9500 1450 50  0001 C CNN
F 1 "+5VA" H 9515 1773 50  0000 C CNN
F 2 "" H 9500 1600 50  0001 C CNN
F 3 "" H 9500 1600 50  0001 C CNN
	1    9500 1600
	1    0    0    -1  
$EndComp
$Comp
L LnConnectors:Mammuth_09a MM?
U 1 1 5DF28D2C
P 8150 2150
F 0 "MM?" H 8278 2188 40  0001 L CNN
F 1 "Mammuth_09a" H 8278 2150 40  0001 L CNN
F 2 "" H 8175 2400 60  0000 C CNN
F 3 "" H 8175 2400 60  0000 C CNN
	1    8150 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR?
U 1 1 5DF30D15
P 2850 4250
F 0 "#PWR?" H 2850 4000 50  0001 C CNN
F 1 "GNDA" H 2855 4077 50  0000 C CNN
F 2 "" H 2850 4250 50  0001 C CNN
F 3 "" H 2850 4250 50  0001 C CNN
	1    2850 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DF30D28
P 7850 2750
F 0 "#PWR?" H 7850 2500 50  0001 C CNN
F 1 "GND" H 7855 2577 50  0000 C CNN
F 2 "" H 7850 2750 50  0001 C CNN
F 3 "" H 7850 2750 50  0001 C CNN
	1    7850 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 2750 7850 2550
Wire Wire Line
	7850 2550 8150 2550
Entry Wire Line
	7250 1850 7350 1750
Entry Wire Line
	7250 1950 7350 1850
Entry Wire Line
	7250 2150 7350 2050
Entry Wire Line
	7250 2550 7350 2450
Entry Wire Line
	7250 2350 7350 2250
Text Label 8300 2050 0    50   ~ 0
pumpState
$Comp
L LnDevice:Alimentatore Al_5Vcc?
U 1 1 5DF2F833
P 10100 2700
F 0 "Al_5Vcc?" H 10250 2500 40  0001 R CNN
F 1 "Alimentatore" H 10200 2400 40  0001 R CNN
F 2 "5Vdc" H 10100 2700 60  0000 C CNN
F 3 "" H 10100 2675 60  0000 C CNN
	1    10100 2700
	-1   0    0    -1  
$EndComp
$Comp
L LnDevice:RELAY_1RT K?
U 1 1 5DFA3B23
P 10200 4100
F 0 "K?" H 10225 4518 40  0000 C CNN
F 1 "RELAY_1RT" H 10225 4442 40  0000 C CNN
F 2 "" H 10200 4120 60  0000 C CNN
F 3 "" H 10200 4120 60  0000 C CNN
	1    10200 4100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10500 3600 10500 3850
Wire Wire Line
	10700 3600 10700 4250
Wire Wire Line
	10400 3850 10500 3850
Connection ~ 10500 3850
Wire Wire Line
	10500 3850 10500 5850
Wire Wire Line
	10400 4250 10700 4250
Connection ~ 10700 4250
Wire Wire Line
	10700 4250 10700 5850
Wire Wire Line
	9950 4050 9500 4050
Wire Wire Line
	8150 2250 7350 2250
Wire Wire Line
	8150 2050 7350 2050
Wire Wire Line
	7350 1750 8150 1750
Wire Wire Line
	7350 1850 8150 1850
$Comp
L LnConnectors:Mammuth_09a MM?
U 1 1 5DF5DA63
P 5150 3400
F 0 "MM?" H 5278 3438 40  0001 L CNN
F 1 "Mammuth_09a" H 5278 3400 40  0001 L CNN
F 2 "" H 5175 3650 60  0000 C CNN
F 3 "" H 5175 3650 60  0000 C CNN
	1    5150 3400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DF5DA69
P 4900 3900
F 0 "#PWR?" H 4900 3650 50  0001 C CNN
F 1 "GND" H 4905 3727 50  0000 C CNN
F 2 "" H 4900 3900 50  0001 C CNN
F 3 "" H 4900 3900 50  0001 C CNN
	1    4900 3900
	1    0    0    -1  
$EndComp
Text Notes 7400 2050 0    50   ~ 0
Bianco/Verde
Wire Wire Line
	7350 2450 8150 2450
Entry Wire Line
	6100 3700 6200 3800
Entry Wire Line
	6100 3500 6200 3600
Entry Wire Line
	6100 3300 6200 3400
Entry Wire Line
	6100 3100 6200 3200
Entry Wire Line
	6100 3000 6200 3100
Entry Wire Line
	6100 3200 6200 3300
Entry Wire Line
	6100 3400 6200 3500
Entry Wire Line
	6100 3600 6200 3700
Entry Wire Line
	7250 2450 7350 2350
Entry Wire Line
	7250 2250 7350 2150
Entry Wire Line
	7250 2050 7350 1950
Wire Wire Line
	7350 1950 8150 1950
Wire Wire Line
	7350 2150 8150 2150
Wire Wire Line
	7350 2350 8150 2350
$Comp
L LnDevice:PulsanteNO SW?
U 1 1 5DFEEB6E
P 4300 3850
F 0 "SW?" V 4150 3900 50  0001 C CNN
F 1 "PCButton" V 4400 3700 40  0000 C CNN
F 2 "" H 4300 3850 60  0000 C CNN
F 3 "" H 4300 3850 60  0000 C CNN
	1    4300 3850
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED_ALT D?
U 1 1 5DFEEBE6
P 3150 3700
F 0 "D?" V 3188 3582 50  0001 R CNN
F 1 "PCState" V 3150 3550 50  0000 R CNN
F 2 "" H 3150 3700 50  0001 C CNN
F 3 "~" H 3150 3700 50  0001 C CNN
	1    3150 3700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5DFEEBEC
P 3150 3350
F 0 "R?" H 3218 3396 50  0001 L CNN
F 1 "470" V 3050 3250 50  0000 L CNN
F 2 "" V 3190 3340 50  0001 C CNN
F 3 "~" H 3150 3350 50  0001 C CNN
	1    3150 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 3500 3150 3550
Text Label 9650 1900 0    50   ~ 0
pc_button
Text Label 9900 2100 0    50   ~ 0
pc_GND
Text Label 8350 2450 0    50   ~ 0
pc_button
Wire Wire Line
	9700 2100 10250 2100
Wire Wire Line
	10700 1050 10700 2800
Wire Wire Line
	10500 1150 10500 2600
Wire Wire Line
	9700 2100 9700 2800
Wire Wire Line
	9800 2800 9700 2800
Connection ~ 9700 2800
Wire Wire Line
	9800 2600 9500 2600
Connection ~ 9500 2600
Wire Wire Line
	10400 2600 10500 2600
Connection ~ 10500 2600
Wire Wire Line
	10500 2600 10500 3300
Wire Wire Line
	10400 2800 10700 2800
Connection ~ 10700 2800
Wire Wire Line
	10700 2800 10700 3300
Text Notes 5350 3600 0    50   ~ 0
Celeste
Text Notes 5350 3700 0    50   ~ 0
Bianco/Celeste
Text Notes 5350 3000 0    50   ~ 0
Marrone
Text Notes 5350 3100 0    50   ~ 0
Bianco/Marrone
Text Notes 5350 3400 0    50   ~ 0
Arancio
Text Notes 5350 3500 0    50   ~ 0
Bianco/Arancio
Text Notes 5350 3200 0    50   ~ 0
Verde
Wire Wire Line
	6100 3300 5150 3300
Wire Wire Line
	5150 3000 6100 3000
Wire Wire Line
	5150 3100 6100 3100
Text Notes 5350 3300 0    50   ~ 0
Bianco/Verde
Wire Wire Line
	5150 3200 6100 3200
Wire Wire Line
	5150 3500 6100 3500
Wire Wire Line
	5150 3700 6100 3700
Wire Wire Line
	5150 3400 6100 3400
Wire Wire Line
	5150 3600 6100 3600
Wire Wire Line
	5150 3000 2850 3000
Connection ~ 5150 3000
Wire Wire Line
	5150 3100 3150 3100
Wire Wire Line
	3150 3100 3150 3200
Connection ~ 5150 3100
Wire Wire Line
	2850 3000 2850 4100
Wire Wire Line
	3150 3850 3150 4100
Connection ~ 2850 4100
Wire Wire Line
	2850 4100 2850 4250
Wire Wire Line
	8150 2450 8900 2450
Connection ~ 8150 2450
Wire Wire Line
	9000 2050 8150 2050
Connection ~ 8150 2050
Wire Wire Line
	5150 3700 4300 3700
Wire Wire Line
	4300 3700 4300 3800
Wire Wire Line
	4300 4100 4300 3900
Connection ~ 3150 4100
Wire Wire Line
	2850 4100 3150 4100
Wire Wire Line
	5150 3800 4900 3800
Wire Wire Line
	4900 3800 4900 3900
$Comp
L Device:Buzzer BZ?
U 1 1 5DF25F7B
P 3700 3400
F 0 "BZ?" H 3750 3450 50  0001 C CNN
F 1 "Active-Buzzer" H 3500 3400 50  0000 C CNN
F 2 "" V 3675 3500 50  0001 C CNN
F 3 "~" V 3675 3500 50  0001 C CNN
	1    3700 3400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3800 3300 5150 3300
Connection ~ 5150 3300
Wire Wire Line
	3800 3500 3900 3500
Wire Wire Line
	3900 3500 3900 4100
Connection ~ 3900 4100
Wire Wire Line
	3900 4100 4300 4100
Connection ~ 5150 3700
Wire Wire Line
	3150 4100 3900 4100
Text Label 8450 1750 0    50   ~ 0
GNDA
Text Label 8450 1850 0    50   ~ 0
+5VA
Text Notes 3300 4700 0    50   ~ 10
PCButton:        Press to turn ON/OFF Press-Control\n\nPCState:         Led ON when Press-Control is ON.\n\nActive-Buzzer:   sounds when pump is ON.
$Comp
L LnDevice:Pulse SW?
U 1 1 5DF3BB59
P 4200 3200
F 0 "SW?" H 4050 3300 70  0001 C CNN
F 1 "Pulse" H 4200 3100 70  0001 C CNN
F 2 "" H 4200 3200 60  0000 C CNN
F 3 "" H 4200 3200 60  0000 C CNN
	1    4200 3200
	1    0    0    1   
$EndComp
Text Notes 4300 3300 0    50   ~ 0
+5Vcc
$Comp
L Isolator:PC817 U?
U 1 1 5DF3B278
P 9800 4900
F 0 "U?" H 9800 5225 50  0000 C CNN
F 1 "PC817" H 9800 5134 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 9600 4700 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 9800 4900 50  0001 L CNN
	1    9800 4900
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DF3CE5D
P 10200 4600
F 0 "R?" H 10270 4646 50  0001 L CNN
F 1 "1K" V 10200 4550 50  0000 L CNN
F 2 "" V 10130 4600 50  0001 C CNN
F 3 "~" H 10200 4600 50  0001 C CNN
	1    10200 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR?
U 1 1 5DF3CEF5
P 9400 5100
F 0 "#PWR?" H 9400 4850 50  0001 C CNN
F 1 "GNDA" H 9500 5000 50  0000 C CNN
F 2 "" H 9400 5100 50  0001 C CNN
F 3 "" H 9400 5100 50  0001 C CNN
	1    9400 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR?
U 1 1 5DF3CF08
P 10200 5100
F 0 "#PWR?" H 10200 4850 50  0001 C CNN
F 1 "GNDA" H 10300 5000 50  0000 C CNN
F 2 "" H 10200 5100 50  0001 C CNN
F 3 "" H 10200 5100 50  0001 C CNN
	1    10200 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 4050 9500 4350
Wire Wire Line
	9500 4350 10200 4350
Wire Wire Line
	10200 4350 10200 4450
Connection ~ 9500 4050
Wire Wire Line
	10200 4750 10200 4800
Wire Wire Line
	10200 4800 10100 4800
Wire Wire Line
	10100 5000 10200 5000
Wire Wire Line
	10200 5000 10200 5100
Wire Wire Line
	9500 5000 9400 5000
Wire Wire Line
	9400 5000 9400 5100
$Comp
L power:GNDA #PWR?
U 1 1 5DF4678D
P 2800 6550
F 0 "#PWR?" H 2800 6300 50  0001 C CNN
F 1 "GNDA" H 2805 6377 50  0000 C CNN
F 2 "" H 2800 6550 50  0001 C CNN
F 3 "" H 2800 6550 50  0001 C CNN
	1    2800 6550
	1    0    0    -1  
$EndComp
$Comp
L LnConnectors:Mammuth_09a MM?
U 1 1 5DF46793
P 5100 5700
F 0 "MM?" H 5228 5738 40  0001 L CNN
F 1 "Mammuth_09a" H 5228 5700 40  0001 L CNN
F 2 "" H 5125 5950 60  0000 C CNN
F 3 "" H 5125 5950 60  0000 C CNN
	1    5100 5700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DF46799
P 4850 6200
F 0 "#PWR?" H 4850 5950 50  0001 C CNN
F 1 "GND" H 4855 6027 50  0000 C CNN
F 2 "" H 4850 6200 50  0001 C CNN
F 3 "" H 4850 6200 50  0001 C CNN
	1    4850 6200
	1    0    0    -1  
$EndComp
Entry Wire Line
	6050 6000 6150 6100
Entry Wire Line
	6050 5800 6150 5900
Entry Wire Line
	6050 5600 6150 5700
Entry Wire Line
	6050 5400 6150 5500
Entry Wire Line
	6050 5300 6150 5400
Entry Wire Line
	6050 5500 6150 5600
Entry Wire Line
	6050 5700 6150 5800
Entry Wire Line
	6050 5900 6150 6000
$Comp
L LnDevice:PulsanteNO SW?
U 1 1 5DF467A7
P 4250 6150
F 0 "SW?" V 4100 6200 50  0001 C CNN
F 1 "PCButton" V 4350 6000 40  0000 C CNN
F 2 "" H 4250 6150 60  0000 C CNN
F 3 "" H 4250 6150 60  0000 C CNN
	1    4250 6150
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED_ALT D?
U 1 1 5DF467AD
P 3100 6000
F 0 "D?" V 3138 5882 50  0001 R CNN
F 1 "PCState" V 3100 5850 50  0000 R CNN
F 2 "" H 3100 6000 50  0001 C CNN
F 3 "~" H 3100 6000 50  0001 C CNN
	1    3100 6000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5DF467B3
P 3100 5650
F 0 "R?" H 3168 5696 50  0001 L CNN
F 1 "470" V 3000 5550 50  0000 L CNN
F 2 "" V 3140 5640 50  0001 C CNN
F 3 "~" H 3100 5650 50  0001 C CNN
	1    3100 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 5800 3100 5850
Text Notes 5300 5900 0    50   ~ 0
Celeste
Text Notes 5300 6000 0    50   ~ 0
Bianco/Celeste
Text Notes 5300 5300 0    50   ~ 0
Marrone
Text Notes 5300 5400 0    50   ~ 0
Bianco/Marrone
Text Notes 5300 5700 0    50   ~ 0
Arancio
Text Notes 5300 5800 0    50   ~ 0
Bianco/Arancio
Text Notes 5300 5500 0    50   ~ 0
Verde
Wire Wire Line
	6050 5600 5100 5600
Wire Wire Line
	5100 5300 6050 5300
Wire Wire Line
	5100 5400 6050 5400
Text Notes 5300 5600 0    50   ~ 0
Bianco/Verde
Wire Wire Line
	5100 5500 6050 5500
Wire Wire Line
	5100 5800 6050 5800
Wire Wire Line
	5100 6000 6050 6000
Wire Wire Line
	5100 5700 6050 5700
Wire Wire Line
	5100 5900 6050 5900
Wire Wire Line
	5100 5300 2800 5300
Connection ~ 5100 5300
Wire Wire Line
	5100 5400 3750 5400
Wire Wire Line
	3100 5400 3100 5500
Connection ~ 5100 5400
Wire Wire Line
	2800 5300 2800 6400
Wire Wire Line
	3100 6150 3100 6400
Connection ~ 2800 6400
Wire Wire Line
	2800 6400 2800 6550
Wire Wire Line
	5100 6000 4250 6000
Wire Wire Line
	4250 6000 4250 6100
Wire Wire Line
	4250 6400 4250 6200
Connection ~ 3100 6400
Wire Wire Line
	2800 6400 3100 6400
Wire Wire Line
	5100 6100 4850 6100
Wire Wire Line
	4850 6100 4850 6200
$Comp
L Device:Buzzer BZ?
U 1 1 5DF467DA
P 3650 5700
F 0 "BZ?" H 3700 5750 50  0001 C CNN
F 1 "Active-Buzzer" H 3450 5700 50  0000 C CNN
F 2 "" V 3625 5800 50  0001 C CNN
F 3 "~" V 3625 5800 50  0001 C CNN
	1    3650 5700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3750 5800 4200 5800
Connection ~ 5100 6000
Text Notes 3250 7000 0    50   ~ 10
PCButton:        Press to turn ON/OFF Press-Control\n\nPCState:         Led ON when Press-Control is ON.\n\nActive-Buzzer:   sounds when pump is ON.
Text Notes 4050 5400 0    50   ~ 0
+5Vcc
Wire Wire Line
	3750 5600 3750 5400
Connection ~ 3750 5400
Wire Wire Line
	3750 5400 3100 5400
Wire Wire Line
	3100 6400 4250 6400
Wire Wire Line
	4200 5800 4200 5600
Wire Wire Line
	4200 5600 5100 5600
Connection ~ 5100 5600
Wire Wire Line
	9200 4800 9500 4800
$Comp
L LnDevice:Jumper3_B SW?
U 1 1 5DF59A4E
P 9200 4350
F 0 "SW?" V 9200 4451 50  0001 L CNN
F 1 "Jumper3_B" V 9245 4451 50  0001 L CNN
F 2 "" H 9150 4470 60  0000 C CNN
F 3 "" H 9150 4470 60  0000 C CNN
	1    9200 4350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9000 2050 9000 4350
Wire Wire Line
	9000 4350 9150 4350
Wire Wire Line
	9200 4450 9200 4800
Wire Wire Line
	9200 4250 9200 4150
Wire Wire Line
	9200 4150 10050 4150
Wire Notes Line
	2050 5000 8650 5000
Wire Notes Line
	8650 5000 8650 4400
Wire Notes Line
	8650 4400 10900 4400
Wire Notes Line
	10900 4400 10900 5550
Wire Notes Line
	10900 5550 6650 5550
Wire Notes Line
	6650 5550 6650 7300
Wire Notes Line
	6650 7300 2050 7300
Wire Notes Line
	2050 7300 2050 5000
Wire Wire Line
	8900 1900 8900 2450
Wire Wire Line
	9700 2800 9700 3200
Wire Wire Line
	9500 2600 9500 4050
Wire Wire Line
	8150 1850 9500 1850
Wire Wire Line
	9500 1600 9500 1850
Connection ~ 8150 1850
Connection ~ 9500 1850
Wire Wire Line
	9500 1850 9500 2600
Wire Wire Line
	8800 1750 8150 1750
Connection ~ 8150 1750
Wire Notes Line
	2050 2750 6700 2750
Wire Notes Line
	6700 2750 6700 3650
Wire Notes Line
	6700 3650 11050 3650
Wire Notes Line
	11050 3650 11050 4350
Wire Notes Line
	11050 4350 6750 4350
Wire Notes Line
	6750 4350 6750 4800
Wire Notes Line
	6750 4800 2050 4800
Wire Notes Line
	2050 4800 2050 2750
Wire Bus Line
	7250 1600 7250 2850
Wire Bus Line
	6200 2850 6200 4100
Wire Bus Line
	6150 5150 6150 6400
Text Notes 2200 2900 0    100  ~ 20
Solution 1
Text Notes 2200 5200 0    100  ~ 20
Solution 2
$EndSCHEMATC
