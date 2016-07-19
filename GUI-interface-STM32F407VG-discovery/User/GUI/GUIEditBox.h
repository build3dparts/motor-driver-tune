#ifndef __GUI_EDITBOX__
#define __GUI_EDITBOX__

#include "Component.h"

#ifdef __cplusplus
extern "C" {
#endif

class EditBox:public GUIComponent
{
    public:
        EditBox(SSD1289_LCD *lcd,OnEvent proc,int x,int y,int w,int h,font_t *font,int font_color,int back_color,int border_color,bool pwd,int ID);
        
        virtual void AddChar(char ch);
        virtual void RemoveLastChar();
        virtual void Clear();
        virtual void Redraw();
        virtual void ResetInitialState(bool state);
        virtual char *GetText();
        virtual void SetText(char *data);
     
    protected:  
        font_t *Font;
        char text[MAX_STRING_SIZE+1];
        int xx,yy,ww,hh;
        int fore;
        int background;
        int border;
        int prev_len;
        bool initial;
        bool is_pwd;
};

#ifdef __cplusplus
}
#endif


#endif
