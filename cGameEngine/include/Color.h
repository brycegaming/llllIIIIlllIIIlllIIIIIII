#ifndef INCLUDE_COLORS_H
#define INCLUDE_COLORS_H

#include "defs.h"

/**
 * defines a supported color
 * */
typedef struct Color{
    int r;
    int g;
    int b;
    int index;
}Color;

/**
 * inits all colors that can be used in this
 * instance of the program
 * returns 0 if more than 8 colors are not supported
 * */
int ColorsInit(int startPair, int background, Color* colors, int size, const char* colorFile);

/**
 * get closest defined color
 * */
Color ColorGetClosest(Color* colors, int size, int r, int g, int b);



#endif
