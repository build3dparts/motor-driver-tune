#include "GUIButton.h"
 
 Button::Button(SSD1289_LCD *lcd,OnEvent proc,int x, int y, int w, int h,char *text,font_t *font,int bcolor,int ID,bool ct3d):GUIComponent(lcd,proc,x,y,w,h,ID)
 {
    ButtonFont=font;
    freefont=0;
    freeButton=1;
    color=bcolor;
    
    memcpy(label,text,strlen(text)+1);
    xx=x;
    yy=y;
    ww=w;
    hh=h;   

		ctl3d=ct3d;
    
    pressed=0;
 }
 
 char * Button::GetLabel()
 {
    return label;
 }

void Button::Redraw(void)
{  
    int lx;
    int i,tokens,data[5];
    int starty,l;
    font_t *old_font;
    
		if (ctl3d)
		{
			_lcd->FillRect(xx,yy,xx+ww,yy+hh,color); 
			_lcd->DrawLine(xx,yy,xx+ww-1,yy,COLOR_WHITE);
			_lcd->DrawLine(xx,yy+1,xx+ww-1,yy+1,COLOR_WHITE);
			_lcd->DrawLine(xx,yy,xx,yy+hh-1,COLOR_WHITE);
			_lcd->DrawLine(xx+1,yy,xx+1,yy+hh-1,COLOR_WHITE);
			_lcd->DrawLine(xx+ww,yy+2,xx+ww,yy+hh,COLOR_BLACK);			
			_lcd->DrawLine(xx+2,yy+hh,xx+ww,yy+hh,COLOR_BLACK);			
		}
    else
			_lcd->FillRect(xx,yy+1,xx+ww,yy+hh-1,color); 
                             
    
    tokens=1;
    data[0]=0;
    l=strlen(label);
    for (i=0;i<l;i++)
    {
        if (label[i]==' ')
        {
            label[i]=0;
            data[tokens]=i+1;
            tokens++;
        }
    }
		
    old_font=_lcd->GetFont();
    _lcd->SetFont( ButtonFont );
    starty=yy+(hh-tokens*ButtonFont->Height)/2;
    for (i=0;i<tokens;i++)
    {
        lx=xx+ww/2-(strlen(label+data[i])*ButtonFont->Width)/2;
        _lcd->Print(label+data[i],lx,starty+ButtonFont->Height*i,COLOR_BLACK);
    }
    _lcd->SetFont( old_font );
    for (i=0;i<l;i++)
    {
        if (label[i]==0)
            label[i]=' ';
    }    
}

int Button::TouchDown(int x, int y,void *data)
{
    event_proc(data);
    return GUI_PASS;
}

int Button::TouchUp(int x,int y,void *data)
{    
    return GUI_PASS;
}

