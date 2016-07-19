#include "GUI.h"
#include "Component.h"

GUIComponent::GUIComponent(SSD1289_LCD *lcd,OnEvent proc, int x, int y, int w, int h,int ID)
{
    Init(x, y, w, h);
    _lcd=lcd;
    repaint=true;
    event_proc=proc;
    component_ID=ID;
}

int GUIComponent::GetID(void)
{
    return component_ID;
}

int GUIComponent::MustRepaint()
{
    return repaint;
}

void GUIComponent::SetRepaint(bool state)
{
    repaint=state;
}

void GUIComponent::Init(int x, int y, int w, int h)
{
     SetRect(x, y, w, h);
    pressed=0;
}

void GUIComponent::SetRect(int x, int y, int w, int h)
{
    xx = x;
    yy = y;
    if ( w >= 0 )
        ww = w;
    if ( h >= 0 )
        hh = h;
}

int GUIComponent::HitRect(int x, int y)
{
    int hit;
    
    hit = 1;
    if ( (x < xx) || (x >= (xx+ww)) || (y < yy) || (y >= (yy+hh)) ) 
        hit = 0;
    return(hit);   
}

void GUIComponent::Redraw(void)
{
}

int GUIComponent::TouchDown(int x, int y,void *data)
{
    return(GUI_PASS);
}

int GUIComponent::TouchUp(int x, int y,void *data)
{
    return(GUI_PASS);
}

int GUIComponent::HandleEvent(TOUCH_event *event,void *event_data)
{
    GUI *_gui=((GUI_PACKET*)event_data)->gui;
    int id=((GUI_PACKET*)event_data)->ID;    

    switch (event->type) 
    {
        case TOUCH_DOWN: 
            {
                if ( HitRect(event->x, event->y) )                   
                {
                    //printf("[HandleEvent-TouchDown]: For component [%d] on Window [%d]\r\n",id,_gui->GetWindow());
                    return(TouchDown(event->x, event->y,event_data));
                }
            }
        break;
        case TOUCH_UP: 
            {
                if ( HitRect(event->x, event->y) )
                {
                    //printf("[HandleEvent-TouchUp]: For component [%d] on Window [%d]\r\n",id,_gui->GetWindow());
                    return(TouchUp(event->x, event->y,event_data));
                }
            }
        break;
        default: 
        break;
    }
    return(GUI_PASS);
}
