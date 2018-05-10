#ifndef INCLUDE_GAME
#define INCLUDE_GAME

#include "Ncurses.h"

/**
 * holds informaiton about the model that each 
 * color on the map corresponds to
 * */
typedef struct MapBlock{
    float r;
    float g; 
    float b;

    float height;

    float scalex;
    float scaley;
    float scalez;

    float roty;

    Model* model;
    int onGround;
    int texture;
    int cull;
}MapBlock;

/**
 * starts ncurses and runs what would normally go in main
 * */
void start(int* running, Instance** instance);

/**
 * the main input function for the game
 * */
char GameUpdate(float delta, int* running);

MapBlock MapBlockCreate(Model* model, float r, float g, float b, float height, float scalex, float scaley, float scalez, float roty, int onGround, int texture, int cull);

#endif 
