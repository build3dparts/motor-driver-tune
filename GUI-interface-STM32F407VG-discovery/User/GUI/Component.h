#ifndef __GUI_COMPONENT__
#define __GUI_COMPONENT__

#include "SSD1289_TouchScreen/TouchPanel.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_STRING_SIZE 40

typedef enum {
    GUI_REDRAW,         
    GUI_YUM,          
    GUI_PASS,           
} GUI_status;

typedef enum {
    COMPONENT_VISIBLE,
    COMPONENT_HIDDEN,
} COMPONENT_status;

typedef void (*OnEvent)(void *data);

class GUIComponent
{
    public:
        GUIComponent(SSD1289_LCD *lcd,OnEvent proc, int x, int y, int w, int h,int ID);
    
        virtual void SetRect(int x, int y, int w, int h);
        virtual void GetRect(int *x, int *y, int *w, int *h) {*x=xx;*y=yy;*w=ww;*h=hh;}
        virtual int X() { return xx; }
        virtual int Y() { return yy; }
        virtual int W() { return ww; }
        virtual int H() { return hh; }
        virtual int HitRect(int x, int y);
        virtual void Redraw(void);
        virtual int TouchDown(int x, int y,void *data);
        virtual int TouchUp(int x, int y,void *data);
        virtual int HandleEvent(TOUCH_event *event,void *event_data);
        virtual int MustRepaint();
        virtual void SetRepaint(bool state);
        virtual int GetID(void);
    
    protected:
        SSD1289_LCD *_lcd;
        void Init(int x, int y, int w, int h);
        int xx,yy,ww,hh;
        int status;
        int pressed;
        bool repaint;
        OnEvent event_proc;
        int component_ID;
};

#ifdef __cplusplus
}
#endif


#endif
