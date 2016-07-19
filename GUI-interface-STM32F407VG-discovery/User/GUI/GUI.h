#ifndef __GUI__
#define __GUI__

#include "TFTLCD/ssd1289.h"
#include "SSD1289_TouchScreen/TouchPanel.h"
#include "GUI/Component.h"
#include "GUI/GUIDesktop.h"

#define MAX_DESKS 15
#define MAX_DESK_COMP 20

#ifdef __cplusplus
extern "C" {
#endif

class GUI{
    public:
        GUI(SSD1289_LCD *lcd,Touch *touch,int window);
        void AddComponent(GUIComponent *comp,int window);
        void Display(TOUCH_event *event);
        void ChangeWindow(int window);
        void Run();
        int GetWindow();
        void PrepareDealocation(int widow);
        void DealocateWindow(int window);
        GUIComponent *GetComponentByID(int id,int win);
        void PostTimerEvents();
        void TranzitFereastra(int win_from,int win_to);
				SSD1289_LCD *GetLCD();
				Touch *GetTouch();
        bool WindowReady();
        
    protected:
        SSD1289_LCD *_lcd;
        TOUCH_event event;
        Touch *_touch;
        int numcomponents[MAX_WINDOWS];
        int must_deallocate[MAX_WINDOWS];
        GUIComponent ***components;
        void HandleEvent(TOUCH_event *event);        
        int CurrentWindow;
        bool can_change_window;
};

typedef struct _GUI_PACKET{
    GUI *gui;
    int ID;
    int window;
}GUI_PACKET;


#ifdef __cplusplus
}
#endif


#endif
