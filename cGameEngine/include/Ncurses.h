#ifndef INCLUDE_NCURSES
#define INCLUDE_NCURSES

#include "defs.h"
#include <string.h>
#include "GameObject.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Matrix44.h"
#include "Camera.h"
#include "FrameBuffer.h"
#include "Color.h"
#include "BMPLoader.h"
#include "Panel.h"
//#include "Texture.h"

/**
 * defines a triangle in the render process
 * */
typedef struct TriangleList_S{
    int ind1;
    int ind2;
    int ind3;
    Vertex* vertices;
    GameObject* object;

    struct TriangleList_S* next;
}TriangleList;

/**
 * defines all information about a vertex
 * */
typedef struct TriVert{
    Vertex* v1;
    Vertex* v2;
    Vertex* v3;

    Vector2* texCoord1;
    Vector2* texCoord2;
    Vector2* texCoord3;

    Vector3* n1;
    Vector3* n2;
    Vector3* n3;

    Matrix44* transformMatrix;
    Matrix44* finalMatrix;
}TriVert;

/**
 * doubly linked list for each of the windows currently in existence
 * */
typedef struct Window{
    char tag[30];
    WINDOW* window;

    //refreneces for linked list
    struct Window* next;
    struct Window* prev;
}Window;

/**
 * a list of game objects
 * */
typedef struct GOList{
    GameObject* object;
    struct GOList* next;
}GOList;

/**
 * holds information about the state of the engine reguarding ncurses
 * */
typedef struct data{
    Window* windows;
    GOList* objects;
    TriangleList* renderQueue;
    Camera camera;
    Color* colors;

    FrameBuffer* mainFrame;
    FrameBuffer* swapFrame;

    Vector3 lightPos;

    //linked list of the menus in the game
    Panel* menus;
    int paused;
}Instance;

/**
 * adds a new menu to the screen
 * */
void InstanceAddPanel(Instance* instance, Panel* panel);

/**
 * removes the currently focused panel
 * */
int InstanceRemovePanel(Instance* instance);

/**
 * creates a list of each triangle that needs to be rendered
 * onto the screen
 * */
TriangleList* RenderQueueCreate(Instance* instance);

/**
 * frees all memory in a renderQueue
 * */
void RenderQueueFree(TriangleList* list);

/**
 * the main game loop of the program, finds input, keeps the frames constant, updates time, renders objects
 * updates are being done on thread, so it wont have to worry about that at all, so long as the variables are mutex locked
 *
 * returns the users's input
 * */
char MainLoop(int* running, Instance* instance, char (*inputCallback)(float, int*));

/**
 * inits everything to do with ncurses
 * */
void NcursesInit(Instance** instance, int frameBufferResx, int frameBufferResy);

/**
deallocates memory used by ncurses and ends the process
* */
void NcursesDeInit(Instance* instance);

/**
 * clears all the game objects in the instance
 * */
void NcursesClearGameObjects(Instance* instance);

/**
 * creates a new ncurses window
 * */
WINDOW* NcursesCreateWindow(const char* tag, int height, int width, int starty, int startx, Instance* instance);

/**
 * prints to a window at a relative position
 * */
void NcursesPrint(Window* window, int locy, int locx, const char* string);

/**
 * prints all information about the current instance to any window
 * */
void PrintInstance(WINDOW* window, int startLocy, int startLocx, Instance* instance);

/**
 * returns the first window found that has the specified tag
 * */
Window* GetWindowByTag(Instance* instance, const char* tag);

/**
 * refreshes all windows
 * */
void RefreshAllWindows(Instance* instance);

/**
 * creates a gameobject and adds to the instance
 * */
GameObject* NcursesCreateGameObject(Model* model, const char* tag, Window* window, Instance* instance);

/**
 * renders a scene based on all the triangles passed too it
 * */
void RenderRenderQueue(TriangleList* list);

/**
 * sets the current color pair
 * */
void NcursesSetColorPair(uint16_t colorpair);

#endif
