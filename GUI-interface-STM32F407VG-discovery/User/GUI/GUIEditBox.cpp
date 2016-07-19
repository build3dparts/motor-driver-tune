#include "GUIEditBox.h"

EditBox::EditBox(SSD1289_LCD *lcd,OnEvent proc,int x,int y,int w,int h,font_t *font,int font_color,int back_color,int border_color,bool pwd,int ID):GUIComponent(lcd,proc,x,y,w,h,ID)
{
    xx=x;
    yy=y;
    ww=w;
    hh=h;
    Font=font;
    fore=font_color;
    
    memset(text,0,sizeof(text));
    fore=font_color;
    background=back_color;
    border=border_color;
    prev_len=0;
    initial=true;
    
    is_pwd=pwd;
}

char *EditBox::GetText()
{
    return text;
}

void EditBox::AddChar(char ch)
{
    int l;
    
    if (!text[0])
        text[0]=ch;
    else
    {
        l=strlen(text);
        if (l<sizeof(text))
            text[l]=ch;
        prev_len++;
    }
    
    repaint=true;
}

void EditBox::SetText(char *data)
{
    memcpy(text,data,strlen(data)+1);
    repaint=true;
    prev_len=strlen(text);
}

void EditBox::RemoveLastChar()
{
    int l;
    
    if (text[0])
    {
        l=strlen(text);
        prev_len=l;
        l--;      
        text[l]=0;        
    }
    
    repaint=true;
}

void EditBox::Clear()
{
    memset(text,0,sizeof(text));
    prev_len=0;
    repaint=true;
}

void EditBox::ResetInitialState(bool state)
{
    initial=state;    
}

void EditBox::Redraw(void)
{
    font_t *old_font;
        
    old_font=_lcd->GetFont();
    _lcd->SetFont(Font);
    
    if (initial)
    {
        _lcd->DrawRect(xx,yy,xx+ww,yy+hh,border);
        _lcd->FillRect(xx+1,yy+1,xx+ww-1,yy+hh-1,background);
        prev_len=0;
        memset(text,0,sizeof(text));
        initial=false;
    }
    else
    {
        if (prev_len<strlen(text))
        {
            if (!is_pwd)
                _lcd->Print(text+prev_len,xx+2+prev_len*Font->Width,yy+2,fore); 
            else
                _lcd->Print("*",xx+2+prev_len*Font->Width,yy+2,fore); 
        }
        else
        if (prev_len>strlen(text))
        {
            _lcd->FillRect(xx+2+strlen(text)*Font->Width,yy+2,xx+2+strlen(text)*Font->Width+Font->Width,yy+2+Font->Height,background);
        }
        else
        {
            _lcd->FillRect(xx+1,yy+1,xx+ww-1,yy+hh-1,background);
            _lcd->Print(text,xx+1,yy+1,fore); 
        }
    }
    
    
    _lcd->SetFont(old_font);           
}
