#include "GUIMemo.h"

Memo::Memo(SSD1289_LCD *lcd,OnEvent proc,font_t *font,int font_color,int back_color,int border_color,int ID):GUIComponent(lcd,proc,0,40,320,145,ID)
{
    int i;
    focolor=font_color;
    bkcolor=back_color;
    bocolor=border_color;
    Font=font;
		first=0;
		total=0;
    cline=-1;
		prev_line=-1;
    items=(char**)malloc(MAX_LINES*sizeof(char*));
    for (i=0;i<MAX_LINES;i++)
    {
        items[i]=(char*)malloc(MAX_LINE_SIZE+1);        
        memset(items[i],0,MAX_LINE_SIZE+1);
    }
		initial=true;
		repaint=true;
}

void Memo::AddLine(char *data)
{    
		int len=strlen(data);
		int i;
		
		if (total<MAX_LINES)
		{
			if (len<MAX_LINE_SIZE)
				memcpy(items[total],data,len);
			else
			{
				memcpy(items[total],data,MAX_LINE_SIZE/2-2);
				memcpy(items[total]+MAX_LINE_SIZE/2-2,"....",4);
				memcpy(items[total]+MAX_LINE_SIZE/2+2,data+len-MAX_LINE_SIZE/2+2,MAX_LINE_SIZE/2-2);
			}			
			total++;    
		}
		else
		{
			for (i=1;i<MAX_LINES;i++)
				memcpy(items[i-1],items[i],MAX_LINE_SIZE);	
			memset(items[total-1],0,MAX_LINE_SIZE);
			if (len<MAX_LINE_SIZE)
				memcpy(items[total-1],data,len);
			else
			{
				memcpy(items[total-1],data,MAX_LINE_SIZE/2-2);
				memcpy(items[total-1]+MAX_LINE_SIZE/2-2,"....",4);
				memcpy(items[total-1]+MAX_LINE_SIZE/2+2,data+len-MAX_LINE_SIZE/2+2,MAX_LINE_SIZE/2-2);
			}				
		}
		repaint=true;
}

void Memo::RemoveLine(int id)
{    
   memset(items[id],' ',32);
	 repaint=true;
}

void Memo::FreeData(void)
{
    int i;
    
    for (i=0;i<MAX_LINES;i++)
        free(items[i]);
    free(items);
}

void Memo::ResetInitialState()
{
    int i;
    
    for (i=0;i<10;i++)
        memset(items[i],0,MAX_LINE_SIZE);    
    cline=0;
    
    initial=true;
    repaint=true;
}

void Memo::Redraw(void)
{
    int i;
    font_t *oldc;
    
    oldc=_lcd->GetFont();
    _lcd->SetFont(Font);		
		
    if (initial)
    {
        _lcd->FillRect(xx,yy,xx+ww,yy+hh,bkcolor);
        _lcd->DrawRect(xx,yy,xx+ww,yy+hh,bocolor);
				for (i=0;i<VISIBLE_LINES;i++)
				{
						if (first+i<VISIBLE_LINES)
						{
							_lcd->Print(items[first+i],0,yy+i*Font->Height,focolor);
							_lcd->DrawLine(0,yy+i*Font->Height,ww,yy+i*Font->Height,bocolor);
						}
				}			
				_lcd->DrawLine(0,yy+i*Font->Height,ww,yy+i*Font->Height,bocolor);
    }
		else
		{
				for (i=0;i<VISIBLE_LINES;i++)
				{
					_lcd->FillRect(1,yy+i*Font->Height+1,ww,yy+i*Font->Height+15,bkcolor);
					_lcd->Print(items[first+i],xx,yy+i*Font->Height,focolor);
				}			
		}

    _lcd->SetFont(oldc);
    initial=false;
}

int Memo::TouchDown(int x, int y,void *data)
{
    return GUI_PASS;
}

int Memo::TouchUp(int x,int y,void *data)
{    
    return GUI_PASS;
}

