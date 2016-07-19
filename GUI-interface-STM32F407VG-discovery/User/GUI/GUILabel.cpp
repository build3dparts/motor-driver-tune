#include "GUILabel.h"

Label::Label(SSD1289_LCD *lcd,OnEvent proc,int x,int y,int w,int h,char *text,font_t *font,int font_color,int bcol1,int ID,ALIGN al):GUIComponent(lcd,proc,x,y,w,h,ID)
{
    Font=font;
    foreground=font_color;
    
    memcpy(label,text,strlen(text)+1);
    xx=x;
    yy=y;
    ww=w;
    hh=h;    
		
		align=al;
    
		background=bcol1;
}
        
void Label::ChangeLabel(char* text)
{
    memcpy(label,text,strlen(text)+1);
    repaint=true;
}

void Label::ChangeLabelColor(int new_color)
{
    foreground=new_color;
    repaint=true;
}

void Label::ChangeLabelBack(int new_color)
{
		background=new_color;
		repaint=true;
}

void Label::ResetColorBack(void)
{
		background=COLOR_CYAN;
		repaint=true;
}

void Label::Redraw(void)
{
    font_t *old_font;
    int startx,starty;
        
    old_font=_lcd->GetFont();
    _lcd->SetFont(Font);
    
		_lcd->FillRect(xx,yy,xx+ww,yy+hh,background);
		starty=yy+(hh-Font->Height)/2;    
		switch (align)
		{
			case _CENTER: startx=xx+(ww-strlen(label)*Font->Width)/2; break;
			case _LEFT:   startx=xx; break;
			case _RIGHT:  startx=xx+(ww-strlen(label)*Font->Width); break;				
		}
		_lcd->Print(label,startx,starty,foreground);
		_lcd->SetFont(old_font);
}


