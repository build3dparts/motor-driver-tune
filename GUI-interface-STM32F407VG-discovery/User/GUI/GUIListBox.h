#ifndef __GUI_LIST_BOX__
#define __GUI_LIST_BOX__

#include "Component.h"

#define MAX_LINE_SIZE 40
#define MAX_LINES     9
#define VISIBLE_LINES 9

#ifdef __cplusplus
extern "C" {
#endif


class ListBox:public GUIComponent
{
    public:
        ListBox(SSD1289_LCD *lcd,OnEvent proc,font_t *font,int sel_color,int font_color,int back_color,int border_color,int ID);
                
        virtual void AddLine(char *data);
				virtual void RemoveLine(int id);
        virtual void FreeData(void);
        virtual void Redraw(void);
        virtual void ResetInitialState();    
				
        virtual int TouchDown(int x, int y,void *data);
        virtual int TouchUp(int x, int y,void *data);  				
     
    protected:  
        font_t *Font;
        char **items;
        int focolor;
        int bkcolor;
        int bocolor;
				int secolor;
				int first;
				int total;
        int cline;  
				int prev_line;
        bool initial;
};

#ifdef __cplusplus
}
#endif


#endif