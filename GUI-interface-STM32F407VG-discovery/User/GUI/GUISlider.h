#ifndef __GUI_SLIDER__
#define __GUI_SLIDER__

#include "Component.h"

#ifdef __cplusplus
extern "C" {
#endif

class Slider:public GUIComponent
{
    public:
        Slider(SSD1289_LCD *lcd,OnEvent proc,int x,int y,int w,int h,int steps,int max_value,int increment,font_t *font,int font_color,int ID);
        void ChangeSlider(int pas);
				void Increment();
				void Decrement();
        virtual void Redraw(void);      
        virtual void Reset(bool state);
        virtual int TouchDown(int x, int y,void *data);
        virtual int TouchUp(int x, int y,void *data);  				
				int ReadValue();
     
    protected:  
        font_t *Font;
				int pas;
				int value;
				int steps;
        int xx,yy,ww,hh;
        int color_font;
        int color_border;
        bool initial;
				int max_val;
};

#ifdef __cplusplus
}
#endif


#endif
