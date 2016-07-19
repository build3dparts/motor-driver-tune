#ifndef TFTLCD_SSD1289_H
#define TFTLCD_SSD1289_H

#include "lcd_base.h"

#define LCD_REG              (*((volatile unsigned short *) 0x60000000)) /* RS = 0 */
#define LCD_RAM              (*((volatile unsigned short *) 0x60020000)) /* RS = 1 */


#define  ILI9320    0  /* 0x9320 */
#define  ILI9325    1  /* 0x9325 */
#define  ILI9328    2  /* 0x9328 */
#define  ILI9331    3  /* 0x9331 */
#define  SSD1298    4  /* 0x8999 */
#define  SSD1289    5  /* 0x8989 */
#define  ST7781     6  /* 0x7783 */
#define  LGDP4531   7  /* 0x4531 */
#define  SPFD5408B  8  /* 0x5408 */
#define  R61505U    9  /* 0x1505 0x0505 */	   
#define  HX8347D    10 /* 0x0047 */
#define  HX8347A    11 /* 0x0047 */	
#define  LGDP4535   12 /* 0x4535 */  
#define  SSD2119    13 /* 3.5 LCD 0x9919 */

#ifdef __cplusplus
extern "C" {
#endif

class SSD1289_LCD : public LCD
{
	public:
			SSD1289_LCD();			
	
	protected:
			virtual void Initialize( orientation_t orientation = LANDSCAPE );
			virtual void WriteCmdData( uint16_t cmd, uint16_t data );
			virtual void LCD_WriteIndex(uint16_t index);
			virtual void LCD_WriteData(uint16_t data);
			virtual uint16_t LCD_ReadData(void);
			virtual uint16_t LCD_ReadReg(uint16_t LCD_Reg);
	
			virtual void LCD_SetCursor( uint16_t Xpos, uint16_t Ypos );
	
			virtual void LCD_CtrlLinesConfig(void);
			virtual void LCD_FSMCConfig(void);
			virtual void LCD_Initializtion(void);
		
	private:
			uint8_t LCD_Code;
};

#ifdef __cplusplus
}
#endif

#endif 
