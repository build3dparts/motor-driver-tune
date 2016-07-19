#ifndef __GUI_LABEL__
#define __GUI_LABEL__

#include "Component.h"

#ifdef __cplusplus
extern "C" {
#endif

enum ALIGN{
	_LEFT,
	_RIGHT,
	_CENTER
};

class Label:public GUIComponent
{
    public:
        Label(SSD1289_LCD *lcd,OnEvent proc,int x,int y,int w,int h,char *text,font_t *font,int font_color,int bcol1,int ID,ALIGN al=_CENTER);
        
        virtual void ChangeLabel(char* text);
        virtual void Redraw(void);     
        virtual void ChangeLabelColor(int new_color);
				virtual void ChangeLabelBack(int new_color);
				virtual void ResetColorBack(void);
     
    protected:  
        font_t *Font;
        char label[MAX_STRING_SIZE+1];
        int xx,yy,ww,hh;
        int current_window;
        int foreground;
        int background;
				ALIGN align;
};

#ifdef __cplusplus
}
#endif


#endif
