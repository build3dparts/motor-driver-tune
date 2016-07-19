#include "GUIProgress.h"

Progress::Progress(SSD1289_LCD *lcd,OnEvent proc,int x,int y,int w,int h,int steps,int start_step,font_t *font,int border,int font_color,int bkfont,int bcol1,int bcol2,int bcol3,int ID):GUIComponent(lcd,proc,x,y,w,h,ID)
{
    Font=font;
    steps_total=steps;
    xx=x;
    yy=y;
    ww=w;
    hh=h;
    color_font=font_color;
    color_back_font=bkfont;
    color_border=border;
    b1=bcol1;
    b2=bcol2;
    b3=bcol3;
    initial=true;
    steps_per_percent=(double)steps_total/100;
    current_step=start_step;
    percent=(current_step*100)/steps; 
    oldper=0;
    next_x=0;
    prev_x=0;
}

void Progress::AddSteps(int pasi)
{
    current_step+=pasi;
    percent=current_step/steps_per_percent;
    next_x=(double)current_step/((double)steps_total/ww);   
    
    if (prev_x!=next_x)
    {
        repaint=true;
        prev_x=next_x;
    }
    else
        repaint=false;
}

void Progress::ResetInitialState(bool state)
{
    initial=state;    
}

void Progress::Redraw(void)
{
    font_t *oldf;
    static int prev_data=1;
    char data[10];
    
    if (percent>100)
        return;
    
    oldf=_lcd->GetFont();
    _lcd->SetFont(Font);
    
    //debug.printf("initial = %d | next_x = %d\r\n",initial,(int)next_x);
    
    if (initial)
    {        
        _lcd->FillRect(xx,yy,xx+ww,yy+hh,COLOR_WHITE);
        _lcd->DrawRect(xx,yy,xx+ww+1,yy+hh,color_border);
        sprintf(data,"%d%%",(int)percent);
        _lcd->Print(data,xx+ww/2-strlen(data)*Font->Width/2,yy+hh+5,color_font);
        _lcd->FillRect(xx+1,yy+1,xx+(int)(percent*ww/100),yy+hh,b1);
        initial=false;    
        prev_data=1;
    }
    else
    {
        _lcd->FillRect(xx+prev_data,yy+1,xx+next_x,yy+hh-1,b1);
        prev_data=next_x;
        sprintf(data,"%d%%",(int)percent);
        _lcd->FillRect(xx+ww/2-strlen(data)*Font->Width/2,yy+hh+5,xx+ww/2+strlen(data)*Font->Width/2,yy+hh+5+Font->Height,color_back_font);
        _lcd->Print(data,xx+ww/2-strlen(data)*Font->Width/2,yy+hh+5,color_font);       
    }
    
    _lcd->SetFont(oldf);
    repaint=false;
}

