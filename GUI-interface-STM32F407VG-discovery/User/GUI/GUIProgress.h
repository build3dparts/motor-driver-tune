#ifndef __GUI_PROGRESS__
#define __GUI_PROGRESS__

#include "Component.h"

#ifdef __cplusplus
extern "C" {
#endif

class Progress:public GUIComponent
{
    public:
        Progress(SSD1289_LCD *lcd,OnEvent proc,int x,int y,int w,int h,int steps,int start_step,font_t *font,int border,int font_color,int bkfont,int bcol1,int bcol2,int bcol3,int ID);
        virtual void AddSteps(int pasi);
        virtual void Redraw(void);      
        virtual void ResetInitialState(bool state);
     
    protected:  
        font_t *Font;
        double percent;
        int xx,yy,ww,hh;
        int color_font;
        int color_border;
        int color_back_font;
        int b1,b2,b3;
        bool initial;
        double steps_per_percent;
        int steps_total;
        int current_step;
        double oldper;
        double next_x;
        double prev_x;
};

#ifdef __cplusplus
}
#endif


#endif
