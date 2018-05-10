#ifndef INCLUDE_TEXTURE
#define INCLUDE_TEXTURE

#include "defs.h"
#include "BMPLoader.h"
#include "Ncurses.h"

/**
 * allows the program to use the feature of textures
 * */
void TextureInit();

/**
 * loads a texture from a file
 * */
void TextureLoad(unsigned int index, const char* path);

/**
 * loads a texture from a bmp
 * */
void TextureLoadFromBMP(unsigned int index, BMPData* data);

/**
 * binds the texture for future use
 * */
void TextureBind(int index);

/**
 * frees all textures '
 * */
void TexturesFree();

/**
 * returns the color at a floating point selected position in the texture
 * */
color_t TextureSample(double texCoordx, double texCoordy);

#endif





