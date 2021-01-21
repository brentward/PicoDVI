EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "HyperRAM PMOD"
Date "2020-08-19"
Rev "A"
Comp "Luke Wren"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L picodvi:S70KS128 U1
U 1 1 5F3DDDDC
P 6850 3550
F 0 "U1" H 6850 4515 50  0000 C CNN
F 1 "S70KS128" H 6850 4424 50  0000 C CNN
F 2 "picodvi:S70KS128" H 6800 4900 50  0001 C CNN
F 3 "" H 6800 4900 50  0001 C CNN
	1    6850 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x06_Odd_Even J2
U 1 1 5F3DDEB5
P 4000 4900
F 0 "J2" H 4050 4375 50  0000 C CNN
F 1 "2.54mm_2x6" H 4050 4466 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x06_P2.54mm_Horizontal" H 4000 4900 50  0001 C CNN
F 3 "~" H 4000 4900 50  0001 C CNN
	1    4000 4900
	-1   0    0    1   
$EndComp
Wire Wire Line
	7200 2850 7300 2850
Wire Wire Line
	7200 2950 7300 2950
Wire Wire Line
	7200 3050 7300 3050
Wire Wire Line
	7200 3150 7300 3150
Wire Wire Line
	7200 3250 7300 3250
Wire Wire Line
	7200 3350 7300 3350
Wire Wire Line
	7200 3450 7300 3450
Wire Wire Line
	7200 3550 7300 3550
Text Label 7300 2850 0    50   ~ 0
DQ0
Text Label 7300 2950 0    50   ~ 0
DQ1
Text Label 7300 3050 0    50   ~ 0
DQ2
Text Label 7300 3150 0    50   ~ 0
DQ3
Text Label 7300 3250 0    50   ~ 0
DQ4
Text Label 7300 3350 0    50   ~ 0
DQ5
Text Label 7300 3450 0    50   ~ 0
DQ6
Text Label 7300 3550 0    50   ~ 0
DQ7
Wire Wire Line
	4200 4800 4300 4800
Wire Wire Line
	4200 4900 4300 4900
Wire Wire Line
	4200 5000 4300 5000
Wire Wire Line
	4200 5100 4300 5100
Wire Wire Line
	3600 4800 3700 4800
Wire Wire Line
	3600 4900 3700 4900
Wire Wire Line
	3600 5000 3700 5000
Wire Wire Line
	3600 5100 3700 5100
Text Label 4300 5100 0    50   ~ 0
DQ0
Text Label 4300 5000 0    50   ~ 0
DQ1
Text Label 4300 4900 0    50   ~ 0
DQ2
Text Label 4300 4800 0    50   ~ 0
DQ3
Text Label 3600 5100 2    50   ~ 0
DQ4
Text Label 3600 5000 2    50   ~ 0
DQ5
Text Label 3600 4900 2    50   ~ 0
DQ6
Text Label 3600 4800 2    50   ~ 0
DQ7
Wire Wire Line
	4200 4700 4250 4700
Wire Wire Line
	4250 4700 4250 5300
$Comp
L power:GND #PWR0101
U 1 1 5F3DE7EC
P 4250 5300
F 0 "#PWR0101" H 4250 5050 50  0001 C CNN
F 1 "GND" H 4255 5127 50  0000 C CNN
F 2 "" H 4250 5300 50  0001 C CNN
F 3 "" H 4250 5300 50  0001 C CNN
	1    4250 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 4600 4250 4600
Wire Wire Line
	4250 4600 4250 4350
Wire Wire Line
	3700 4600 3650 4600
Wire Wire Line
	3650 4600 3650 4350
$Comp
L power:+3V3 #PWR0102
U 1 1 5F3DEEF6
P 3650 4350
F 0 "#PWR0102" H 3650 4200 50  0001 C CNN
F 1 "+3V3" H 3665 4523 50  0000 C CNN
F 2 "" H 3650 4350 50  0001 C CNN
F 3 "" H 3650 4350 50  0001 C CNN
	1    3650 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0103
U 1 1 5F3DEF14
P 4250 4350
F 0 "#PWR0103" H 4250 4200 50  0001 C CNN
F 1 "+3V3" H 4265 4523 50  0000 C CNN
F 2 "" H 4250 4350 50  0001 C CNN
F 3 "" H 4250 4350 50  0001 C CNN
	1    4250 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 4700 3650 4700
Wire Wire Line
	3650 4700 3650 5300
