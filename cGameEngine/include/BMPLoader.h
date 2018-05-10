#ifndef INCLUDE_BMPLOADER
#define INCLUDE_BMPLOADER

#include "defs.h"
#include "Color.h"

/**
 * holds data bout the pixel in the bmp file
 * */
typedef struct BMPPixel{
    unsigned char r;
    unsigned char g;
    unsigned char b;

    color_t color;
}BMPPixel;

/**
 * holds information loaded by the loader
 * */
typedef struct BMPData{
    unsigned int width;
    unsigned int height;

    BMPPixel* pixels;
}BMPData;

/**
 * loads the BMP file
 * */
BMPData* BMPLoad(const char* file, Color* allColors, int size);

/**
 * frees the image data
 * */
void BMPFree(BMPData* data);

/**
 * determines if the passed file is a BMP
 * */
int IsBMP(const char* file);

/**
 * returns the pixel at a certain x and y coord
 * starting with bottom left corner
 * */
BMPPixel* BMPGetPixel(BMPData* data, int x, int y);

/**
 * gets the pixel according to a floating point percentage on the picture
 * */
BMPPixel* BMPSamplePixel(BMPData* data, float x, float y);

/**
 * prints the bmp to the specified bounds
 * */
void BMPDraw(BMPData* data, unsigned int x, unsigned int y, unsigned int sizex, unsigned int sizey, int backgroundTransparency);

#endif
