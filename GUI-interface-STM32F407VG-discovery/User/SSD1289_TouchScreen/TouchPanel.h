#ifndef __TOUCH_PANEL__
#define __TOUCH_PANEL__

#include "TFTLCD/ssd1289.h"

#define Open_TP_CS_PIN									GPIO_Pin_4
#define Open_TP_CS_PORT									GPIOC
#define Open_TP_CS_CLK									RCC_AHB1Periph_GPIOC

#define Open_TP_IRQ_PIN									GPIO_Pin_5
#define Open_TP_IRQ_PORT								GPIOC
#define Open_TP_IRQ_CLK									RCC_AHB1Periph_GPIOC

#define TP_CS(x)	x ? GPIO_SetBits(Open_TP_CS_PORT,Open_TP_CS_PIN): GPIO_ResetBits(Open_TP_CS_PORT,Open_TP_CS_PIN)
#define TP_INT_IN   GPIO_ReadInputDataBit(Open_TP_IRQ_PORT,Open_TP_IRQ_PIN)

#define Open_RCC_SPI   	        				RCC_APB1Periph_SPI2
#define Open_GPIO_AF_SPI 								GPIO_AF_SPI2

#define Open_SPI                        SPI2
#define Open_SPI_CLK_INIT               RCC_APB1PeriphClockCmd
#define Open_SPI_IRQn                   SPI2_IRQn
#define Open_SPI_IRQHANDLER             SPI2_IRQHandler

#define Open_SPI_SCK_PIN                GPIO_Pin_13
#define Open_SPI_SCK_GPIO_PORT          GPIOB
#define Open_SPI_SCK_GPIO_CLK           RCC_AHB1Periph_GPIOB
#define Open_SPI_SCK_SOURCE             GPIO_PinSource13

#define Open_SPI_MISO_PIN               GPIO_Pin_14
#define Open_SPI_MISO_GPIO_PORT         GPIOB
#define Open_SPI_MISO_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define Open_SPI_MISO_SOURCE            GPIO_PinSource14

#define Open_SPI_MOSI_PIN               GPIO_Pin_15
#define Open_SPI_MOSI_GPIO_PORT         GPIOB
#define Open_SPI_MOSI_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define Open_SPI_MOSI_SOURCE            GPIO_PinSource15		


#ifdef __cplusplus
extern "C" {
#endif

typedef struct POINT 
{
   uint16_t x;
   uint16_t y;
}Coordinate;

typedef enum {
    TOUCH_DOWN,
    TOUCH_UP,    
} TOUCH_type;

typedef struct _TOUCH_event {
    TOUCH_type type;
    int x;
    int y;
} TOUCH_event;

typedef struct Matrix 
{                       
    long double An,Bn,Cn,Dn,En,Fn,Divider;
} Matrix ;

extern Coordinate ScreenSample[3];
extern Coordinate DisplaySample[3];
extern Matrix matrix ;
extern Coordinate  display ;

#define CHX     144
#define CHY     208

#define THRESHOLD 2

class Touch
{
    public:
        Touch(SSD1289_LCD *lcd);
        void InitializeTouch();
        Coordinate *ReadAds7846(void);
        void TouchPanelCalibrate(void);
        void TouchPanelExperimentalCalibrate(int *values);    //values must be in order (x y) topleft, (x y) topright, (x y) midbottom
        bool getDisplayPoint(Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr );
        bool GetTouchState(TOUCH_event *event);
        
    protected:
        int RDAD(void);
        int ReadX(void);
        int ReadY(void);
        void GetAdXY(int *x,int *y);
        void DrawPoint(int Xpos,int Ypos);
        void DrawCross(int Xpos,int Ypos);
        bool setCalibrationMatrix( Coordinate * displayPtr, Coordinate * screenPtr, Matrix * matrixPtr); 

				void ADS7843_SPI_Init(void);		
				void WR_CMD (uint8_t cmd);
		
		private:
				SSD1289_LCD *_lcd;
};


#ifdef __cplusplus
}
#endif


#endif