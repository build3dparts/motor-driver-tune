#include "ssd1289.h"
#include "tm_stm32f4_delay.h"
//#include "delay.h"

SSD1289_LCD::SSD1289_LCD() : LCD(320,240)
{
	LCD_Initializtion();
}

void SSD1289_LCD::LCD_CtrlLinesConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	/* Enable GPIOs clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE , ENABLE);
	
	/* Enable FSMC clock */
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE); 

	/*-- GPIOs Configuration ------------------------------------------------------*/
	/*
	+-------------------+--------------------+------------------+------------------+
	+                       SRAM pins assignment                                   +

	+-------------------+--------------------+
	*/
	/* GPIOD configuration */
		/* Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
	 PD.10(D15), PD.11(A16), PD.14(D0), PD.15(D1) as alternate function push pull */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | 
	                            GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
								 GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
	 PE.14(D11), PE.15(D12) as alternate function push pull */	
	/* GPIOE configuration */
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource2 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2 | GPIO_Pin_7 | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 |
	                             GPIO_Pin_11| GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD,GPIO_Pin_7);
}

void SSD1289_LCD::LCD_FSMCConfig(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitStructure;
	
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
//	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 


	/* FSMC写速度设置 */
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = 15;//1;   /* 地址建立时间  */
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime = 0;	   
	FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime = 15;//1;	   /* 数据建立时间  */
	FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;	/* FSMC 访问模式 */
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;	  
	
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
	
	/* Enable FSMC Bank4_SRAM Bank */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}

void SSD1289_LCD::Initialize( orientation_t orientation )
{
    _orientation = orientation;
    
	u32 i=0x1fffff;
	LCD_CtrlLinesConfig();
	while(i--)
		;
	LCD_FSMCConfig();
}

