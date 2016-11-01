#ifndef __WINDOW_ID__
#define __WINDOW_ID__

#define WINDOW_0  0   //meniu principal
#define WINDOW_1  1   //alege numar bucati
#define WINDOW_2  2   //alege lungime bucata
#define WINDOW_3  3   //PRELUCRARE material
#define WINDOW_4  4   //introducere parola
#define WINDOW_5  5   //fereastra de configurari
#define WINDOW_6  6   //calibrare encoder
#define WINDOW_7  7   //schimbare parola - introdu parola curenta
#define WINDOW_8  8   //schimbare parola - introdu parola noua
#define WINDOW_9  9   //status incheiere prelucrare EROARE/INCHEIERE FORTATA (cat s-a taiat din cat, inchidere automata/fortata, revenire/continuare)
#define WINDOW_10 10  //verificare manuala a subcomponentelor
#define WINDOW_11 11  //finalizare activitate SUCCES
#define WINDOW_12 12  //alege valoare impulsuri pentru lungimea specificata
#define WINDOW_13 13  //vectorul de calibrare
#define WINDOW_14 14  //test encoder
#define WINDOW_15 15  //test presa
#define WINDOW_16 16  //test electromagnet
#define WINDOW_17 17  //test intrare material
#define WINDOW_18 18  //test senzor iesire material
#define WINDOW_19 19  //test de executie completa 1/2 bucati

//window 0
#define ID_BUT_BUCATI   100
#define ID_BUT_LUNGIME  101
#define ID_BUT_CONFIG   102
#define ID_BUT_START    103
#define ID_LAB_NRB1     104
#define ID_LAB_LUNG1    105
#define ID_MAIN_TITLE   106

//window 1
#define ID_TITLE_MANUAL        200
#define ID_LABEL_BASE_PWM      201
#define ID_LABEL_ADJUST_PWM    202
#define ID_LABEL_BASE_SPEED    203
#define ID_LABEL_ADJUST_SPEED  204
#define ID_BUT_MOVE_LEFT       205
#define ID_BUT_MOVE_RIGHT      206
#define ID_BUT_RENUNTA1        207
#define ID_CONFIG_WIN          208
#define ID_EN_PWM							 209
#define ID_DIS_PWM				     210
#define ID_EN_DRV              211
#define ID_DIS_DRV             212
#define ID_EN_RST							 213
#define ID_DIS_RST						 214
#define ID_EN_SLP							 215
#define ID_DIS_SLP						 216
#define ID_ONE_STEP					   217
#define ID_STEP_INC						 218
#define ID_STEP_DEC						 219
#define ID_STEP_DIR						 220
#define ID_LAB_speed           221
#define ID_LAB_dir4            222
#define ID_LAB_mode						 223
#define ID_LAB_stepping        224

#define ID_TITLE_MANUAL2			 250
#define ID_CONFIG_WIN2				 251
#define ID_BUT_RENUNTA2				 252
#define ID_SLIDER							 253

//window 2
#define ID_LAB_LUNG2    300
#define ID_EDT_BOX2     301
#define ID_BUT_ACCEPTA2 302
#define ID_BUT_RENUNTA2 303
#define ID_BUT_FIRSTC2  304
#define ID_S200         305
#define ID_S400         306
#define ID_S800         307
#define ID_S1600        308
#define ID_S3200        309
#define ID_LAB_srev     310

//window 4
#define ID_LAB_SIM  		 400
#define ID_SIM_AUTO   	 401
#define ID_SIM_MANUAL    402
#define ID_BUT_SIMR   	 403


//window 3
#define ID_LAB_AUTO3      500
#define ID_BUT_AUTO_BACK3 501
#define ID_AUTO_LIST3     502
#define ID_LAB_dir				503
#define ID_LAB_step1  		504
#define ID_LAB_step2		  505
#define ID_LAB_step3		  506
#define ID_LAB_step4		  507
#define ID_LAB_step5		  508
#define ID_LAB_pwm_freq   509
#define ID_LAB_dir2				510
#define ID_LAB_dir3				511
#define ID_LAB_step6		  512
#define ID_LAB_step7		  513
#define ID_LAB_step8		  514
#define ID_LAB_step9		  515
#define ID_LAB_step10		  516
#define ID_LAB_pwm_facto  517
#define ID_LAB_step2_nr		  518
#define ID_LAB_pwm_freq_nr	519
#define ID_LAB_pwm_facto_nr	520


