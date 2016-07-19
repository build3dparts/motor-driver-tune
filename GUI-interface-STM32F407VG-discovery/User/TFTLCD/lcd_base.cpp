#include "lcd_base.h"
#include <string.h>
#include <stdio.h>
 
LCD::LCD( unsigned short width, unsigned short height )
{
    _font = NULL;
	_disp_width=width;
	_disp_height=height;
}

void LCD::SetFont( font_t *font )
{
    _font = font;
}

font_t* LCD::GetFont(void)
{
    return (font_t*)_font;
}

inline unsigned short LCD::GetWidth( void )
{
	return _disp_width;
}

inline unsigned short LCD::GetHeight( void )
{
    return _disp_height;
}

inline uint8_t LCD::GetFontWidth( void )
{
    if ( _font != 0 ) 
			return _font->Width;
    return 0;
}

inline uint8_t LCD::GetFontHeight( void )
{
    if ( _font != 0 ) 
				return _font->Height;
    return 0;
}

void LCD::FillScreen( int color )
{	
	int i;
	LCD_SetCursor(0,0); 
	LCD_WriteIndex(0x0022);
	for( i = 0; i < _disp_width * _disp_height; i++ )
		LCD_WriteData(color);
}

inline void LCD::ClearScreen( void )
{
    FillScreen( 0 );
}

void LCD::DrawPixel( unsigned short x, unsigned short y, int color )
{
	if( x >= _disp_width || y >= _disp_height )
		return;
	LCD_SetCursor(x,y);
	WriteCmdData(0x0022,color);
}

void LCD::DrawLine( unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, int color )
{
	short dx,dy;
	short temp;

	if( x0 > x1 )
	{
		temp = x1;
		x1 = x0;
		x0 = temp;   
	}
	if( y0 > y1 )
	{
		temp = y1;
		y1 = y0;
		y0 = temp;   
	}

	dx = x1-x0;
	dy = y1-y0;

	if( dx == 0 )
	{
		do
		{ 
			DrawPixel(x0, y0, color);
			y0++;
		}while( y1 >= y0 ); 
		return; 
	}
	if( dy == 0 )
	{
		do
		{
			DrawPixel(x0, y0, color);
			x0++;
		}
		while( x1 >= x0 ); 
		return;
	}

	/* Bresenham's line algorithm  */
	if( dx > dy )
	{
		temp = 2 * dy - dx;
		while( x0 != x1 )
		{
			DrawPixel(x0,y0,color);
			x0++;
			if( temp > 0 )
			{
				y0++;
				temp += 2 * dy - 2 * dx; 
			}
			else         
			{
				temp += 2 * dy;
			}       
		}
		DrawPixel(x0,y0,color);
	}  
	else
	{
		temp = 2 * dx - dy;
		while( y0 != y1 )
		{
			DrawPixel(x0,y0,color);     
			y0++;                 
			if( temp > 0 )           
			{
				x0++;               
				temp+=2*dy-2*dx; 
			}
			else
			{
				temp += 2 * dy;
			}
		} 
		DrawPixel(x0,y0,color);
	}
}

void LCD::DrawRect( unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, int color )
{
    if ( x1 > x2 ) swap( uint16_t, x1, x2 )
    if ( y1 > y2 ) swap( uint16_t, y1, y2 )

    DrawHLine( x1, y1, x2 - x1, color );
    DrawHLine( x1, y2, x2 - x1, color );
    DrawVLine( x1, y1, y2 - y1, color );
    DrawVLine( x2, y1, y2 - y1, color );
}

void LCD::DrawRoundRect( unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, int color )
{
    if ( x1 > x2 ) swap( uint16_t, x1, x2 )
    if ( y1 > y2 ) swap( uint16_t, y1, y2 )

    if ( ( x2 - x1 ) > 4 && ( y2 - y1 ) > 4 )
    {
        DrawPixel( x1 + 1, y1 + 1, color );
        DrawPixel( x2 - 1, y1 + 1, color );
        DrawPixel( x1 + 1, y2 - 1, color );
        DrawPixel( x2 - 1, y2 - 1, color );
        DrawHLine( x1 + 2, y1, x2 - x1 - 4, color );
        DrawHLine( x1 + 2, y2, x2 - x1 - 4, color );
        DrawVLine( x1, y1 + 2, y2 - y1 - 4, color );
        DrawVLine( x2, y1 + 2, y2 - y1 - 4, color );
    }
}

void LCD::FillRect( unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, int color )
{
    if ( x1 > x2 ) swap( uint16_t, x1, x2 );
    if ( y1 > y2 ) swap( uint16_t, y1, y2 );

		int i,j;
    for ( int i = 0; i < y2 - y1 + 1; i++ )
    {
        //DrawHLine( x1, y1 + i, x2 - x1, color );
        //DrawHLine( x1, y2 - i, x2 - x1, color );
				LCD_SetCursor(x1,y1+i);
				LCD_WriteIndex(0x0022);		
				for ( j = 0; j < x2-x1+1; j++ )
						LCD_WriteData(color);				
    }
}