$Comp
L power:GND #PWR0104
U 1 1 5F3DF31B
P 3650 5300
F 0 "#PWR0104" H 3650 5050 50  0001 C CNN
F 1 "GND" H 3655 5127 50  0000 C CNN
F 2 "" H 3650 5300 50  0001 C CNN
F 3 "" H 3650 5300 50  0001 C CNN
	1    3650 5300
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x06_Odd_Even J1
U 1 1 5F3DF38F
P 4000 3250
F 0 "J1" H 4050 2725 50  0000 C CNN
F 1 "2.54mm_2x6" H 4050 2816 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x06_P2.54mm_Horizontal" H 4000 3250 50  0001 C CNN
F 3 "~" H 4000 3250 50  0001 C CNN
	1    4000 3250
	-1   0    0    1   
$EndComp
Wire Wire Line
	4200 3150 4300 3150
Wire Wire Line
	4200 3250 4300 3250
Wire Wire Line
	4200 3350 4300 3350
Wire Wire Line
	4200 3450 4300 3450
Wire Wire Line
	3600 3450 3700 3450
Wire Wire Line
	4200 3050 4250 3050
Wire Wire Line
	4250 3050 4250 3650
$Comp
L power:GND #PWR0105
U 1 1 5F3DF3A8
P 4250 3650
F 0 "#PWR0105" H 4250 3400 50  0001 C CNN
F 1 "GND" H 4255 3477 50  0000 C CNN
F 2 "" H 4250 3650 50  0001 C CNN
F 3 "" H 4250 3650 50  0001 C CNN
	1    4250 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 2950 4250 2950
Wire Wire Line
	4250 2950 4250 2700
Wire Wire Line
	3700 2950 3650 2950
Wire Wire Line
	3650 2950 3650 2700
$Comp
L power:+3V3 #PWR0106
U 1 1 5F3DF3B2
P 3650 2700
F 0 "#PWR0106" H 3650 2550 50  0001 C CNN
F 1 "+3V3" H 3665 2873 50  0000 C CNN
F 2 "" H 3650 2700 50  0001 C CNN
F 3 "" H 3650 2700 50  0001 C CNN
	1    3650 2700
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0107
U 1 1 5F3DF3B8
P 4250 2700
F 0 "#PWR0107" H 4250 2550 50  0001 C CNN
F 1 "+3V3" H 4265 2873 50  0000 C CNN
F 2 "" H 4250 2700 50  0001 C CNN
F 3 "" H 4250 2700 50  0001 C CNN
	1    4250 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 3050 3650 3050
Wire Wire Line
	3650 3050 3650 3650
$Comp
L power:GND #PWR0108
U 1 1 5F3DF3C0
P 3650 3650
F 0 "#PWR0108" H 3650 3400 50  0001 C CNN
F 1 "GND" H 3655 3477 50  0000 C CNN
F 2 "" H 3650 3650 50  0001 C CNN
F 3 "" H 3650 3650 50  0001 C CNN
	1    3650 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3750 7300 3750
Wire Wire Line
	7200 3850 7300 3850
Wire Wire Line
	7200 4050 7300 4050
Wire Wire Line
	7200 4250 7300 4250
Text Label 7300 3750 0    50   ~ 0
~CK~
Text Label 7300 3850 0    50   ~ 0
CK
Text Label 7300 3950 0    50   ~ 0
~CS~
Text Label 7300 4050 0    50   ~ 0
RWDS
Text Label 7300 4250 0    50   ~ 0
~RST~
Wire Wire Line
	6500 2850 6350 2850
Wire Wire Line
	6350 2850 6350 2600
$Comp
L power:+3V3 #PWR0109
U 1 1 5F3E24FA
P 6350 2600
F 0 "#PWR0109" H 6350 2450 50  0001 C CNN
F 1 "+3V3" H 6365 2773 50  0000 C CNN
F 2 "" H 6350 2600 50  0001 C CNN
F 3 "" H 6350 2600 50  0001 C CNN
	1    6350 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 2950 6350 2950
Wire Wire Line
	6350 2950 6350 2850
Connection ~ 6350 2850
Wire Wire Line
	6350 2950 6350 3350
Wire Wire Line
	6350 3350 6500 3350
Connection ~ 6350 2950
Wire Wire Line
	6500 3050 6400 3050
Wire Wire Line
	6400 3050 6400 3150
$Comp
L power:GND #PWR0110
U 1 1 5F3E5242
P 6400 4450
F 0 "#PWR0110" H 6400 4200 50  0001 C CNN
F 1 "GND" H 6405 4277 50  0000 C CNN
F 2 "" H 6400 4450 50  0001 C CNN
F 3 "" H 6400 4450 50  0001 C CNN
	1    6400 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 3150 6400 3150
Connection ~ 6400 3150
Wire Wire Line
	6400 3150 6400 3450
Wire Wire Line
	6500 3450 6400 3450
Connection ~ 6400 3450
Wire Wire Line
	6400 3450 6400 4450
