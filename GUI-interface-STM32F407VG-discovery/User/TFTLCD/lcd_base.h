#ifndef TFTLCD_BASE_H
#define TFTLCD_BASE_H

#include "terminus.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RGB(red, green, blue) (int) (((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3))
#define swap( type, a, b )      { type tmp = ( a ); ( a ) = ( b ); ( b ) = tmp; }

#define COLOR_BLACK             RGB( 0x00, 0x00, 0x00 )
#define COLOR_WHITE             RGB( 0xFF, 0xFF, 0xFF )
#define COLOR_RED               RGB( 0xFF, 0x00, 0x00 )
#define COLOR_GREEN             RGB( 0x00, 0xFF, 0x00 )
#define COLOR_BLUE              RGB( 0x00, 0x00, 0xFF )
#define COLOR_CYAN              RGB( 0x00, 0xFF, 0xFF )
#define COLOR_MAGENTA           RGB( 0xFF, 0x00, 0xFF )
#define COLOR_YELLOW            RGB( 0xFF, 0xFF, 0x00 )
#define COLOR_GRAY              RGB( 0x80, 0x80, 0x80 )
#define COLOR_LIGHT_GRAY        RGB( 0xC0, 0xC0, 0xC0 )
#define COLOR_DARK_ORANGE       RGB( 0xFF, 0x80, 0x80 )
#define COLOR_VIOLET            RGB( 0x80, 0x80, 0xFF )
#define COLOR_MAROON            RGB( 0xFF, 0x80, 0x80 )
#define COLOR_WORM_GREEN        RGB( 0x80, 0xFF, 0x80 )
#define COLOR_LIGHT_RED         RGB( 0xFF, 0xC0, 0xC0 )
#define COLOR_LIGHT_BLUE        RGB( 0xC0, 0xC0, 0xFF )
#define COLOR_AQUA              RGB( 0x80, 0xFF, 0xFF )
#define COLOR_PINK              RGB( 0xFF, 0x80, 0xFF )
#define COLOR_LIGHT_YELLOW      RGB( 0xFF, 0xFF, 0x80 )
#define COLOR_LIME              RGB( 0x10, 0xFF, 0x80 )
#define LIGHT_RED               RGB( 0xFF, 0x80, 0x80 )
#define COLOR_DARK_RED          RGB( 0x80, 0x00, 0x00 )
#define COLOR_DARK_BLUE         RGB( 0x00, 0x00, 0x80 )
#define COLOR_DARK_GREEN        RGB( 0x00, 0x80, 0x00 )
#define COLOR_OLIVE             RGB( 0x80, 0x80, 0x00 )
#define COLOR_NAVY              RGB( 0x00, 0x80, 0x80 )
#define COLOR_ORANGE            RGB( 0xFF, 0x80, 0x40 )

enum Orientation_enum
{
    PORTRAIT = 0, 
    LANDSCAPE = 1,
    PORTRAIT_REV = 2,
    LANDSCAPE_REV = 3, 
};
typedef enum Orientation_enum orientation_t;

enum Alignment_enum
{
    LEFT = 0, 
    CENTER = 9998, 
    RIGHT = 9999, 
};
typedef enum Alignment_enum align_t;

typedef struct _DIB{
    uint32_t header_sz;
    uint32_t Width;
    uint32_t Height;
    uint16_t color_planes;
    uint16_t bpp;
    uint32_t compresion_method;
    uint32_t raw_bmp_size;
    uint32_t horiz_res;
    uint32_t vert_res;
    uint32_t nr_colors;
    uint32_t important_colors;  
}__attribute__((packed))DIB;

typedef struct _BMP{
    uint16_t BMP_sig;
    uint32_t BMP_size;
    uint32_t reserved;
    uint32_t bmpoffset; 
    DIB dib_data;
}__attribute__((packed))BMP;

extern  BMP *splashscreen;

class LCD
{
	public:
			virtual void Initialize( orientation_t orientation) = 0;
			virtual void SetFont( font_t* font );
			virtual font_t* GetFont();
			unsigned short GetWidth( void );
			unsigned short GetHeight( void );
			uint8_t GetFontWidth( void );
			uint8_t GetFontHeight( void );
			virtual void FillScreen( int color = -1 );
			virtual void ClearScreen( void );
			virtual void DrawPixel( unsigned short x, unsigned short y, int color = -2 );
			virtual void DrawLine( unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, int color = -2 );
			virtual void DrawRect( unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, int color = -2 );
			virtual void DrawRoundRect( unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, int color = -2 );
			virtual void FillRect( unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, int color = -2 );
			virtual void FillGradientRect(int x1,int y1,int x2,int y2,int g1,int g2,int g3);
			virtual void FillRoundRect( unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, int color = -2 );
			virtual void Print( const char *str, unsigned short x, unsigned short y, int fgColor = -2);
			virtual void DisplayBMP(int x,int y,BMP *bmpdata);
			
	protected:
			LCD( unsigned short width, unsigned short height );			
			virtual void WriteCmdData( uint16_t cmd, uint16_t data ) = 0;
			virtual void LCD_SetCursor( uint16_t Xpos, uint16_t Ypos ) = 0;
			virtual void LCD_WriteIndex(uint16_t index) = 0;
			virtual void LCD_WriteData(uint16_t data) = 0;	
			virtual void DrawHLine( unsigned short x, unsigned short y, unsigned short len, int color = -2 );
			virtual void DrawVLine( unsigned short x, unsigned short y, unsigned short len, int color = -2 );
			virtual void PrintChar( char c, unsigned short x, unsigned short y, int fgColor = -2);

	protected:
			unsigned short  _disp_width, _disp_height;
			orientation_t   _orientation;
			font_t*   _font;
};

#ifdef __cplusplus
}
#endif

#endif
