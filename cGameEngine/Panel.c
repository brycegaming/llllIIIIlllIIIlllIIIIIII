#include "include/Panel.h"
#include "include/Ncurses.h"

Panel* PanelCreate(const char* text, int startx, int starty, int scalex, int scaley, int numOptions){
    Panel* ret;
    ret = (Panel*)malloc(sizeof(Panel));

    //set scale and start options
    ret->startx = startx;
    ret->starty = starty;
    ret->scalex = scalex;
    ret->scaley = scaley;

    //set instance and num options
    ret->numOptions = numOptions;

    //set the text
    strcpy(ret->text, text);

    //default options
    ret->border = 1;
    ret->textOffsetX = 0;
    ret->textOffsetY = 0;

    ret->optionsOffsetX = 0;
    ret->optionsOffsetY = 0;

    ret->optionFunctions = (menuCallFunc*)malloc(sizeof(menuCallFunc) * numOptions);

    ret->currentOption = 0;
    ret->inFocus = 1;
    ret->rendering = 1;

    ret->activateKey = CHAR_d;
    ret->next = NULL;

    ret->optionSpacing = 0;
    ret->optionColor = WHITE;
    ret->selectionColor = GREEN;
    ret->textColor = WHITE;

    return ret;
}

int PanelUpdate(Panel* panel){
    int input = getch();

    if(input == CHAR_s){
        panel->currentOption++;
    }
    else if(input == CHAR_w){
        panel->currentOption--;
    }
    else if(input == panel->activateKey){
        panel->optionFunctions[panel->currentOption]();
    }

    //clamp the value within the proper range
    panel->currentOption = MIN(panel->currentOption, panel->numOptions - 1);
    panel->currentOption = MAX(panel->currentOption, 0);

    return -1;
}

void PanelFree(Panel* panel){
    free(panel->optionFunctions);
    free(panel);
}


