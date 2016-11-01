#include "EventMethods.h"
#include "SSD1289_TouchScreen/TouchPanel.h"
#include "pinout.h"
#include "usart/uartlib.h"
#include "adc.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_pwm.h"

int numar_bucati;
int lungime_buc;
int bucata_curenta;
int hours_left;
int minutes_left;
int seconds_left;
bool job_start;
bool enc_test;
int senzor_rotatie_presa;
int senzor_material_iesire;
double lensum;
int error_mode;
int old_adc_vals[2];
int comb_ids[2][6]={{ID_C01,ID_C02,ID_C03,ID_C04,ID_C05,ID_C06},
										{ID_C11,ID_C12,ID_C13,ID_C14,ID_C15,ID_C16}};
extern int Ssens[3];
extern int Dsens[3];
int bucati_predefinite[20]={50,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
int lungimi_predefinite[20]={10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
int vector_impulsuri[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int index_impulsuri;

int password[6]={'0','0','0','0','0','0'};   // parola este defapt NARCIS scris pe tastele de la un telefon care are 3 litere pe tasta

extern vu16 adc_vals[2];

int pwm_procent=50;
int pwm_frecventa=30000;
int steptime=1000;

//-----------------------------------------------callback tastatura virtuala predefinita--------------------------------------------------------------------
void mini_predefined_keyboard(void *interfata)
{
        
}
//----------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------adauga tastatura virtuala----------------------------------------------------------------
void AddPredefinedButtons(GUI *gui,int first_ID,OnEvent proc,int *label_vector,int window)
{

}

void AddPredefinedButtonsPWD(GUI *gui,int first_ID,OnEvent proc,int window)
{

}
//-------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------alocare componente pentru ferestre---------------------------------------------------------------
void InitWindow(GUI *gui,int window)
{
  char data[50];
	SSD1289_LCD *lcd=gui->GetLCD();
	char *comb[2][6]={{"D1","D2","D3","D4","D5","D6"},
										{"S1","S2","S3","S4","S5","S6"}};
	int i;
    
	printf("Init Window [%d]\r\n",window);
	
    switch (window)
    {
        case WINDOW_0:
                //init fereastra 0  - meniu principal
								GUIComponent *label_titlu=new Label(lcd,NULL,0,0,319,40,"Calibrare Stepper",(font_t*)&TerminusBigFont,COLOR_DARK_BLUE,COLOR_LIGHT_GRAY,ID_MAIN_TITLE);															
								GUIComponent *button_calibrare=new Button(lcd,usart_interface,5,60,150,80,"USART",(font_t*)&TerminusBigFont,COLOR_LIGHT_BLUE,ID_BUT_BUCATI);               
								GUIComponent *button_testare=new Button(lcd,manual_config,5,150,150,80,"MANUAL",(font_t*)&TerminusBigFont,COLOR_ORANGE,ID_BUT_LUNGIME);
								GUIComponent *button_simulare=new Button(lcd,auto_config,165,150,150,80,"AUTO",(font_t*)&TerminusBigFont,COLOR_LIME,ID_BUT_START);
								GUIComponent *button_live=new Button(lcd,motor_test,165,60,150,80,"TEST",(font_t*)&TerminusBigFont,COLOR_LIGHT_YELLOW,ID_BUT_CONFIG);
								gui->AddComponent(label_titlu,WINDOW_0);
								gui->AddComponent(button_calibrare,WINDOW_0);
								gui->AddComponent(button_testare,WINDOW_0);
								gui->AddComponent(button_simulare,WINDOW_0);
								gui->AddComponent(button_live,WINDOW_0);    
            break;
        case WINDOW_1:                                
                //init fereastra 1 - manual config
                GUIComponent *label_testare=new Label(lcd,NULL,0,0,319,40,"Configurare Manuala",(font_t*)&TerminusBigFont,COLOR_BLACK,COLOR_LIGHT_GRAY,ID_TITLE_MANUAL);								
								GUIComponent *conf_win=new Button(lcd,configs,275,45,40,145,">",(font_t*)&TerminusBigFont,COLOR_PINK,ID_CONFIG_WIN);
								
								GUIComponent *PWM_enable=new Button(lcd,enpwm,5,45,72,32,"Auto",(font_t*)&Font8x16,COLOR_YELLOW,ID_EN_PWM);
								GUIComponent *PWM_disable=new Button(lcd,dispwm,5,82,72,32,"Manual",(font_t*)&Font8x16,COLOR_YELLOW,ID_DIS_PWM);
								GUIComponent *DRV_enable=new Button(lcd,endrv,5,119,72,32,"Enable",(font_t*)&Font8x16,COLOR_LIME,ID_EN_DRV);
								GUIComponent *DRV_disable=new Button(lcd,disdrv,5,156,72,32,"Disable",(font_t*)&Font8x16,COLOR_LIME,ID_DIS_DRV);
												
								GUIComponent *single_step=new Button(lcd,onestep,159,45,111,32,"STEP",(font_t*)&Font8x16,COLOR_LIGHT_GRAY,ID_ONE_STEP);								
								GUIComponent *inc_speed=new Button(lcd,incspeed,159,82,111,32,"SPEED++",(font_t*)&Font8x16,COLOR_WHITE,ID_STEP_INC);								
								GUIComponent *dec_speed=new Button(lcd,decspeed,159,119,111,32,"SPEED--",(font_t*)&Font8x16,COLOR_WHITE,ID_STEP_DEC);								
								GUIComponent *dir=new Button(lcd,direction,159,156,111,32,"Left/Right",(font_t*)&Font8x16,COLOR_WHITE,ID_STEP_DIR);		

								GUIComponent *label_speed=new Label(lcd,NULL,82,45,72,32,"100",(font_t*)&Font8x16,COLOR_WHITE,COLOR_ORANGE,ID_LAB_speed,_CENTER);
								GUIComponent *label_dir4=new Label(lcd,NULL,82,82,72,32,"Left",(font_t*)&Font8x16,COLOR_WHITE,COLOR_ORANGE,ID_LAB_dir4,_CENTER);
								GUIComponent *label_mode=new Label(lcd,NULL,82,119,72,32,"Auto",(font_t*)&Font8x16,COLOR_WHITE,COLOR_ORANGE,ID_LAB_mode,_CENTER);
								GUIComponent *label_stepping=new Label(lcd,NULL,82,156,72,32,"200",(font_t*)&Font8x16,COLOR_WHITE,COLOR_ORANGE,ID_LAB_stepping,_CENTER);
								
                GUIComponent *test_back=new Button(lcd,testare_back,85,195,150,35,"REVENIRE",(font_t*)&TerminusBigFont,COLOR_LIGHT_RED,ID_BUT_RENUNTA1);								

								gui->AddComponent(label_testare,WINDOW_1);
								gui->AddComponent(conf_win,WINDOW_1);
								gui->AddComponent(PWM_enable,WINDOW_1);
								gui->AddComponent(PWM_disable,WINDOW_1);
								gui->AddComponent(DRV_disable,WINDOW_1);
								gui->AddComponent(DRV_enable,WINDOW_1);		
								gui->AddComponent(single_step,WINDOW_1);	
								gui->AddComponent(inc_speed,WINDOW_1);	
								gui->AddComponent(dec_speed,WINDOW_1);	
								gui->AddComponent(dir,WINDOW_1);
								gui->AddComponent(test_back,WINDOW_1);
								gui->AddComponent(label_speed,WINDOW_1);
								gui->AddComponent(label_dir4,WINDOW_1);
								gui->AddComponent(label_mode,WINDOW_1);
								gui->AddComponent(label_stepping,WINDOW_1);
            break;
        case WINDOW_2:                         
                //init fereastra 2 - help config
                GUIComponent *label_testare2=new Label(lcd,NULL,0,0,319,40,"Configurare Manuala",(font_t*)&TerminusBigFont,COLOR_BLACK,COLOR_LIGHT_GRAY,ID_TITLE_MANUAL2);								
								GUIComponent *conf_win2=new Button(lcd,configs2,5,45,40,145,"<",(font_t*)&TerminusBigFont,COLOR_PINK,ID_CONFIG_WIN2);
								
								GUIComponent *test_back2=new Button(lcd,testare_back2,85,195,150,35,"REVENIRE",(font_t*)&TerminusBigFont,COLOR_LIGHT_RED,ID_BUT_RENUNTA2);								
								
								GUIComponent *label_tit_steps=new Label(lcd,NULL,50,45,260,17,"Steps / Revolution",(font_t*)&Font8x16,COLOR_BLACK,COLOR_WHITE,ID_LAB_srev,_CENTER);
								GUIComponent *Step_200=new Button(lcd,s200,50,65,50,32,"200",(font_t*)&Font8x16,COLOR_YELLOW,ID_S200);
								GUIComponent *Step_400=new Button(lcd,s400,103,65,50,32,"400",(font_t*)&Font8x16,COLOR_YELLOW,ID_S400);
								GUIComponent *Step_800=new Button(lcd,s800,156,65,50,32,"800",(font_t*)&Font8x16,COLOR_YELLOW,ID_S800);
								GUIComponent *Step_1600=new Button(lcd,s1600,209,65,50,32,"1600",(font_t*)&Font8x16,COLOR_YELLOW,ID_S1600);
								GUIComponent *Step_3200=new Button(lcd,s3200,262,65,50,32,"3200",(font_t*)&Font8x16,COLOR_YELLOW,ID_S3200);								
								
								gui->AddComponent(label_testare2,WINDOW_2);
								gui->AddComponent(conf_win2,WINDOW_2);
								gui->AddComponent(test_back2,WINDOW_2);
								gui->AddComponent(Step_200,WINDOW_2);				
								gui->AddComponent(Step_400,WINDOW_2);				
								gui->AddComponent(Step_800,WINDOW_2);				
								gui->AddComponent(Step_1600,WINDOW_2);				
								gui->AddComponent(Step_3200,WINDOW_2);									
								gui->AddComponent(label_tit_steps,WINDOW_2);	
						break;
        case WINDOW_3:                  
                //init fereastra 3 - PLAY LIVE
                GUIComponent *label_auto3=new Label(lcd,NULL,0,0,319,40,"USART PC Interface",(font_t*)&TerminusBigFont,COLOR_WHITE,COLOR_BLUE,ID_LAB_AUTO3);                
                GUIComponent *auto_back3=new Button(lcd,back_from_play,85,195,150,35,"REVENIRE",(font_t*)&TerminusBigFont,COLOR_LIGHT_RED,ID_BUT_AUTO_BACK3);	
								
								GUIComponent *label_dir=new Label(lcd,NULL,10,45,32,20,"Dir:",(font_t*)&Font8x16,COLOR_BLACK,COLOR_CYAN,ID_LAB_dir,_LEFT);
								GUIComponent *label_dir2=new Label(lcd,NULL,100,45,50,16,"  <  ",(font_t*)&Font8x16,COLOR_WHITE,COLOR_DARK_GREEN,ID_LAB_dir2,_LEFT);
								GUIComponent *label_dir3=new Label(lcd,NULL,160,45,50,16,"  >  ",(font_t*)&Font8x16,COLOR_WHITE,COLOR_BLACK,ID_LAB_dir3,_LEFT);
								GUIComponent *stepping=new Label(lcd,NULL,10,65,150,  16,"Stepping:",(font_t*)&Font8x16,COLOR_BLACK,COLOR_CYAN,ID_LAB_step1,_LEFT);
								GUIComponent *stepping2=new Label(lcd,NULL,100,65,50, 16," AUTO ",(font_t*)&Font8x16,COLOR_WHITE,COLOR_DARK_GREEN,ID_LAB_step4,_LEFT);
								GUIComponent *stepping3=new Label(lcd,NULL,160,65,50, 16,"MANUAL",(font_t*)&Font8x16,COLOR_WHITE,COLOR_BLACK,ID_LAB_step5,_LEFT);
								GUIComponent *steps_rev= new Label(lcd,NULL,10,85,90,  16,"Steps/rev:",(font_t*)&Font8x16,COLOR_BLACK,COLOR_CYAN,ID_LAB_step3,_LEFT);
								GUIComponent *steps_rev2=new Label(lcd,NULL,100,85,24, 16,"200",(font_t*)&Font8x16, COLOR_WHITE,COLOR_DARK_GREEN,ID_LAB_step6,_LEFT);
								GUIComponent *steps_rev3=new Label(lcd,NULL,132,85,24, 16,"400",(font_t*)&Font8x16, COLOR_WHITE,COLOR_BLACK,ID_LAB_step7,_LEFT);
								GUIComponent *steps_rev4=new Label(lcd,NULL,164,85,24, 16,"800",(font_t*)&Font8x16, COLOR_WHITE,COLOR_BLACK,ID_LAB_step8,_LEFT);
								GUIComponent *steps_rev5=new Label(lcd,NULL,196,85,32, 16,"1600",(font_t*)&Font8x16,COLOR_WHITE,COLOR_BLACK,ID_LAB_step9,_LEFT);
								GUIComponent *steps_rev6=new Label(lcd,NULL,236,85,32, 16,"3200",(font_t*)&Font8x16,COLOR_WHITE,COLOR_BLACK,ID_LAB_step10,_LEFT);
								GUIComponent *steps_sec=new Label(lcd,NULL,10,105,88,16,"Steps/s:   ",(font_t*)&Font8x16,COLOR_BLACK,COLOR_CYAN,ID_LAB_step2,_LEFT);								
								GUIComponent *pwm_freq=new Label(lcd,NULL,10,125,88,16, "PWM Freq:  ",(font_t*)&Font8x16,COLOR_BLACK,COLOR_CYAN,ID_LAB_pwm_freq,_LEFT);								
								GUIComponent *pwm_facto=new Label(lcd,NULL,10,145,88,16,"PWM %:     ",(font_t*)&Font8x16,COLOR_BLACK,COLOR_CYAN,ID_LAB_pwm_facto,_LEFT);																
								GUIComponent *steps_sec_nr=new Label(lcd,NULL,98,105,60,16,"100",(font_t*)&Font8x16,COLOR_BLACK,COLOR_CYAN,ID_LAB_step2_nr,_LEFT);								
								GUIComponent *pwm_freq_nr=new Label(lcd,NULL,98,125,88,16, "200 Hz",(font_t*)&Font8x16,COLOR_BLACK,COLOR_CYAN,ID_LAB_pwm_freq_nr,_LEFT);								
								GUIComponent *pwm_facto_nr=new Label(lcd,NULL,98,145,88,16,"50 %",(font_t*)&Font8x16,COLOR_BLACK,COLOR_CYAN,ID_LAB_pwm_facto_nr,_LEFT);											
								
								
                gui->AddComponent(label_auto3,WINDOW_3);  
                gui->AddComponent(auto_back3,WINDOW_3);
								gui->AddComponent(label_dir,WINDOW_3);
								gui->AddComponent(label_dir2,WINDOW_3);
								gui->AddComponent(label_dir3,WINDOW_3);
								gui->AddComponent(stepping,WINDOW_3);
								gui->AddComponent(stepping2,WINDOW_3);
								gui->AddComponent(stepping3,WINDOW_3);
								gui->AddComponent(steps_sec,WINDOW_3);
								gui->AddComponent(steps_rev,WINDOW_3);
								gui->AddComponent(steps_rev2,WINDOW_3);
								gui->AddComponent(steps_rev3,WINDOW_3);
								gui->AddComponent(steps_rev4,WINDOW_3);
								gui->AddComponent(steps_rev5,WINDOW_3);
								gui->AddComponent(steps_rev6,WINDOW_3);
								gui->AddComponent(pwm_freq,WINDOW_3);
								gui->AddComponent(pwm_facto,WINDOW_3);
								gui->AddComponent(steps_sec_nr,WINDOW_3);
								gui->AddComponent(pwm_freq_nr,WINDOW_3);
								gui->AddComponent(pwm_facto_nr,WINDOW_3);
            break;
        case WINDOW_4:
                //init fereastra 4 - SIMULARE
                GUIComponent *label_simulare=new Label(lcd,NULL,0,0,319,40,"SIMULARE",(font_t*)&TerminusBigFont,COLOR_WHITE,COLOR_GRAY,ID_LAB_SIM);
                GUIComponent *auto_sim=new Button(lcd,sim_auto,5,60,150,100,"SIMULARE AUTO",(font_t*)&TerminusBigFont,COLOR_PINK,ID_SIM_AUTO);
                GUIComponent *manual_sim=new Button(lcd,sim_manual,165,60,150,100,"SIMULARE MANUALA",(font_t*)&TerminusBigFont,COLOR_VIOLET,ID_SIM_MANUAL);
                GUIComponent *sim_back=new Button(lcd,back_sim,85,195,150,35,"REVENIRE",(font_t*)&TerminusBigFont,COLOR_LIGHT_RED,ID_BUT_SIMR);									
                gui->AddComponent(label_simulare,WINDOW_4);
								gui->AddComponent(auto_sim,WINDOW_4);
								gui->AddComponent(manual_sim,WINDOW_4);
								gui->AddComponent(sim_back,WINDOW_4);
            break;      
        case WINDOW_5:
                //init fereastra 5 - misca degete
                GUIComponent *label_move_fingers=new Label(lcd,NULL,0,0,319,40,"Miscare degete",(font_t*)&TerminusBigFont,COLOR_WHITE,COLOR_GRAY,ID_LAB_SETARI);
								GUIComponent *sens1=new Label(lcd,NULL,0,50 ,128,16," Senzor1(PC0 ): ",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_SENS0); 
								GUIComponent *sens2=new Label(lcd,NULL,0,66 ,128,16," Senzor2(PC1 ): ",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_SENS1);    
								GUIComponent *sens3=new Label(lcd,NULL,0,82 ,128,16," Senzor3(PC2 ): ",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_SENS2);   
								GUIComponent *sens4=new Label(lcd,NULL,0,108,128,16," Senzor4(PC13): ",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_SENS3); 
								GUIComponent *sens5=new Label(lcd,NULL,0,124,128,16," Senzor5(PC14): ",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_SENS4);    
								GUIComponent *sens6=new Label(lcd,NULL,0,140,128,16," Senzor6(PC15): ",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_SENS5);   

								GUIComponent *sens11=new Label(lcd,NULL,128,50 ,8,16,"0",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_SENS00);    
								GUIComponent *sens22=new Label(lcd,NULL,128,66 ,8,16,"0",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_SENS11);    
								GUIComponent *sens33=new Label(lcd,NULL,128,82 ,8,16,"0",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_SENS22);    
								GUIComponent *sens44=new Label(lcd,NULL,128,108,8,16,"0",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_SENS33);    
								GUIComponent *sens55=new Label(lcd,NULL,128,124,8,16,"0",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_SENS44);    
								GUIComponent *sens66=new Label(lcd,NULL,128,140,8,16,"0",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_SENS55);    

								GUIComponent *senz_drt=new Label(lcd,NULL,150,50 ,150,16,"Mana Dreapta",(font_t*)&Font8x16,COLOR_DARK_BLUE,COLOR_LIGHT_YELLOW,ID_MDRT); 
								GUIComponent *senz_stg=new Label(lcd,NULL,150,108,150,16,"Mana Stanga",(font_t*)&Font8x16,COLOR_DARK_BLUE,COLOR_LIGHT_YELLOW, ID_MSTG); 
								
								GUIComponent *vectori_drt=new Button(lcd,trace_drt,150,70,150,28,"VECTORI",(font_t*)&Font8x16,COLOR_LIGHT_YELLOW,ID_BUT_TRD);		
								GUIComponent *vectori_stg=new Button(lcd,trace_stg,150,128,150,28,"VECTORI",(font_t*)&Font8x16,COLOR_LIME,ID_BUT_TRS);		
								
                GUIComponent *move_back=new Button(lcd,back_from_move,85,195,150,35,"REVENIRE",(font_t*)&TerminusBigFont,COLOR_LIGHT_RED,ID_BUT_REVENIRE);								
                gui->AddComponent(label_move_fingers,WINDOW_5);
                gui->AddComponent(sens1,WINDOW_5);
                gui->AddComponent(sens2,WINDOW_5);
                gui->AddComponent(sens3,WINDOW_5);
                gui->AddComponent(sens4,WINDOW_5);
                gui->AddComponent(sens5,WINDOW_5);
                gui->AddComponent(sens6,WINDOW_5);								
								gui->AddComponent(sens11,WINDOW_5);
								gui->AddComponent(sens22,WINDOW_5);
								gui->AddComponent(sens33,WINDOW_5);
								gui->AddComponent(sens44,WINDOW_5);
								gui->AddComponent(sens55,WINDOW_5);
								gui->AddComponent(sens66,WINDOW_5);	
								gui->AddComponent(senz_drt,WINDOW_5);	
								gui->AddComponent(senz_stg,WINDOW_5);	
								gui->AddComponent(vectori_drt,WINDOW_5);	
								gui->AddComponent(vectori_stg,WINDOW_5);	
                gui->AddComponent(move_back,WINDOW_5);
            break;
        case WINDOW_6:
                //init fereastra 6 - SETARI - atinge degete
								GUIComponent *comb_lbl;
                GUIComponent *label_touch_fingers=new Label(lcd,NULL,0,0,319,40,"Atinge degete",(font_t*)&TerminusBigFont,COLOR_WHITE,COLOR_GRAY,ID_LAB_TFING);
								GUIComponent *adc1=new Label(lcd,NULL,0,50 ,200,16,"Mana Dreapta (ADC1-PA6): ",(font_t*)&Font8x16,COLOR_DARK_BLUE,COLOR_LIGHT_YELLOW,ID_ADC1); 
								GUIComponent *adc2=new Label(lcd,NULL,0,66 ,200,16,"Mana Stanga  (ADC2-PA7): ",(font_t*)&Font8x16,COLOR_DARK_BLUE,COLOR_LIGHT_YELLOW,ID_ADC2);
								GUIComponent *nadc1=new Label(lcd,NULL,200,50 ,40,16,"     ",(font_t*)&Font8x16,COLOR_DARK_BLUE,COLOR_LIGHT_YELLOW,ID_NADC1); 
								GUIComponent *nadc2=new Label(lcd,NULL,200,66 ,40,16,"     ",(font_t*)&Font8x16,COLOR_DARK_BLUE,COLOR_LIGHT_YELLOW,ID_NADC2); 								
                GUIComponent *move_back_tf=new Button(lcd,back_from_touch,85,195,150,35,"REVENIRE",(font_t*)&TerminusBigFont,COLOR_LIGHT_RED,ID_BUT_REV_TC);
								
								GUIComponent *label_comb_drt=new Label(lcd,NULL,0,90,319,16,"combinatii dreapta",(font_t*)&Font8x16,COLOR_ORANGE,COLOR_LIGHT_YELLOW,ID_COMBS); 
								GUIComponent *label_comb_stg=new Label(lcd,NULL,0,140,319,16,"combinatii stanga",(font_t*)&Font8x16,COLOR_ORANGE,COLOR_LIGHT_YELLOW,ID_COMBD); 
								
								for (i=0;i<6;i++)
								{
										comb_lbl=new Label(lcd,NULL,20+i*48,106,32,28,comb[0][i],(font_t*)&TerminusBigFont,COLOR_WHITE,COLOR_LIGHT_YELLOW,comb_ids[0][i]);
										gui->AddComponent(comb_lbl,WINDOW_6);
										comb_lbl=new Label(lcd,NULL,20+i*48,156,32,28,comb[1][i],(font_t*)&TerminusBigFont,COLOR_WHITE,COLOR_LIGHT_YELLOW,comb_ids[1][i]);
										gui->AddComponent(comb_lbl,WINDOW_6);										
								}
								
                gui->AddComponent(label_touch_fingers,WINDOW_6);
                gui->AddComponent(move_back_tf,WINDOW_6);
                gui->AddComponent(adc1,WINDOW_6);
								gui->AddComponent(adc2,WINDOW_6);
								gui->AddComponent(nadc1,WINDOW_6);
								gui->AddComponent(nadc2,WINDOW_6);
								gui->AddComponent(label_comb_drt,WINDOW_6);
								gui->AddComponent(label_comb_stg,WINDOW_6);
            break;
        case WINDOW_7:
                //init fereastra 7 - vectori senzori dreapta
                GUIComponent *label_dvecs=new Label(lcd,NULL,0,0,319,40,"Vectori Dreapta",(font_t*)&TerminusBigFont,COLOR_WHITE,COLOR_GRAY,ID_VECT_DRT);
								
                GUIComponent *label_vecd0=new Label(lcd,NULL,10,45,112,16,"Vector Senzor1",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_LAB_S0);    
                GUIComponent *editvecd0=new EditBox(lcd,NULL,10,61,260,16,(font_t*)&Font8x16,COLOR_BLACK,COLOR_WHITE,COLOR_BLUE,true,ID_EDT_S0);  
                GUIComponent *label_vecd1=new Label(lcd,NULL,10,87,112,16,"Vector Senzor2",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_LAB_S1);    
                GUIComponent *editvecd1=new EditBox(lcd,NULL,10,103,260,16,(font_t*)&Font8x16,COLOR_BLACK,COLOR_WHITE,COLOR_BLUE,true,ID_EDT_S1);  
                GUIComponent *label_vecd2=new Label(lcd,NULL,10,129,112,16,"Vector Senzor3",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_LAB_S2);    
                GUIComponent *editvecd2=new EditBox(lcd,NULL,10,145,260,16,(font_t*)&Font8x16,COLOR_BLACK,COLOR_WHITE,COLOR_BLUE,true,ID_EDT_S2);  
								
								GUIComponent *vdmove_back=new Button(lcd,back_from_vd,85,195,150,35,"REVENIRE",(font_t*)&TerminusBigFont,COLOR_LIGHT_RED,ID_BUT_REV_VD);							
								
                gui->AddComponent(label_dvecs,WINDOW_7);     
                gui->AddComponent(label_vecd0,WINDOW_7);
								gui->AddComponent(editvecd0,WINDOW_7);
								gui->AddComponent(label_vecd1,WINDOW_7);
								gui->AddComponent(editvecd1,WINDOW_7);
								gui->AddComponent(label_vecd2,WINDOW_7);
								gui->AddComponent(editvecd2,WINDOW_7);
								gui->AddComponent(vdmove_back,WINDOW_7);
            break;
        case WINDOW_8:
                //init fereastra 8 - vectori senzori stanga
                GUIComponent *label_svecs=new Label(lcd,NULL,0,0,319,40,"Vectori Stanga",(font_t*)&TerminusBigFont,COLOR_WHITE,COLOR_GRAY,ID_VECT_STG);
								
                GUIComponent *label_vecs0=new Label(lcd,NULL,10,45,112,16,"Vector Senzor4",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_LAB_S3);    
                GUIComponent *editvecs0=new EditBox(lcd,NULL,10,61,260,16,(font_t*)&Font8x16,COLOR_BLACK,COLOR_WHITE,COLOR_BLUE,true,ID_EDT_S3);  
                GUIComponent *label_vecs1=new Label(lcd,NULL,10,87,112,16,"Vector Senzor5",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_LAB_S4);    
                GUIComponent *editvecs1=new EditBox(lcd,NULL,10,103,260,16,(font_t*)&Font8x16,COLOR_BLACK,COLOR_WHITE,COLOR_BLUE,true,ID_EDT_S4);  
                GUIComponent *label_vecs2=new Label(lcd,NULL,10,129,112,16,"Vector Senzor6",(font_t*)&Font8x16,COLOR_DARK_GREEN,COLOR_LIGHT_YELLOW,ID_LAB_S5);    
                GUIComponent *editvecs2=new EditBox(lcd,NULL,10,145,260,16,(font_t*)&Font8x16,COLOR_BLACK,COLOR_WHITE,COLOR_BLUE,true,ID_EDT_S5);  
								
								GUIComponent *vsmove_back=new Button(lcd,back_from_vs,85,195,150,35,"REVENIRE",(font_t*)&TerminusBigFont,COLOR_LIGHT_RED,ID_BUT_REV_VS);	
								
                gui->AddComponent(label_svecs,WINDOW_8);     
                gui->AddComponent(label_vecs0,WINDOW_8);
								gui->AddComponent(editvecs0,WINDOW_8);
								gui->AddComponent(label_vecs1,WINDOW_8);
								gui->AddComponent(editvecs1,WINDOW_8);
								gui->AddComponent(label_vecs2,WINDOW_8);
								gui->AddComponent(editvecs2,WINDOW_8);
								gui->AddComponent(vsmove_back,WINDOW_8);
            break;            
        case WINDOW_9:
                //init fereastra 9 - SIMULARE AUTO  
                GUIComponent *label_auto=new Label(lcd,NULL,0,0,319,40,"Simulare Auto",(font_t*)&TerminusBigFont,COLOR_WHITE,COLOR_BLUE,ID_LAB_AUTO);                
                GUIComponent *auto_back=new Button(lcd,back_from_auto,85,195,150,35,"REVENIRE",(font_t*)&TerminusBigFont,COLOR_LIGHT_RED,ID_BUT_AUTO_BACK);	
								GUIComponent *auto_list=new ListBox(lcd,NULL,(font_t*)&Font8x16,COLOR_LIGHT_GRAY,COLOR_BLACK,COLOR_WHITE,COLOR_RED,ID_AUTO_LIST);
                gui->AddComponent(label_auto,WINDOW_9);  
                gui->AddComponent(auto_back,WINDOW_9);
								gui->AddComponent(auto_list,WINDOW_9);
            break;
        case WINDOW_10:
                //init fereastra 10 - SIMULARE MANUALA
                GUIComponent *label_manual=new Label(lcd,NULL,0,0,319,40,"Simulare Manuala",(font_t*)&TerminusBigFont,COLOR_WHITE,COLOR_BLUE,ID_LAB_MAN);                
                GUIComponent *manual_back=new Button(lcd,back_from_manual,85,195,150,35,"REVENIRE",(font_t*)&TerminusBigFont,COLOR_LIGHT_RED,ID_BUT_MAN_BACK);	
                gui->AddComponent(label_manual,WINDOW_10);  
                gui->AddComponent(manual_back,WINDOW_10);                                                                                  
            break;
        case WINDOW_11:
                //init fereastra 11 - Masina a terminat ce avea de facut, timpul de lucru, numar bucati, lungime bucata, revenire meniu principal
                /*GUIComponent *label_succt=new Label(lcd,NULL,0,0,319,30,"Masina a terminat cu succes!",(font_t*)&Font8x16,COLOR_BLACK,COLOR_GREEN,COLOR_WHITE,COLOR_GREEN,ID_LAB_SUCCESS);                
                sprintf(data,"Bucati taiate: %d",numar_bucati);
                GUIComponent *label_succinfo=new Label(lcd,NULL,0,210,319,30,data,(font_t*)&Font8x16,COLOR_BLACK,COLOR_YELLOW,COLOR_WHITE,COLOR_YELLOW,ID_LAB_SUCCINF);                
                GUIComponent *but_succ_term=new Button(lcd,revenire_success,50,80,220,50,"REVENIRE",(font_t*)&Font8x16,COLOR_LIGHT_RED,ID_LAB_SUCCREV); 
                gui->AddComponent(label_succt,WINDOW_11);  
                gui->AddComponent(label_succinfo,WINDOW_11);  
                gui->AddComponent(but_succ_term,WINDOW_11);     */                                            
            break;
        case WINDOW_12:
                //init fereastra 12 - alege impulsuri pentru lungimea predefinita
                /*GUIComponent *label_alval=new Label(lcd,NULL,0,0,319,30,"EDITEAZA ECHIVALENT IMPULSURI",(font_t*)&Font8x16,COLOR_BLACK,COLOR_LIME,COLOR_WHITE,COLOR_LIME,ID_LAB_SELCAL);                                    
                GUIComponent *edtval=new EditBox(lcd,NULL,10,40,300,20,(font_t*)&Font8x16,COLOR_BLACK,COLOR_WHITE,COLOR_BLUE,false,ID_EDT_CALVAL);  
                GUIComponent *acceptv=new Button(lcd,accepta_impulsuri,30,200,100,25,"ACCEPTA",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_ACCEPTV);
                GUIComponent *refuzv=new Button(lcd,refuza_impulsuri,190,200,100,25,"RENUNTA",(font_t*)&Font8x16,COLOR_LIGHT_RED,ID_BUT_REJECTV);    
                gui->AddComponent(label_alval,WINDOW_12);     
                gui->AddComponent(edtval,WINDOW_12);
                gui->AddComponent(acceptv,WINDOW_12);
                gui->AddComponent(refuzv,WINDOW_12);
                AddPredefinedButtonsPWD(gui,ID_BUT_FIRSTC7,mini_predefined_keyboard,WINDOW_12);*/
            break;
        case WINDOW_13:
                //init fereastra 13 - arata vectorul de calibrare pentru encoder                
                /*char *text;
                int i;
                
                GUIComponent *label_calibv=new Label(lcd,NULL,0,0,319,30,"Vectorul de calibrare",(font_t*)&Font8x16,COLOR_BLACK,COLOR_LIME,COLOR_WHITE,COLOR_LIME,ID_LAB_CALIBV);                                     
                GUIComponent *calibv_back=new Button(lcd,revenire_show_vector,50,205,220,30,"REVENIRE",(font_t*)&Font8x16,COLOR_LIGHT_RED,ID_BUT_BACK);               
                GUIComponent *vect_info=new TextField(lcd,0,60,40,200,160,(font_t*)&Font8x16,true,COLOR_AQUA,COLOR_BLACK,COLOR_RED,ID_TEXT_FIELD);               
                text=new char[30];
                for (i=0;i<10;i++)
                {
                    sprintf(text,"%3d - %-6d %3d - %-6d",lungimi_predefinite[i],vector_impulsuri[i],lungimi_predefinite[10+i],vector_impulsuri[10+i]);
                    ((TextField*)vect_info)->AddLine(text);
                } 
                free(text);
                gui->AddComponent(label_calibv,WINDOW_13);
                gui->AddComponent(calibv_back,WINDOW_13);
                gui->AddComponent(vect_info,WINDOW_13);*/
            break;
        case WINDOW_14:
                //testare encoder
                /*GUIComponent *label_encr=new Label(lcd,NULL,0,0,319,30,"Roteste Encoder",(font_t*)&Font8x16,COLOR_BLACK,COLOR_OLIVE,COLOR_WHITE,COLOR_OLIVE,ID_LAB_ENCT);                                                     
                sprintf(data,"Lungime: %d mm",lensum);
                GUIComponent *encdata=new Label(lcd,NULL,60,110,200,20,data,(font_t*)&Font8x16,COLOR_BLACK,COLOR_OLIVE,COLOR_CYAN,COLOR_OLIVE,ID_TEXT_ENC);
                GUIComponent *enc_reset=new Button(lcd,enc_reset_data,50,175,100,60,"RESET",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_ERESET);               
                GUIComponent *enc_stop=new Button(lcd,enc_stop_data,170,175,100,60,"REVENIRE",(font_t*)&Font8x16,COLOR_LIGHT_RED,ID_BUT_EBACK);               
                gui->AddComponent(label_encr,WINDOW_14);
                gui->AddComponent(encdata,WINDOW_14);
                gui->AddComponent(enc_reset,WINDOW_14); 
                gui->AddComponent(enc_stop,WINDOW_14); */
            break;    
        case WINDOW_15:
                //testare presa
                /*GUIComponent *label_presa=new Label(lcd,NULL,0,0,319,30,"Verificare Presa",(font_t*)&Font8x16,COLOR_BLACK,COLOR_OLIVE,COLOR_WHITE,COLOR_OLIVE,ID_LAB_PRESA);                                                     
                GUIComponent *enc_prescc=new Button(lcd,presa_ciclu_simplu,30,35,120,50,"Rotatie Scurta",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_CICSI);               
                GUIComponent *enc_presch=new Button(lcd,presa_ciclu_continuu,170,35,120,50,"Rotatie Cursiva",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_CICCU); 
                GUIComponent *enc_press1=new Button(lcd,presa_complet,30,95,120,50,"Rotatie Completa",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_SUPA1);               
                GUIComponent *enc_span=new Button(lcd,presa_span,170,95,120,50,"Curata Span",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_SUPA2); 
                sprintf(data,"Senzor Rotatie Presa: %d",senzor_rotatie_presa);
                GUIComponent *label_rot_presa=new Label(lcd,NULL,30,160,250,16,data,(font_t*)&Font8x16,COLOR_BLACK,COLOR_CYAN,0,0,ID_LAB_ROTB1);                
                GUIComponent *enc_prev=new Button(lcd,presa_stop,110,190,100,40,"REVENIRE",(font_t*)&Font8x16,COLOR_LIGHT_RED,ID_BUT_CIREV);               
                gui->AddComponent(label_presa,WINDOW_15);
                gui->AddComponent(enc_prescc,WINDOW_15);
                gui->AddComponent(enc_presch,WINDOW_15); 
                gui->AddComponent(enc_press1,WINDOW_15); 
                gui->AddComponent(enc_span,WINDOW_15); 
                gui->AddComponent(label_rot_presa,WINDOW_15); 
                gui->AddComponent(enc_prev,WINDOW_15);  */               
            break;    
        case WINDOW_16:
                //testare electromagnet
                /*GUIComponent *label_elemag=new Label(lcd,NULL,0,0,319,30,"Verificare Piston Electromagnet",(font_t*)&Font8x16,COLOR_BLACK,COLOR_OLIVE,COLOR_WHITE,COLOR_OLIVE,ID_LAB_ELEMG);                                                     
                GUIComponent *emg_pistoni=new Button(lcd,elemg_pistoni,30,35,120,60,"Impinge Piston",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_PISTONI);               
                GUIComponent *emg_pistont=new Button(lcd,elemg_pistont,170,35,120,60,"Trage Piston",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_PISTONT); 
                GUIComponent *emg_elemgon=new Button(lcd,elemg_elemagon,30,110,120,60,"Activeaza Electromagnet",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_ELEMGI);               
                GUIComponent *emg_elemgof=new Button(lcd,elemg_elemagof,170,110,120,60,"Dezactiveaza Electromagnet",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_ELEMGT);                 
                GUIComponent *emg_prev=new Button(lcd,elemg_rev,110,190,100,40,"REVENIRE",(font_t*)&Font8x16,COLOR_LIGHT_RED,ID_BUT_ELEREV);               
                gui->AddComponent(label_elemag,WINDOW_16);
                gui->AddComponent(emg_pistoni,WINDOW_16);
                gui->AddComponent(emg_pistont,WINDOW_16); 
                gui->AddComponent(emg_elemgon,WINDOW_16); 
                gui->AddComponent(emg_elemgof,WINDOW_16); 
                gui->AddComponent(emg_prev,WINDOW_16);     */                            
            break;    
        case WINDOW_17:
                //testare intrare material - motor
                /*GUIComponent *label_motorin=new Label(lcd,NULL,0,0,319,30,"Verificare Motor Intrare",(font_t*)&Font8x16,COLOR_BLACK,COLOR_OLIVE,COLOR_WHITE,COLOR_OLIVE,ID_LAB_MOTOR);                                                     
                GUIComponent *motor_activ=new Button(lcd,motor_activare,30,35,120,60,"Porneste Motor",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_MOTORAC);               
                GUIComponent *motor_inactiv=new Button(lcd,motor_oprire,170,35,120,60,"Opreste Motor",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_MOTORST); 
                GUIComponent *motor_1s=new Button(lcd,motor_1secunda,30,110,120,60,"Porneste 1s",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_MOTOR1S);               
                GUIComponent *motor_3s=new Button(lcd,motor_3secunde,170,110,120,60,"Porneste 3s",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_MOTOR3S);                 
                GUIComponent *motor_rev=new Button(lcd,motor_revenire,110,190,100,40,"REVENIRE",(font_t*)&Font8x16,COLOR_LIGHT_RED,ID_BUT_MOTORBK);               
                gui->AddComponent(label_motorin,WINDOW_17);
                gui->AddComponent(motor_activ,WINDOW_17);
                gui->AddComponent(motor_inactiv,WINDOW_17); 
                gui->AddComponent(motor_1s,WINDOW_17); 
                gui->AddComponent(motor_3s,WINDOW_17); 
                gui->AddComponent(motor_rev,WINDOW_17);  */                   
            break;    
        case WINDOW_18:
                //testare senzor iesire material
                /*GUIComponent *label_senzor_out=new Label(lcd,NULL,0,0,319,30,"Verificare Senzor Iesire",(font_t*)&Font8x16,COLOR_BLACK,COLOR_OLIVE,COLOR_WHITE,COLOR_OLIVE,ID_LAB_SENZMAT);                                                                     
                GUIComponent *label_material_Static=new Label(lcd,NULL,0,100,319,30,"Material gata:",(font_t*)&TerminusBigFont,COLOR_BLACK,COLOR_CYAN,0,0,ID_LAB_SENZOIM);                
                sprintf(data,"%s",(senzor_material_iesire==1)?"DA":"NU");
                GUIComponent *label_material_dinamic=new Label(lcd,NULL,15*TerminusBigFont.Width,100,40,30,data,(font_t*)&TerminusBigFont,COLOR_RED,COLOR_CYAN,0,0,ID_LAB_SENZDIN);                
                GUIComponent *senz_rev=new Button(lcd,senzor_material_rev,110,190,100,40,"REVENIRE",(font_t*)&Font8x16,COLOR_LIGHT_RED,ID_BUT_SENZREV);               
                gui->AddComponent(label_senzor_out,WINDOW_18); 
                gui->AddComponent(label_material_Static,WINDOW_18); 
                gui->AddComponent(label_material_dinamic,WINDOW_18); 
                gui->AddComponent(senz_rev,WINDOW_18);  */
            break;    
        case WINDOW_19:
                //teste complete de executie (1/2 bucati de proba)
                /*GUIComponent *label_executie=new Label(lcd,NULL,0,0,319,30,"Proba Executie Bucati",(font_t*)&Font8x16,COLOR_BLACK,COLOR_OLIVE,COLOR_WHITE,COLOR_OLIVE,ID_LAB_EXECUTA);                                                                     
                GUIComponent *executa_1b20cm=new Button(lcd,exec1b20,30,35,120,60,"Executa 1buc/20cm",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_EXE1B20);               
                GUIComponent *executa_3b20cm=new Button(lcd,exec3b20,170,35,120,60,"Executa 3buc/20cm",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_EXE3B20); 
                GUIComponent *executa_1b40cm=new Button(lcd,exec1b40,30,110,120,60,"Executa 1buc/40cm",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_EXE1B40);               
                GUIComponent *executa_3b40cm=new Button(lcd,exec3b40,170,110,120,60,"Executa 3buc/40cm",(font_t*)&Font8x16,COLOR_WORM_GREEN,ID_BUT_EXE3B40);                 
                GUIComponent *executa_rev=new Button(lcd,exec_rev,110,190,100,40,"REVENIRE",(font_t*)&Font8x16,COLOR_LIGHT_RED,ID_BUT_EXECREV);               
                gui->AddComponent(label_executie,WINDOW_19);
                gui->AddComponent(executa_1b20cm,WINDOW_19);
                gui->AddComponent(executa_3b20cm,WINDOW_19); 
                gui->AddComponent(executa_1b40cm,WINDOW_19); 
                gui->AddComponent(executa_3b40cm,WINDOW_19); 
                gui->AddComponent(executa_rev,WINDOW_19); */                                   
            break;            
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------

/*
orice buton apasat care face tranzitia intr-o alta fereastra, va aloca intai toate componentele noii ferestre,
apoi va seta un flag care va spune GUIului ca dupa repaint la noua fereastra va dealoca complet fereastra anterioara
astfel vom avea mereu in memorie cel mult 2 ferestre, cea curenta si cea in care intentionam sa tranzitam
*/

//------------------------------------CALLBACKURI pentru evenimentele de TOUCH-DOWN la butoanele de pe fereastra 0-----------------------------------------
void usart_interface(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;
    _gui->TranzitFereastra(WINDOW_0,WINDOW_3);
}

void manual_config(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_0,WINDOW_1);
}

void auto_config(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_0,WINDOW_4);
}

void motor_test(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_0,WINDOW_3);		
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------CALLBACKURI pentru evenimentele de TOUCH-DOWN la butoanele de pe fereastra 1--------------------------------------
void move_left(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_1,WINDOW_5);         
}

void move_right(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_1,WINDOW_6); 		
}

void testare_back(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_1,WINDOW_0);      
}