void LCD::FillGradientRect(int x1,int y1,int width,int height,int g1,int g2,int g3)
{
    FillRect(x1,y1,x1+width,y1+height,g2);
    /*
    float grad[100]={0};     
    int levels=height/2;
    int desc;
    int r,g,b;
    float rr,gg,bb;
    int i;
    //char msg[100];
    float rinc=0,binc=0,ginc=0;
    bool incdec;   
    int rc1,rc2,bc1,bc2,gc1,gc2; 
    
    //sprintf(msg,"g1=%X | g2=%X | g3=%X",g1,g2,g3);
    //Print(msg,0,66,COLOR_WHITE,COLOR_BLACK,0);    
    desc=g1^g2;
    
    rr=g1>>11;
    gg=(g1>>6)&0x1F;
    bb=g1&0x1F;
    
    rc1=rr;
    gc1=gg;
    bc1=bb;
    rc2=g2>>11;
    gc2=(g2>>6)&0x1F;
    bc2=g2&0x1F;
    
    if (rc1>rc2 || gc1>gc2 || bc1>bc2)
        incdec=false;
    else
        incdec=true;
    
    r=desc>>11;
    g=(desc>>6)&0x1F;
    b=desc&0x1F;
    
    rinc=r/(float)levels;
    ginc=g/(float)levels;
    binc=b/(float)levels;
        
    //sprintf(msg,"desc=%X | r=%X | g=%X | b=%X",desc,r,g,b);
    //Print(msg,0,50,COLOR_WHITE,COLOR_BLACK,0);
    //sprintf(msg,"rinc=%f",rinc);
    //Print(msg,0,140,COLOR_WHITE,COLOR_BLACK,0);    
    
    for (i=0;i<levels;i++)
    {
        grad[i]=RGB((int)rr,(int)gg,(int)bb);
        if (!incdec)
        {
            rr-=rinc;
            gg-=ginc;
            bb-=binc;
        }
        else
        {
            rr+=rinc;
            gg+=ginc;
            bb+=binc;        
        }        
    }
    //for (i=0;i<levels;i++)
    //    grad[levels+i]=g2;
    for (i=0;i<levels;i++)
    {
        grad[levels+i]=RGB((int)rr,(int)gg,(int)bb);
        if (!incdec)
        {
            rr+=rinc;
            gg+=ginc;
            bb+=binc;
        }
        else
        {
            rr-=rinc;
            gg-=ginc;
            bb-=binc;        
        } 
    }
    grad[levels]=grad[levels-1];

    for (i=0;i<height;i++)
        DrawHLine( x1, y1 + i, width, grad[i] ); */   
}

void LCD::FillRoundRect( unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, int color )
{
    if ( x1 > x2 ) swap( uint16_t, x1, x2 )
    if ( y1 > y2 ) swap( uint16_t, y1, y2 )

    if ( ( x2 - x1 ) > 4 && ( y2 - y1 ) > 4 )
    {
        for ( int i = 0; i < ( ( y2 - y1 ) / 2 ) + 1; i++ )
        {
            switch ( i )
            {
                case 0:
                    DrawHLine( x1 + 2, y1 + i, x2 - x1 - 4, color );
                    DrawHLine( x1 + 2, y2 - i, x2 - x1 - 4, color );
                    break;

                case 1:
                    DrawHLine( x1 + 1, y1 + i, x2 - x1 - 2, color );
                    DrawHLine( x1 + 1, y2 - i, x2 - x1 - 2, color );
                    break;

                default:
                    DrawHLine( x1, y1 + i, x2 - x1, color );
                    DrawHLine( x1, y2 - i, x2 - x1, color );
                    break;
            }
        }
    }
}

void LCD::Print( const char *str, unsigned short x, unsigned short y, int fgColor)
{
    int stl, i;

    stl = strlen( str );

    if ( x == RIGHT )
        x = GetWidth() - ( stl * _font->Width );
    if ( x == CENTER )
        x = ( GetWidth() - ( stl * _font->Width ) ) / 2;

    for ( i = 0; i < stl; i++ )
			PrintChar( *str++, x + ( i * ( _font->Width ) ), y, fgColor );
}

void LCD::DisplayBMP(int x,int y,BMP *bmpdata)
{   
    int line_size;
    int maxx,maxy,i,j;
     
    if (bmpdata->dib_data.Width>320)
        maxx=320;
    else
        maxx=bmpdata->dib_data.Width;

    if (bmpdata->dib_data.Height>240)
        maxy=240;
    else
        maxy=bmpdata->dib_data.Height;  
        
    line_size=((bmpdata->dib_data.bpp*bmpdata->dib_data.Width+31)/32)*4;  
        
    for (i=0;i<maxy;i++)
    {
        for (j=0;j<maxx;j++)
        {
            switch (bmpdata->dib_data.bpp)
            {
                case 16:
                    DrawPixel(x+j,y+i,((uint16_t*)((uint8_t*)bmpdata+bmpdata->bmpoffset+(bmpdata->dib_data.Height-1-i)*line_size))[j]);
                    break;
            }                   
        }
    }            
}

void LCD::DrawHLine( unsigned short x, unsigned short y, unsigned short len, int color )
{
		int i;
			
		LCD_SetCursor(x,y); 
		LCD_WriteIndex(0x0022);		
    for ( i = 0; i < len + 1; i++ )
				LCD_WriteData(color);
}

void LCD::DrawVLine( unsigned short x, unsigned short y, unsigned short len, int color )
{
    for ( int i = 0; i < len; i++ )
        DrawPixel( x,y+i,color );
}

//bg -1 = ignore / -2 = xor / -3 = not
void LCD::PrintChar( char c, unsigned short x, unsigned short y, int fgColor )
{
    uint8_t i, ch;
    uint16_t j,k;   
    int16_t position = _font->Position[ c - _font->Offset ];

	if ( position == -1 ) 
		position = 0;
    
    for ( j = 0; j < _font->Height; j++ )
    {
        for (k=0;k<_font->Width/8;k++)
        {
            ch = _font->Data[ position ];
            for ( i = 0; i < 8; i++ )
            {            
                if ( ( ch & ( 1 << ( 7 - i ) ) ) != 0 ) 
                {                    
                    DrawPixel(x+8*k+i, y+j,fgColor);
                }
            }
            position++;
        }
    }
}

