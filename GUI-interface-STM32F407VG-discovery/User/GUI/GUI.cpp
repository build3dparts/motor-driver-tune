#include "GUI.h"
#include "WindowID.h"
#include "EventMethods.h"
#include "main.h"
#include "adc.h"
#include "tm_stm32f4_delay.h"

#define DEBUG_TOUCH_SCREEN        //chestia asta decomentata ar trebui sa arate pe serial valorile primite de la TOUCH_SCREEN

extern bool job_start;
extern int bucata_curenta;
extern int numar_bucati;
extern int adc_vals[2];

GUI::GUI(SSD1289_LCD *lcd,Touch *touch,int window)
{
    int i;
    _lcd=lcd;
    _touch=touch;
    memset(numcomponents,0,MAX_WINDOWS*sizeof(int));
    CurrentWindow=window;
    
    printf("Alocam [%d] ferestre pentru obiecte\r\n",MAX_WINDOWS);
    components=(GUIComponent***)malloc(MAX_WINDOWS*sizeof(GUIComponent**));
    memset(components,0,MAX_WINDOWS*sizeof(GUIComponent**));    
    for (i=0;i<MAX_WINDOWS;i++)
    {
        printf("Alocam [%d] componente pentru fereastra [%d]\r\n",MAX_COMPONENTS,i);
        components[i] = (GUIComponent**)malloc(MAX_COMPONENTS*sizeof(GUIComponent*));
        memset(components[i],0,MAX_COMPONENTS*sizeof(GUIComponent*));    
    }
    can_change_window=true;
    printf("Clear deallocation vector\r\n");
    memset(must_deallocate,0,MAX_WINDOWS*sizeof(int));
}

SSD1289_LCD *GUI::GetLCD()
{
	return _lcd;
}

Touch *GUI::GetTouch()
{
	return _touch;
}

void GUI::PrepareDealocation(int wnidow)
{
    must_deallocate[wnidow]=1;
}

void GUI::DealocateWindow(int window)
{
    int i;
    
    //printf("dealocam obiectele de pe fereastra [%d]\r\n",window);
    
    for (i=0;i<numcomponents[window];i++)
        free(components[window][i]);
    numcomponents[window]=0;
}

int GUI::GetWindow()
{
    return CurrentWindow;
}

GUIComponent *GUI::GetComponentByID(int id,int win)
{
    int i;
    
    for (i=0;i<numcomponents[win];i++)
        if (id==components[win][i]->GetID())
            return components[win][i];
    return NULL;
}

void GUI::AddComponent(GUIComponent *comp,int window)
{
    int i=numcomponents[window];

    numcomponents[window]++;
    printf("[AddComponent]: 1 component added on window %d. Total Components = %d\r\n",window, numcomponents[window]);
    components[window][i]=comp;
    printf("[AddComponent]: New component @ 0x%08X\r\n",components[window][i]);
}

void GUI::ChangeWindow(int window)
{
    int i;
    
    if (WindowReady())
    {
        CurrentWindow=window;
        printf("[ChangeWindow]: current_window = %d | components = %d | force repaint\r\n",window,numcomponents[CurrentWindow]);
        
        //fortam componentele sa faca repaint        
        for (i=0;i<numcomponents[CurrentWindow];i++)
        {
            printf("Repaint component @ 0x%08X\r\n",components[CurrentWindow][i]);
            components[CurrentWindow][i]->SetRepaint(true);
        }
        
        //clear window
        printf("[ChangeWindow]: clear window\r\n");
        _lcd->FillScreen(COLOR_CYAN);        
        
        //dealocam fereastra anterioara        
        for (i=0;i<MAX_WINDOWS;i++)
        {
            if (must_deallocate[i])
            {
                printf("[ChangeWindow]: Dealocam fereastra %d\r\n",i);
                must_deallocate[i]=0;
                DealocateWindow(i);
            }
        }
        
        //fortam un eveniment inainte de schimbarea ferestrei, ca sa nu avem cazul in care schimbam cu eroare ferestre consecutive, fara evenimente relevante
        can_change_window=false;
    }
}

void GUI::TranzitFereastra(int win_from,int win_to)
{     
    printf("tranzit window %d->%d\r\n",win_from,win_to);
    InitWindow(this,win_to);
    PrepareDealocation(win_from);           
    ChangeWindow(win_to);         
}

void GUI::Display(TOUCH_event *event)
{
    int i;

    for ( i=0; i<numcomponents[CurrentWindow]; ++i ) 
    {
        if (components[CurrentWindow][i]->MustRepaint())
        {
            printf("[Display]: Repaint Component %d on Window %d\r\n",i,CurrentWindow);
            components[CurrentWindow][i]->Redraw();
            components[CurrentWindow][i]->SetRepaint(false);
            can_change_window=true;
        }
    }
}

bool GUI::WindowReady()
{
    return can_change_window;
}

void GUI::HandleEvent(TOUCH_event *event)
{
    int i;
    GUI_PACKET gui_data;
    
    switch (event->type) 
    {
        case TOUCH_DOWN:        
        case TOUCH_UP:
             for (i=0; i<numcomponents[CurrentWindow]; i++) 
            {     
                if (can_change_window)
                { 
                    gui_data.gui=this;
                    gui_data.ID=components[CurrentWindow][i]->GetID();
                    gui_data.window=CurrentWindow;
                    components[CurrentWindow][i]->HandleEvent(event,(void*)&gui_data);
                }
                else
                {
                    printf("Am blocat un eveniment declansat de fereastra %d\r\n",CurrentWindow);
                    printf("Motiv: Nu am voie sa schimb fereastra!\r\n");
                }
            }
            break;

        default:
            break;
    }
}

void GUI::PostTimerEvents()
{  
    GUI_PACKET gui_data;
    gui_data.gui=this;
    gui_data.ID=NULL;
    gui_data.window=CurrentWindow;    
    ProcesariFerestre((void*)&gui_data);
}

void GUI::Run()
{
    do 
    {
        Display(&event);
        if (_touch->GetTouchState(&event))
            HandleEvent(&event);   					
				PostTimerEvents();
        Delayms(5);
    } while ( true );
}