//window 5
#define ID_LAB_SETARI   600
#define ID_BUT_REVENIRE 601
#define ID_BUT_CALIBT   602
#define ID_BUT_CALIBE   603
#define ID_BUT_CHPWD    604
#define ID_BUT_ISTORIC  605
#define ID_SENS0        606
#define ID_SENS1        607
#define ID_SENS2        608
#define ID_SENS3        609
#define ID_SENS4        610
#define ID_SENS5        611
#define ID_SENS00       612
#define ID_SENS11       613
#define ID_SENS22       614
#define ID_SENS33       615
#define ID_SENS44       616
#define ID_SENS55       617
#define ID_MDRT         618
#define ID_MSTG					619
#define ID_BUT_TRD      620
#define ID_BUT_TRS      621

//window 6
#define ID_LAB_TFING    700
#define ID_ADC1  			  701
#define ID_ADC2 				702
#define ID_NADC1 				703
#define ID_NADC2  			704
#define ID_BUT_REV_TC  	705
#define ID_COMBS        706
#define ID_COMBD 				707
#define ID_C01          708
#define ID_C02          709
#define ID_C03          710
#define ID_C04          711
#define ID_C05          712
#define ID_C06          713
#define ID_C11          714
#define ID_C12          715
#define ID_C13          716
#define ID_C14          717
#define ID_C15          718
#define ID_C16          719

//window 7
#define ID_VECT_DRT     800
#define ID_BUT_REV_VD   801
#define ID_LAB_S0       802
#define ID_LAB_S1       803
#define ID_LAB_S2       804
#define ID_EDT_S0       805
#define ID_EDT_S1       806
#define ID_EDT_S2       807


//window 8
#define ID_VECT_STG   	900
#define ID_BUT_REV_VS   901
#define ID_LAB_S3   		902
#define ID_LAB_S4       903
#define ID_LAB_S5       904
#define ID_EDT_S3       905
#define ID_EDT_S4       906
#define ID_EDT_S5       907


//window 9
#define ID_LAB_AUTO      1001
#define ID_BUT_AUTO_BACK 1002
#define ID_AUTO_LIST     1003

//window 10
#define ID_LAB_MAN      1100
#define ID_BUT_MAN_BACK 1101

//window 9
#define ID_LAB_STOPM    1301
#define ID_LAB_STOPBT   1302
#define ID_BUT_REIA     1303
#define ID_BUT_STOPFULL 1304
#define ID_LAB_STOPM2   1305
#define ID_LAB_STOPM3   1306
#define ID_LAB_STOPM4   1307

//window 11
#define ID_LAB_SUCCESS  1401
#define ID_LAB_SUCCINF  1402
#define ID_LAB_SUCCREV  1403

//window 14
#define ID_LAB_ENCT     1500
#define ID_TEXT_ENC     1501
#define ID_BUT_EBACK    1502
#define ID_BUT_ERESET   1503

//window 15
#define ID_LAB_PRESA    1600
#define ID_BUT_CICSI    1601
#define ID_BUT_CICCU    1602
#define ID_BUT_CIREV    1603
#define ID_BUT_SUPA1    1604
#define ID_BUT_SUPA2    1605
#define ID_LAB_ROTB1    1606

//window 16
#define ID_LAB_ELEMG    1700
#define ID_BUT_PISTONI  1701
#define ID_BUT_PISTONT  1702
#define ID_BUT_ELEMGI   1703
#define ID_BUT_ELEMGT   1704
#define ID_BUT_ELEREV   1705

//window 17
#define ID_LAB_MOTOR    1800
#define ID_BUT_MOTORAC  1801
#define ID_BUT_MOTORST  1802
#define ID_BUT_MOTOR1S  1803
#define ID_BUT_MOTOR3S  1804
#define ID_BUT_MOTORBK  1805

//window 18
#define ID_LAB_SENZMAT  1900
#define ID_LAB_SENZOIM  1901
#define ID_LAB_SENZDIN  1902
#define ID_BUT_SENZREV  1903

//window 19
#define ID_LAB_EXECUTA  2000
#define ID_BUT_EXE1B20  2001
#define ID_BUT_EXE3B20  2002
#define ID_BUT_EXE1B40  2003
#define ID_BUT_EXE3B40  2004
#define ID_BUT_EXECREV  2005


#endif