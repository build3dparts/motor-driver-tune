#ifndef __GUI_BUTTON__
#define __GUI_BUTTON__

#include "Component.h"

#ifdef __cplusplus
extern "C" {
#endif

class Button:public GUIComponent
{
    public:
        Button(SSD1289_LCD *lcd,OnEvent proc,int x,int y,int w,int h,char *text,font_t *font,int bcolor,int ID,bool ct3d=true);
        
        virtual void Redraw(void);
        virtual int TouchDown(int x, int y,void *data);
        virtual int TouchUp(int x, int y,void *data);        
        virtual char *GetLabel();
     
    protected:  
        font_t *ButtonFont;
        char label[MAX_STRING_SIZE+1];
        int current_window;
        int freeButton,freefont;
        int color;
				bool ctl3d;
};

#ifdef __cplusplus
}
#endif


#endif