void configs(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_1,WINDOW_2);      
}

void enpwm(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_1,WINDOW_0);      
}

void dispwm(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_1,WINDOW_0);      
}

void endrv(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_1,WINDOW_0);      
}

void disdrv(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_1,WINDOW_0);      
}

void onestep(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_1,WINDOW_0);      	
}

void incspeed(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_1,WINDOW_0);      	
}

void decspeed(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_1,WINDOW_0);      	
}

void direction(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_1,WINDOW_0);      		
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------
void testare_back2(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_2,WINDOW_0);      
}

void configs2(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_2,WINDOW_1);      
}

void slide_event(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
		
    //_gui->TranzitFereastra(WINDOW_2,WINDOW_1);	
}

//---------------------------------------- FEREASTRA 4 - simulare MIDI --------------------------------------------------------------------------------
void sim_auto(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_4,WINDOW_9);	
}

void sim_manual(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_4,WINDOW_10);	
}

void back_sim(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_4,WINDOW_0);    		
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------


//--------------------------------------- FEREASTRA 5 - testare miscare degete ------------------------------------------------------------------------
void back_from_move(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_5,WINDOW_1);      
}

void trace_drt(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_5,WINDOW_7); 
}

void trace_stg(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_5,WINDOW_8); 	
}
//------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------- FEREASTRA 6 - back from atingere degete -----------------------------------------------------------------
void back_from_touch(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_6,WINDOW_1);      		
}
//------------------------------------------------------------------------------------------------------------------------------------------------------