void SSD1289_LCD::LCD_Initializtion(void)
{
	uint16_t DeviceCode;

	Initialize(LANDSCAPE);

	DeviceCode = 0x0123;
	DeviceCode = LCD_ReadReg(0x0000);		/* Read LCD ID	*/	
			 
//-------------------------------------------------SSD1289-----------------------------------------------------------------------		
	if( DeviceCode == 0x8989 )
	{
		LCD_Code = SSD1289;
		WriteCmdData(0x0000,0x0001);    Delayms(50);  // oscillator: 1 = on, 0 = off
		WriteCmdData(0x0003,0xA8A4);    Delayms(50);  // power control 
		WriteCmdData(0x000C,0x0000);    Delayms(50);  // power control 2 
		WriteCmdData(0x000D,0x080C);    Delayms(50);  // power control 3 
		WriteCmdData(0x000E,0x2B00);    Delayms(50);  // power control 4 
		WriteCmdData(0x001E,0x00B0);    Delayms(50);  // power control 5 
		WriteCmdData(0x0002,0x0600);    Delayms(50);  // driving waveform control
		WriteCmdData(0x0010,0x0000);    Delayms(50);  // sleep mode: 0 = exit, 1 = enter

		switch ( _orientation )
		{
			case LANDSCAPE: // works
				WriteCmdData( 0x01, 0x293F ); // driver output control
				Delayms(50);
				WriteCmdData( 0x11, 0x6078 ); // entry mode
				break;
				
			case PORTRAIT_REV: // works
				WriteCmdData( 0x01, 0x693F ); // driver output control
				Delayms(50);
				WriteCmdData( 0x11, 0x6070 ); // entry mode
				break;
				
			case LANDSCAPE_REV: // works
				WriteCmdData( 0x01, 0x6B3F ); // driver output control
				Delayms(50);
				WriteCmdData( 0x11, 0x6078 ); // entry mode
				break;
				
			case PORTRAIT: // works
			default:
				WriteCmdData( 0x01, 0x2B3F ); // driver output control
				Delayms(50);
				WriteCmdData( 0x11, 0x6070 ); // entry mode
				break;
		}
		
		WriteCmdData(0x0005,0x0000);    Delayms(50);	// compare register
		WriteCmdData(0x0006,0x0000);    Delayms(50);	// compare register
		WriteCmdData(0x0016,0xEF1C);    Delayms(50);	// horizontal porch
		WriteCmdData(0x0017,0x0003);    Delayms(50);	// vertical porch
		WriteCmdData(0x0007,0x0133);    Delayms(50);   // display control
		WriteCmdData(0x000B,0x0000);    Delayms(50);   // frame cycle control
		WriteCmdData(0x000F,0x0000);    Delayms(50);	// gate scan position
		WriteCmdData(0x0041,0x0000);    Delayms(50);   // vertical scroll control
		WriteCmdData(0x0042,0x0000);    Delayms(50);	// vertical scroll control
		WriteCmdData(0x0048,0x0000);    Delayms(50);	// 1st screen driving position
		WriteCmdData(0x0049,0x013F);    Delayms(50);	// 1st screen driving position
		WriteCmdData(0x004A,0x0000);    Delayms(50);	// 2nd screen driving position
		WriteCmdData(0x004B,0x0000);    Delayms(50);	// 2nd screen driving position
		WriteCmdData(0x0044,0xEF00);    Delayms(50);	// horizontal ram address position
		WriteCmdData(0x0045,0x0000);    Delayms(50);	// vertical ram address position
		WriteCmdData(0x0046,0x013F);    Delayms(50);	// vertical ram address position
		WriteCmdData(0x0030,0x0707);    Delayms(50);	// gamma control
		WriteCmdData(0x0031,0x0204);    Delayms(50);	// gamma control
		WriteCmdData(0x0032,0x0204);    Delayms(50);	// gamma control
		WriteCmdData(0x0033,0x0502);    Delayms(50);	// gamma control
		WriteCmdData(0x0034,0x0507);    Delayms(50);	// gamma control
		WriteCmdData(0x0035,0x0204);    Delayms(50);	// gamma control
		WriteCmdData(0x0036,0x0204);    Delayms(50);	// gamma control
		WriteCmdData(0x0037,0x0502);    Delayms(50);	// gamma control
		WriteCmdData(0x003A,0x0302);    Delayms(50);	// gamma control
		WriteCmdData(0x003B,0x0302);    Delayms(50);	// gamma control
		WriteCmdData(0x0023,0x0000);    Delayms(50);	// GRAM write mask for red and green pins
		WriteCmdData(0x0024,0x0000);    Delayms(50);	// GRAM write mask for blue pins
		WriteCmdData(0x0025,0x8000);    Delayms(50);	// frame frequency control
		WriteCmdData(0x004f,0);							// ram address set
		WriteCmdData(0x004e,0);							// ram address set

		WriteCmdData(0x0011,0x6068);					
	}				
  Delayms(50);
}

void SSD1289_LCD::WriteCmdData( unsigned short cmd, unsigned short data )
{
	LCD_WriteIndex(cmd);         
	LCD_WriteData(data); 		
}

void SSD1289_LCD::LCD_WriteIndex(uint16_t index)
{
	LCD_REG	= index;
}

void SSD1289_LCD::LCD_WriteData(uint16_t data)
{
	LCD_RAM = data;
}

uint16_t SSD1289_LCD::LCD_ReadData(void)
{
	return LCD_RAM;
}

uint16_t SSD1289_LCD::LCD_ReadReg(uint16_t LCD_Reg)
{
	LCD_WriteIndex(LCD_Reg);
	return LCD_ReadData();
}

void SSD1289_LCD::LCD_SetCursor( uint16_t Xpos, uint16_t Ypos )
{
	switch (_orientation)
	{
		case PORTRAIT:
				WriteCmdData(0x004e, Xpos );      
				WriteCmdData(0x004f, Ypos );  			
			break;
		case LANDSCAPE:
				WriteCmdData(0x004e, Ypos );      
				WriteCmdData(0x004f, Xpos );  
			break;		
	}        
}

