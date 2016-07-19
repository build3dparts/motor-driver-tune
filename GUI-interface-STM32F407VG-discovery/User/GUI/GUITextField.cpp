#include "GUITextField.h"

TextField::TextField(SSD1289_LCD *lcd,OnEvent proc,int x,int y,int w,int h,font_t *font,bool splitter,int font_color,int back_color,int border_color,int ID):GUIComponent(lcd,proc,x,y,w,h,ID)
{
    int i;
    xx=x;
    yy=y;
    ww=w;
    hh=h;
    focolor=font_color;
    bkcolor=back_color;
    bocolor=border_color;
    Font=font;
    last=0;
    cline=0;
    cchar=0;
    items=(char**)malloc(10*sizeof(char*));
    for (i=0;i<10;i++)
    {
        items[i]=(char*)malloc(30);        
        memset(items[i],0,30);
    }
    split=splitter;
    initial=true;
}

void TextField::AddLine(char *data)
{    
    memcpy(items[last],data,strlen(data));
    last++;    
}

void TextField::FreeData(void)
{
    int i;
    
    for (i=0;i<10;i++)
        free(items[i]);
    free(items);
}

void TextField::AddChar(char ch)
{
    int i;
    items[cline][cchar]=ch;
    cchar++;    
    if (cchar==25)
    {
        cchar=0;
        cline++;   
    }
}

void TextField::ResetInitialState()
{
    int i;
    
    for (i=0;i<10;i++)
        memset(items[i],0,30);    
    cline=0;
    cchar=0;
    
    initial=true;
    repaint=true;
}

void TextField::Redraw(void)
{
    int i;
    font_t *oldc;
    
    if (initial)
    {
        _lcd->FillRect(xx,yy,xx+ww,yy+hh,bkcolor);
        _lcd->DrawRect(xx,yy,xx+ww,yy+hh,bocolor);
    }
    
    oldc=_lcd->GetFont();
    _lcd->SetFont(Font);

    for (i=0;i<10;i++)
        _lcd->Print(items[i],xx,yy+i*Font->Height,focolor);
    
    if (split)
        _lcd->DrawLine(xx+ww/2,yy+1,xx+ww/2,yy+hh-1,bocolor);

    _lcd->SetFont(oldc);
    initial=false;
}
