#ifndef INCLUDE_PANEL
#define INCLUDE_PANEL

#include "defs.h"
typedef int (*menuCallFunc)();

/**
 * a menu for the engine to use
 * you can specify many things including the key to exit the menu, the key to 
 * activate menu options, parent and child menus, choose what happens
 * when you activate a menu item
 * */
typedef struct Panel{
    //location options
    int startx;
    int starty;
    int scalex;
    int scaley;

    //text options
    char text[500];
    int textOffsetX;
    int textOffsetY;
    color_t textColor;

    //offset options
    int optionsOffsetX;
    int optionsOffsetY;

    //option options
    char options[500];
    menuCallFunc* optionFunctions;
    color_t optionColor;
    color_t selectionColor;
    int optionSpacing;
    
    int numOptions;
    int currentOption;
    
    //render options
    int inFocus;
    int rendering;

    //input options
    char activateKey;

    //visual options
    int highlightCurrentOption;
    int border;

    struct Panel* next;
}Panel;

/**
 * loads a new panel into the engine for rendering
 * */
Panel* PanelCreate(const char* text, int startx, int starty, int scalex, int scaley, int numOptions);

/**
 * updates the panel and returns the selected 
 * option. if no option was selected, the return is -1
 * */
int PanelUpdate(Panel* panel);

/**
 * frees a panel's memory
 */
void PanelFree(Panel* panel);

#endif