//------------------------------------------- FEREASTRA 7 - back from vector dreapta -------------------------------------------------------------------
void back_from_vd(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_7,WINDOW_5); 			
}
//------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------- FEREASTRA 8 - back from vector stanga -------------------------------------------------------------------
void back_from_vs(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_8,WINDOW_5); 			
}
//------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------- FEREASTRA 9 AUTO SIMULARE --------------------------------------------------------------------------------
void back_from_auto(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_9,WINDOW_4); 		
}

void back_from_play(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_3,WINDOW_0); 		
}
//------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------- FEREASTRA 10 SIMULARE MANUALA ---------------------------------------------------------------------------
void back_from_manual(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_10,WINDOW_4); 				
}
//------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------CALLBACKURI pentru evenimentele de TOUCH-DOWN la butoanele de pe fereastra 2--------------------------------------
void accepta_lungime(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;
    GUIComponent *editbox=_gui->GetComponentByID(ID_EDT_BOX2,WINDOW_2);
    lungime_buc=(atoi(((EditBox*)editbox)->GetText())+13)*10;
    ((EditBox*)editbox)->ResetInitialState(true);
    _gui->TranzitFereastra(WINDOW_2,WINDOW_0);   
}

void refuza_lungime(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;
    _gui->TranzitFereastra(WINDOW_2,WINDOW_0);   
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------CALLBACKURI pentru evenimentele de TOUCH-DOWN la butoanele de pe fereastra 3--------------------------------------
void stop_masina(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    job_start=false;             
    UNIVERSAL_STOP();
    error_mode=0;
    _gui->TranzitFereastra(WINDOW_3,WINDOW_9);   
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------CALLBACKURI pentru evenimentele de pe fereastra de setari---------------------------------------------
void calibrare_touch(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
		Touch *tpl=_gui->GetTouch();
    printf("[calibrare_touch]: Recalibram TouchScreen\r\n");
    tpl->TouchPanelCalibrate();    
    printf("[calibrare_touch]: Changing Window to 5. *GUI=%08X\r\n",_gui);  
    _gui->ChangeWindow(WINDOW_5);    
}

void calibrare_encoder(void *interfata)
{
    //suspendata temporar
    //GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    //_gui->TranzitFereastra(WINDOW_5,WINDOW_6);   
}

void change_password(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;
    _gui->TranzitFereastra(WINDOW_5,WINDOW_7);   
}

void configurare_manuala(void *interfata)
{
     GUI *_gui=((GUI_PACKET*)interfata)->gui;
    _gui->TranzitFereastra(WINDOW_5,WINDOW_10);   
}

void revenire_setari(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;
    _gui->TranzitFereastra(WINDOW_5,WINDOW_0);   
}
//------------------------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------CALLBACKURI de pe fereastra cu itrodus parola curenta pt schimbat--------------------------------------
void accepta_parola_curenta(void *interfata)
{

}

void refuza_parola_curenta(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_7,WINDOW_5);   
}
//------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------CALLBACKURI pentru acceptat noua parola----------------------------------------------------------------
void accepta_parola_noua(void *interfata)
{

}

void refuza_parola_noua(void *interfata)
{
    GUI *_gui=((GUI_PACKET*)interfata)->gui;    
    _gui->TranzitFereastra(WINDOW_8,WINDOW_5);   
}
//------------------------------------------------------------------------------------------------------------------------------------------------------

void s200(void *interfata)
{
	
}

void s400(void *interfata)
{
	
}

void s800(void *interfata)
{
	
}

void s1600(void *interfata)
{
	
}

void s3200(void *interfata)
{
	
}

int get_val_index(int val,int *vector)
{
		int i;
		
		for (i=0;i<6;i++)
		{
				if (val<=vector[i])
					return i;
		}
		
		return 1000;
}

char buf[100];
int cidx;

/*
lista comenzi suportate:
dir:L!          0
dir:R!          1
stepping:A!     2
stepping:M!     3
stepsrev:200!   4
stepsrev:400!   4
stepsrev:800!   4
stepsrev:1600!  4
stepsrev:3200!  4
stepssec:nr!    5
pwmfrequ:nr!    6
pwmfacto:nr!    7
startpwm!				8
stoppwm!				9			
singlestep!			10
*/
int GetCMD(int *nr)
{
		int status=false;
		
		if (cidx>0 && buf[cidx-1]=='!')
		{
				buf[cidx-1]=0;
				cidx=0;
				status=true;
		}
		
		if (status)
		{
				if (!strncmp(buf,"dir",3))
				{
						switch (buf[4])
						{
								case 'L': return 0;
								case 'R': return 1;
						}
				}
				
				if (!strncmp(buf,"stepping",8))
				{
						switch (buf[9])
						{
								case 'A': return 2;
								case 'M': return 3;
						}
				}
				
				if (!strncmp(buf,"stepsrev",8))
				{
						*nr=atoi(buf+9);
						return 4;
				}		
				
				if (!strncmp(buf,"steptime",8))
				{
						*nr=atoi(buf+9);
						return 5;
				}				
				
				if (!strncmp(buf,"pwmfrequ",8))
				{
						*nr=atoi(buf+9);
						return 6;
				}				

				if (!strncmp(buf,"pwmfacto",8))
				{
						*nr=atoi(buf+9);
						return 7;
				}				
				if (!strncmp(buf,"singlestep",10))
				{
						*nr=atoi(buf+11);
						return 8;
				}
		}
		
		return -1;
}

void ProcesariFerestre(void *interfata)
{
		GUI *_gui=((GUI_PACKET*)interfata)->gui;
		Label *left,*right,*lauto,*lmanual;
		Label *_200,*_400,*_800,*_1600,*_3200;
		Label *stepss;
		char cbuc[40];
		int nr=0,cmd;
		char temp[10];
		int i;
		GPIO_InitTypeDef GPIO_InitStructure;
		TM_PWM_TIM_t PWM_Data;

		if (_gui->WindowReady() && _gui->GetWindow()==WINDOW_3)
		{
				nr=0;
				cmd=GetCMD(&nr);
				if (cmd!=-1)
					printf("cmd=%d, nr=%d\r\n",cmd,nr);
				
				switch(cmd)
				{
					case 0:
							left=(Label*)_gui->GetComponentByID(ID_LAB_dir2,WINDOW_3);
							right=(Label*)_gui->GetComponentByID(ID_LAB_dir3,WINDOW_3);
							left->ChangeLabelBack(COLOR_DARK_GREEN);
							right->ChangeLabelBack(COLOR_BLACK);
							GPIO_SetBits(GPIOC , GPIO_Pin_3);
						break;
					case 1:
							left=(Label*)_gui->GetComponentByID(ID_LAB_dir2,WINDOW_3);
							right=(Label*)_gui->GetComponentByID(ID_LAB_dir3,WINDOW_3);							
							left->ChangeLabelBack(COLOR_BLACK);
							right->ChangeLabelBack(COLOR_DARK_GREEN);							
							GPIO_ResetBits(GPIOC , GPIO_Pin_3);
						break;
					case 2:
							lauto=(Label*)_gui->GetComponentByID(ID_LAB_step4,WINDOW_3);
							lmanual=(Label*)_gui->GetComponentByID(ID_LAB_step5,WINDOW_3);							
							lauto->ChangeLabelBack(COLOR_DARK_GREEN);
							lmanual->ChangeLabelBack(COLOR_BLACK);	
							//activam PWM ca input pentru stepping la PA5
							TM_PWM_InitTimer(TIM2, &PWM_Data, pwm_frecventa);
							TM_PWM_InitChannel(TIM2, TM_PWM_Channel_1, TM_PWM_PinsPack_2);
							TM_PWM_SetChannelPercent(TIM2, &PWM_Data, TM_PWM_Channel_1, pwm_procent);		
							printf("Initialized: PWM ON PA5 - F=[%d Hz] Percent=[%d %%]\r\n",pwm_frecventa,pwm_procent);	  							
						break;
					case 3:
							lauto=(Label*)_gui->GetComponentByID(ID_LAB_step4,WINDOW_3);
							lmanual=(Label*)_gui->GetComponentByID(ID_LAB_step5,WINDOW_3);							
							lauto->ChangeLabelBack(COLOR_BLACK);
							lmanual->ChangeLabelBack(COLOR_DARK_GREEN);														
							//dezactivam PWM ca input pentru stepping la PA5 si trecem pe output normal
							RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
							GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;    
							GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
							GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
							GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
							GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
							GPIO_Init(GPIOA, &GPIO_InitStructure);							
							GPIO_ResetBits(GPIOA , GPIO_Pin_5);							
						break;
					case 4:
							//PC2,PC1,PC0 - MS3,MS2,MS1
							if (nr!=200 && nr!=400 && nr!=800 && nr!=1600 && nr!=3200)
								break;
							_200= (Label*)_gui->GetComponentByID(ID_LAB_step6,WINDOW_3);
							_400= (Label*)_gui->GetComponentByID(ID_LAB_step7,WINDOW_3);
							_800= (Label*)_gui->GetComponentByID(ID_LAB_step8,WINDOW_3);
							_1600=(Label*)_gui->GetComponentByID(ID_LAB_step9,WINDOW_3);
							_3200=(Label*)_gui->GetComponentByID(ID_LAB_step10,WINDOW_3);
							_200->ChangeLabelBack(COLOR_BLACK);
							_400->ChangeLabelBack(COLOR_BLACK);
							_800->ChangeLabelBack(COLOR_BLACK);
							_1600->ChangeLabelBack(COLOR_BLACK);
							_3200->ChangeLabelBack(COLOR_BLACK);
							switch (nr)
							{
								case 200:
										_200->ChangeLabelBack(COLOR_DARK_GREEN);
										GPIO_ResetBits(GPIOC , GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0);	
									break;
								case 400:
										_400->ChangeLabelBack(COLOR_DARK_GREEN);
										GPIO_ResetBits(GPIOC , GPIO_Pin_2 | GPIO_Pin_1);	
										GPIO_SetBits(GPIOC, GPIO_Pin_0);
									break;
								case 800:
										_800->ChangeLabelBack(COLOR_DARK_GREEN);
										GPIO_ResetBits(GPIOC , GPIO_Pin_2 | GPIO_Pin_0);	
										GPIO_SetBits(GPIOC, GPIO_Pin_1);										
									break;
								case 1600:
										_1600->ChangeLabelBack(COLOR_DARK_GREEN);
										GPIO_ResetBits(GPIOC , GPIO_Pin_2);	
										GPIO_SetBits(GPIOC, GPIO_Pin_1|GPIO_Pin_0);																				
									break;
								case 3200:
										_3200->ChangeLabelBack(COLOR_DARK_GREEN);
										GPIO_SetBits(GPIOC, GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0);																														
									break;
							}
						break;
					case 5:							
							stepss= (Label*)_gui->GetComponentByID(ID_LAB_step2_nr,WINDOW_3);
							sprintf(temp,"%d",nr);
							stepss->ChangeLabel((char*)temp);
							steptime=nr;
						break;
					case 6:
							stepss= (Label*)_gui->GetComponentByID(ID_LAB_pwm_freq_nr,WINDOW_3);
							sprintf(temp,"%d Hz",nr);
							stepss->ChangeLabel((char*)temp);
							pwm_frecventa=nr;
							TM_PWM_InitTimer(TIM2, &PWM_Data, pwm_frecventa);
							TM_PWM_InitChannel(TIM2, TM_PWM_Channel_1, TM_PWM_PinsPack_2);
							TM_PWM_SetChannelPercent(TIM2, &PWM_Data, TM_PWM_Channel_1, pwm_procent);		
							printf("Initialized: PWM ON PA5 - F=[%d Hz] Percent=[%d %%]\r\n",pwm_frecventa,pwm_procent);	  														
						break;
					case 7:
							stepss= (Label*)_gui->GetComponentByID(ID_LAB_pwm_facto_nr,WINDOW_3);
							sprintf(temp,"%d %%",nr);
							stepss->ChangeLabel((char*)temp);			
							pwm_procent=nr;
							TM_PWM_InitTimer(TIM2, &PWM_Data, pwm_frecventa);
							TM_PWM_InitChannel(TIM2, TM_PWM_Channel_1, TM_PWM_PinsPack_2);
							TM_PWM_SetChannelPercent(TIM2, &PWM_Data, TM_PWM_Channel_1, pwm_procent);		
							printf("Initialized: PWM ON PA5 - F=[%d Hz] Percent=[%d %%]\r\n",pwm_frecventa,pwm_procent);	  														
						break;
					case 8:		
							printf("Make [%d] steps with steptime [%d]\r\n",nr,steptime);
							for (i=0;i<nr;i++)
							{
								GPIO_SetBits(GPIOA , GPIO_Pin_5);									
								Delay(steptime/2);
								GPIO_ResetBits(GPIOA , GPIO_Pin_5);	
								Delay(steptime/2);
							}
						break;
				}
		}		
}