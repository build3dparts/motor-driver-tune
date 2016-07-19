#ifndef __GUI_DESKTOP__
#define __GUI_DESKTOP__


#include "TFTLCD/ssd1289.h"
#include "SSD1289_TouchScreen/TouchPanel.h"
#include "GUI/Component.h"

#define MAX_COMPONENTS 50
#define MAX_WINDOWS 50

#ifdef __cplusplus
extern "C" {
#endif

class Desktop{
    public:
        Desktop(SSD1289_LCD *lcd,Touch *touch,char *name);
        void AddComponent(GUIComponent *comp,int parent_win);
        void Display();
        void ChangeWindow(int window);
        void Run();
        int GetWindow();
        void PrepareDealocation(int widow);
        void DealocateWindow(int window);
        GUIComponent *GetComponentByID(int id,int parent_win);
        void TranzitFereastra(int win_from,int win_to);
				SSD1289_LCD *GetLCD();
				Touch *GetTouch();
        bool WindowReady();
				void HandleEvent(TOUCH_event *event,Desktop *curent); 
        
    protected:
        SSD1289_LCD *_lcd;
        TOUCH_event event;
        Touch *_touch;
				char *deskname;
        int numcomponents[MAX_WINDOWS];
        int must_deallocate[MAX_WINDOWS];
        GUIComponent ***components;       
        int CurrentWindow;
        bool can_change_window;
};

#ifdef __cplusplus
}
#endif




#endif