#include "include/Ncurses.h"
#include "include/GameObject.h"
#include "include/Texture.h"

static void addWindow(WINDOW* win, const char* tag, Instance* instance){
    //if there are currently no registered windows, it is quite easy to add a new one
    if(!instance->windows->window){
        instance->windows->window = win;
        strcpy(instance->windows->tag, tag);
        return;
    }

    Window* lastWindow = instance->windows;

    //find the last window in the list
    while(lastWindow->next){
        lastWindow = (Window*)lastWindow->next;
    }

    Window* next = malloc(sizeof(Window));
    next->window = win;
    next->prev = lastWindow;
    next->next = NULL;
    strcpy(next->tag, tag);

    lastWindow->next = (Window*)next;
}

void InstanceAddPanel(Instance* instance, Panel* panel){
    //find the last panel
    Panel* lastPanel = instance->menus;

    //if there are currently no panels, just set it to the one after the first
    if(lastPanel == NULL){
        instance->menus = panel;
        return;
    }

    while(lastPanel->next != NULL){
        lastPanel = lastPanel->next;
    }

    lastPanel->next = panel;
}

int InstanceRemovePanel(Instance* instance){
    Panel* lastPanel = instance->menus;
    Panel* prev = lastPanel;

    //if the first one is null, what the hell are we doiong here
    if(lastPanel == NULL){
        return 0;
    }

    if(lastPanel->next == NULL){
        //PanelFree(instance->menus);
        instance->menus = NULL;
        return 1;
    }

    while(lastPanel->next){
        prev = lastPanel;
        lastPanel = lastPanel->next;
    }
   
    prev->next = NULL;
    //PanelFree(lastPanel);

    return 1;
}

static Instance* initInstance(int frameBufferResolutionx, int frameBufferResolutiony){
    Instance* ret = malloc(sizeof(Instance));

    //init the window linked list
    ret->windows = malloc(sizeof(Window));
    ret->windows->next = NULL;
    ret->windows->prev = NULL;
    ret->windows->window = NULL;

    ret->objects = NULL;

    ret->camera = CameraCreate(1.0f, (frameBufferResolutionx/2.0f)/(frameBufferResolutiony), .90f, 80.0f);

    ret->mainFrame = FrameBufferCreate(frameBufferResolutionx, frameBufferResolutiony);
    ret->swapFrame = FrameBufferCreate(frameBufferResolutionx, frameBufferResolutiony);

    ret->colors = (Color*)malloc(sizeof(Color) * 8);
    int colorSupport = ColorsInit(0, NCURSES_BACKGROUND_COLOR, ret->colors, NUM_COLORS, "ColorList.dat");

    ret->menus = NULL;
    ret->paused = 0;

    if(!colorSupport){
        //tell them their terminal doesnt support colors
        //TODO
    }

    return ret;
}

void NcursesClearGameObjects(Instance* instance){
    GOList* objects = instance->objects;

    while(objects){
        GOFree(objects->object);
        GOList* next = objects->next;

        //free(objects);

        objects = next;
    }

    objects = NULL;
    instance->objects = NULL;
}

static void cleanUpInstance(Instance* instance){
    //clear the window list
    //and deallocate the memory created
    Window* current = instance->windows;

    while(current->next){
        Window* next = current->next;
        delwin(current->window);

        free(current);
        current = next;
    }

    //free all gameobjects
    GOList* objects = instance->objects;
    while(objects){
        GOFree(objects->object);
        GOList* next = objects->next;

        free(objects);

        objects = next;
    }

    FrameBufferFree(instance->mainFrame);
    FrameBufferFree(instance->swapFrame);

    free(instance->colors);
}

static void printWindow(WINDOW* wnd,int locy, int locx, Window* window){
    char* tag = window->tag;
    mvwprintw(wnd, locy, locx, "tag: %s", tag);
}

void NcursesInit(Instance** instance, int fbx, int fby){
    initscr();
    curs_set(0);

    start_color();

    noecho();
    cbreak();

    *instance = initInstance(TERMINAL_COLS, TERMINAL_LINES);

    TextureInit();
}

void NcursesDeInit(Instance* instance){
    cleanUpInstance(instance);
    free(instance);
    TexturesFree();

    endwin();
}

WINDOW* NcursesCreateWindow(const char* tag, int height, int width, int starty, int startx, Instance* instance){
    WINDOW* win = newwin(height, width, starty, startx);
    addWindow(win, tag, instance);
    return win;
}

void NcursesPrint(Window* window, int locy, int locx, const char* string){
    mvwprintw(window->window, locy, locx, string);
}

void PrintInstance(WINDOW* window, int startLocy, int startLocx, Instance* instance){
    int cursory = startLocy;
    mvwprintw(window, cursory, startLocx, "Windows:");
    cursory++;

    Window* current = instance->windows;

    while(current){
        printWindow(window, cursory, startLocx, current);
        cursory++;
        current = current->next;
    }
}

Window* GetWindowByTag(Instance* instance, const char* tag){
    if(!instance){
        return NULL;
    }

    Window* current = instance->windows;

    while(current){
        if(!strcmp(tag, current->tag)){
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void RefreshAllWindows(Instance* instance){
    refresh();

    if(!instance){
        return;
    }

    Window* current = instance->windows;

    while(current){
        wrefresh(current->window);
        current = current->next;
    } 
}

static void addGOToInstance(GameObject* object, Instance* instance){ 
    if(instance->objects == NULL){ 
        instance->objects = malloc(sizeof(GOList)); 
        instance->objects->object = object; 
        instance->objects->next = NULL; 

        return;
    } 

    //find the last object 
    GOList* lastObject = instance->objects; 

    while(lastObject->next){ 
        lastObject = lastObject->next; 
    } 

    GOList* next = malloc(sizeof(GOList)); 
    next->object = object; 
    next->next = NULL; 

    lastObject->next = next; 
}

GameObject* NcursesCreateGameObject(Model* model, const char* tag, Window* window, Instance* instance){
    GameObject* object = GOCreate(model, tag, window);
    addGOToInstance(object, instance);

    return object;
}

void NcursesSetColorPair(uint16_t colorpair){
    attron(COLOR_PAIR(colorpair));
}


