#ifndef __GUI_TEXT_FIELD__
#define __GUI_TEXT_FIELD__

#include "Component.h"

#define MAX_LINE_SIZE 25
#define MAX_LINES     10

#ifdef __cplusplus
extern "C" {
#endif


class TextField:public GUIComponent
{
    public:
        TextField(SSD1289_LCD *lcd,OnEvent proc,int x,int y,int w,int h,font_t *font,bool splitter,int font_color,int back_color,int border_color,int ID);
                
        virtual void AddLine(char *data);
        virtual void FreeData(void);
        virtual void Redraw(void);
        virtual void AddChar(char ch);    
        virtual void ResetInitialState();    
     
    protected:  
        font_t *Font;
        int xx,yy,ww,hh;
        char **items;
        int focolor;
        int bkcolor;
        int bocolor;
        int last;
        int cline;   
        int cchar;     
        bool split;
        bool initial;
};

#ifdef __cplusplus
}
#endif


#endif