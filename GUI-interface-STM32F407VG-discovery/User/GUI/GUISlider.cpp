#include "GUISlider.h"

Slider::Slider(SSD1289_LCD *lcd,OnEvent proc,int x,int y,int w,int h,int steps,int max_value,int increment,font_t *font,int font_color,int ID):GUIComponent(lcd,proc,x,y,w,h,ID)
{
    Font=font;
    this->steps=steps;
    xx=x;
    yy=y;
    ww=w;
    hh=h;
    color_font=font_color;
    color_border=0;
    initial=true;
    pas=0;
    value=0;
		max_val=max_value;
}

void Slider::ChangeSlider(int pas)
{
    this->pas=pas;
    value=(pas+1)*(max_val/steps);
		repaint=true;
}

void Slider::Reset(bool state)
{
    initial=state;  		
}

void Slider::Increment()
{
    if (pas<steps-1)
		{
			pas++;
			value=(pas+1)*(max_val/steps);
		}
		repaint=true;
}

void Slider::Decrement()
{
		if (pas>0)
		{
			pas--;
			value=(pas+1)*(max_val/steps);
		}
		repaint=true;
}

int Slider::ReadValue()
{
		return value;
}

void Slider::Redraw(void)
{
    font_t *oldf;
    static int prev_data=1;
    char data[10];
		int i;
      
    oldf=_lcd->GetFont();
    _lcd->SetFont(Font);    
    
    if (initial)
    {        
        _lcd->DrawRect(xx,yy,xx+ww+1,yy+hh,color_border);				
				sprintf(data," %d",value);
				_lcd->FillRect(xx,yy,xx+ww+4*Font->Width,yy+hh,COLOR_LIGHT_GRAY);
        _lcd->Print(data,xx+ww,yy+hh/2-Font->Width/2,color_font);
				_lcd->DrawLine(xx+5,yy+hh/2,xx+ww-5,yy+hh/2,COLOR_BLUE);
				for (i=0;i<steps;i++)
					_lcd->FillRect(xx+10+i*(ww/steps)-2,yy+hh/4,xx+10+i*(ww/steps)+2,yy+hh-hh/4,0);
				_lcd->FillRect(xx+10-2,yy+hh/4,xx+10+2,yy+hh-hh/4,COLOR_RED);
				initial=false;    
    }
    else
    {
				sprintf(data," %d",value);
				_lcd->FillRect(xx+ww,yy,xx+ww+4*Font->Width,yy+hh,COLOR_GRAY);
        _lcd->Print(data,xx+ww,yy+hh/2-Font->Width/2,color_font);
				for (i=0;i<steps;i++)
					_lcd->FillRect(xx+10+i*(ww/steps)-2,yy+hh/4,xx+10+i*(ww/steps)+2,yy+hh-hh/4,0);
				_lcd->FillRect(xx+10+pas*(ww/steps)-2,yy+hh/4,xx+10+pas*(ww/steps)+2,yy+hh-hh/4,COLOR_RED);
    }    
    _lcd->SetFont(oldf);
    repaint=false;
}

int Slider::TouchDown(int x, int y,void *data)
{
	  int pix_per_pas=(ww-20)/steps;
		printf("xstart=%d | x=%d | pixs=%d | pas=%d\r\n",xx,x,pix_per_pas,(x-xx)/pix_per_pas);
		ChangeSlider((x-xx)/pix_per_pas-1);
    event_proc(data);
    return GUI_PASS;
}

int Slider::TouchUp(int x,int y,void *data)
{    
    return GUI_PASS;
}

