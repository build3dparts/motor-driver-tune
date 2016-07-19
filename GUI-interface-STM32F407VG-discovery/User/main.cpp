#include "stm32f4xx.h"
#include <stdio.h>
#include "pinout.h"
#include "adc.h"

extern "C" 
{ 
#include "usart/UARTLib.h"
//#include "SD_CARD/ff.h"
//#include "SD_CARD/sdcard.h"
}

//#include "delay.h"
#include "TFTLCD/lcd_base.h"
#include "TFTLCD/ssd1289.h"
#include "SSD1289_TouchScreen/TouchPanel.h"
#include "GUI/GUI.h"
#include "GUI/GUIButton.h"
#include "GUI/GUILabel.h"
#include "GUI/GUIEditBox.h"
#include "GUI/GUIListBox.h"
#include "GUI/Component.h"
#include "GUI/EventMethods.h"
#include "usart/uartlib.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_pwm.h"

#include "main.h"

RCC_ClocksTypeDef RCC_Clocks;
__IO uint8_t RepeatState = 0;
__IO uint16_t CCR_Val = 100;
extern __IO uint8_t LED_Toggle;


GUI *current_gui_for_timer;

uint8_t tx_buf[512];
uint8_t rx_buf[512];
void OutPutFile(void);

int TouchPanelExperimentalValues[6] = {696,935,3187,1301,2141,3395};
int Ssens[3];
int Dsens[3];
uint32_t ds[6];

void int2bin(uint32_t data,char vector[33])
{
		int i;
		
		for (i=0;i<32;i++)
				vector[i]=(char)(((data>>(31-i))&1)+'0');
		
		vector[32]=0;
}

//aici vin scenariile de eroare luate in calcul in functie de anumite probleme aparute la diversi senzori sau motoare / relee
void UpdateEvents() 
{ 
		static int flag=0;
		
		/*if (flag)
			GPIO_SetBits(GPIOC , GPIO_Pin_9);
		else
			GPIO_ResetBits(GPIOC , GPIO_Pin_9);*/
			
		flag^=1;
}

void TIM_Config_EVENTS(void)
{
    //timerul pentru anumite evenimente pe GUI
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Set the Vector Table base address at 0x08000000 */
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);
    /* Configure the Priority Group to 2 bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    /* Enable the TIM3 gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);         
}


void SetFonts(void)
{
	TerminusFont.Offset=32;
	TerminusFont.Width=8;
	TerminusFont.Height=12;
	TerminusFont.Position=TerminusCharOffsets;
	TerminusFont.Data=TerminusFontBitmaps;
	
	Font8x16.Offset=32;
	Font8x16.Width=8;
	Font8x16.Height=16;
	Font8x16.Position=Font8x16Offsets;
	Font8x16.Data=Font8x16Chars;
	
	TerminusBigFont.Offset=32;
	TerminusBigFont.Width=16;
	TerminusBigFont.Height=28;
	TerminusBigFont.Position=TerminusBigCharOffsets;
	TerminusBigFont.Data=TerminusBigFontBitmaps;	
}

void InitCommonVars(void)
{
}

/*
void SD_STUFF()
{
	SD_Error state;
	FATFS fs;                          
	DIR dirs;
	FILINFO finfo;		
	unsigned int a;
	FRESULT res;
	char path[16]={"0:/"};
	UINT br, bw;         // File R/W count
	FIL fsrc,fdst;
	char buffer[512];


	state=SD_Init();
  Delayms(100);
	printf("Init SD\r\n");
  Delayms(50);
   if(state==SD_OK)
		 {
			  printf("SD OK\r\n");
			}
			else
			{
				   printf("SD ERR\r\n");
			}			
		 printf("SD size: %dMB\r\n",SDCardInfo.CardCapacity>>20);

#if _USE_LFN
    finfo.lfname = Fs_LongFileName;
    finfo.lfsize = sizeof(Fs_LongFileName);
#endif

	printf("mounting:%d\r\n",f_mount(0, &fs));
	if (f_opendir(&dirs, path) == FR_OK) 
	{
    	while (f_readdir(&dirs, &finfo) == FR_OK)  
    	{
      		if (finfo.fattrib & AM_ARC) 
      		{
        		if(!finfo.fname[0]) break;        
        		printf("fname:%s\r\n",finfo.fname);
#if _USE_LFN
        		printf("fname:%s\r\n",finfo.lfname);
#endif
        		res = f_open(&fsrc, finfo.fname, FA_OPEN_EXISTING | FA_READ);
        		br=1;
				a=0;
				printf("buffer:");
				//for (;;) 
				{					
					for(a=0; a<512; a++) buffer[a]=0; 
		    	    res = f_read(&fsrc, buffer, sizeof(buffer), &br);
					printf("%s\r\n",buffer);	
		    	    if (res || br == 0) break;   // error or eof
        		}
				f_close(&fsrc);                 
			}
		} 
	}	
}*/

int main(void)
{			    
		RCC_ClocksTypeDef SYS_Clocks;
		RCC_GetClocksFreq(&SYS_Clocks);	
		TM_PWM_TIM_t PWM_Data;
		
		SystemInit();
		TM_DELAY_Init();
		PeripheralInit(); 
    
		UART_LowLevel_Init();
		printf("Initialized: USART2, bps=262500, TX=PA2, RX=PA3\r\n");	  
		//SysTick_Init();		
		/* Timer settings struct */				
		//printf("Initialized: Green LED\r\n");	  
		//TM_DISCO_LedInit();
		//TM_DISCO_LedOn(LED_GREEN);
		//TM_PWM_InitTimer(TIM2, &PWM_Data, 30000);
		//TM_PWM_InitChannel(TIM2, TM_PWM_Channel_1, TM_PWM_PinsPack_2);
		//TM_PWM_SetChannelPercent(TIM2, &PWM_Data, TM_PWM_Channel_1, 50);		
		//printf("Initialized: PWM on PA5 - 50%\r\n");	  
			
		printf("Setting Graphic FONTs...\r\n");
		SetFonts();
		
		printf("Initializing LCD...\r\n");
		SSD1289_LCD lcd;	
		printf("Initializare TouchScreen...\r\n");
    Touch tpl(&lcd);
		lcd.SetFont(&Font8x16);

		printf("SYSCLK: %dMHz\r\n",SYS_Clocks.SYSCLK_Frequency/1000000);
		printf("HCLK: %dMHz\r\n",SYS_Clocks.HCLK_Frequency/1000000);
		printf("PCLK1: %dMHz\r\n",SYS_Clocks.PCLK1_Frequency/1000000);
		printf("PCLK2: %dMHz\r\n\r\n",SYS_Clocks.PCLK2_Frequency/1000000);
		
    printf("Calibrare cu set predefinit...\r\n");
    tpl.TouchPanelExperimentalCalibrate(TouchPanelExperimentalValues);
    lcd.FillScreen(COLOR_CYAN);
		
    //main screen (4 butoane - [set lungime bucata - cu afisare valoare] / [set nr bucati - cu afisare valoare] / [START/STOP acelasi buton] / [Hidden cu parola pt configurare])
    printf("Initializare GUI...\r\n");
		
    GUI gui(&lcd,&tpl,0);
    current_gui_for_timer=&gui;
	
    //initializam doar fereastra cu meniul principal
		printf("Init First Window!\r\n");
    InitWindow(&gui,WINDOW_0);		
    
		//SD_STUFF();
  
    printf("Running........\r\n");
    gui.Run();    				
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){ while (1){}}
#endif
