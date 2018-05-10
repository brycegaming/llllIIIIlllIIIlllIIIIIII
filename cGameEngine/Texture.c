#include "include/Texture.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

/**
 * array of the textures in the program
 * */
static BMPData** textures;
static int loadedTextureCount;
static int currentBoundTexture;

void TextureInit(){
    textures = (BMPData**) malloc(sizeof(void*) * MAX_TEXTURES);
    loadedTextureCount = 0;
    currentBoundTexture = -1;

    //set all textures to null initially
    for(int i = 0; i < MAX_TEXTURES; i++){
        textures[i] = NULL;
    }
}

void TextureLoad(unsigned int index, const char* path){
}

void TextureLoadFromBMP(unsigned int index, BMPData* data){
    loadedTextureCount ++;
    textures[index] = data;
}

void TextureBind(int index){
    currentBoundTexture = index;
}

void TexturesFree(){
    for(int i = 0; i < loadedTextureCount; i++){
        BMPFree(textures[i]);
    }

    free(textures);
}

color_t TextureSample(double texCoordx, double texCoordy){
    //return white if a texture has not been bound
    if(currentBoundTexture == -1 || textures[currentBoundTexture] == NULL){
       return 1;
    }

    return BMPSamplePixel(textures[currentBoundTexture], texCoordx, texCoordy)->color;
}