Wire Wire Line
	7700 3950 7700 3850
Wire Wire Line
	7200 3950 7700 3950
$Comp
L Device:R R1
U 1 1 5F3EBAFE
P 7700 3700
F 0 "R1" H 7770 3746 50  0000 L CNN
F 1 "4k7" H 7770 3655 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7630 3700 50  0001 C CNN
F 3 "~" H 7700 3700 50  0001 C CNN
	1    7700 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3550 7700 3450
$Comp
L power:+3V3 #PWR0111
U 1 1 5F3ECD1E
P 7700 3450
F 0 "#PWR0111" H 7700 3300 50  0001 C CNN
F 1 "+3V3" H 7715 3623 50  0000 C CNN
F 2 "" H 7700 3450 50  0001 C CNN
F 3 "" H 7700 3450 50  0001 C CNN
	1    7700 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5F3ECD7E
P 5900 2850
F 0 "C3" H 6015 2896 50  0000 L CNN
F 1 "100n" H 6015 2805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5938 2700 50  0001 C CNN
F 3 "~" H 5900 2850 50  0001 C CNN
	1    5900 2850
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0112
U 1 1 5F3ECDFD
P 5900 2600
F 0 "#PWR0112" H 5900 2450 50  0001 C CNN
F 1 "+3V3" H 5915 2773 50  0000 C CNN
F 2 "" H 5900 2600 50  0001 C CNN
F 3 "" H 5900 2600 50  0001 C CNN
	1    5900 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5F3ECEDB
P 5900 3100
F 0 "#PWR0113" H 5900 2850 50  0001 C CNN
F 1 "GND" H 5905 2927 50  0000 C CNN
F 2 "" H 5900 3100 50  0001 C CNN
F 3 "" H 5900 3100 50  0001 C CNN
	1    5900 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 3100 5900 3000
Wire Wire Line
	5900 2700 5900 2600
$Comp
L Device:C C2
U 1 1 5F3EF315
P 5500 2850
F 0 "C2" H 5615 2896 50  0000 L CNN
F 1 "100n" H 5615 2805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5538 2700 50  0001 C CNN
F 3 "~" H 5500 2850 50  0001 C CNN
	1    5500 2850
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0114
U 1 1 5F3EF31C
P 5500 2600
F 0 "#PWR0114" H 5500 2450 50  0001 C CNN
F 1 "+3V3" H 5515 2773 50  0000 C CNN
F 2 "" H 5500 2600 50  0001 C CNN
F 3 "" H 5500 2600 50  0001 C CNN
	1    5500 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5F3EF322
P 5500 3100
F 0 "#PWR0115" H 5500 2850 50  0001 C CNN
F 1 "GND" H 5505 2927 50  0000 C CNN
F 2 "" H 5500 3100 50  0001 C CNN
F 3 "" H 5500 3100 50  0001 C CNN
	1    5500 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3100 5500 3000
Wire Wire Line
	5500 2700 5500 2600
$Comp
L Device:C C1
U 1 1 5F3F0612
P 5100 2850
F 0 "C1" H 5215 2896 50  0000 L CNN
F 1 "100n" H 5215 2805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5138 2700 50  0001 C CNN
F 3 "~" H 5100 2850 50  0001 C CNN
	1    5100 2850
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0116
U 1 1 5F3F0619
P 5100 2600
F 0 "#PWR0116" H 5100 2450 50  0001 C CNN
F 1 "+3V3" H 5115 2773 50  0000 C CNN
F 2 "" H 5100 2600 50  0001 C CNN
F 3 "" H 5100 2600 50  0001 C CNN
	1    5100 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 5F3F061F
P 5100 3100
F 0 "#PWR0117" H 5100 2850 50  0001 C CNN
F 1 "GND" H 5105 2927 50  0000 C CNN
F 2 "" H 5100 3100 50  0001 C CNN
F 3 "" H 5100 3100 50  0001 C CNN
	1    5100 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 3100 5100 3000
Wire Wire Line
	5100 2700 5100 2600
Text Notes 5100 3450 0    50   ~ 0
One cap per supply pin
Text Notes 8000 3800 0    50   ~ 0
Datasheet says ~CS~ *must* be pulled high at power-on.\nNo such restriction on ~RST~, so rely on default state from other side
NoConn ~ 3700 3150
NoConn ~ 3700 3250
NoConn ~ 3700 3350
Text Label 4300 3150 0    50   ~ 0
~CK~
Text Label 4300 3250 0    50   ~ 0
CK
Text Label 4300 3350 0    50   ~ 0
RWDS
Text Label 4300 3450 0    50   ~ 0
~CS~
Text Label 3600 3450 2    50   ~ 0
~RST~
$EndSCHEMATC