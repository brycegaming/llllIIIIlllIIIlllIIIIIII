#include "include/BMPLoader.h"
#include <stdio.h>
#include "include/defs.h"

/**
 * moves the file forward by a set number of bytes
 * */
static void fileMoveForward(FILE* file, int numBytes);

/**
 * returns the number of bytes in the file
 * */
static unsigned int getBitMapLength(FILE* file);

/**
 * returns the next int loaded in the file
 * */
static unsigned int next4Bytes(FILE* file);

static unsigned int next4Bytes(FILE* file){
    unsigned int value;
    fread(&value, 4, 1, file);
    return value;
}

static unsigned short next2Bytes(FILE* file){
    unsigned int value;
    fread(&value, 2, 1, file);
    return value;
}

static void fileMoveForward(FILE* file, int numBytes){
   for(int i = 0; i < numBytes; i++){
       nextByte(file);
   } 
}

static unsigned int getBitMapLength(FILE* file){
    unsigned int ret = next4Bytes(file);
    return ret;
}

BMPData* BMPLoad(const char* file, Color* allColors, int size){
    BMPData* ret = malloc(sizeof(BMPData));

    //make sure the file is the correct format
    if(!IsBMP(file)){
        free(ret);
        return NULL;
    }

    //create file reading binary
    FILE* f = fopen(file, "rb");
    fileMoveForward(f, 2);
    
    unsigned int fileLength = getBitMapLength(f);

    //next 4 bytes are reserved for other data
    fileMoveForward(f, 4);
    unsigned int pixelDataOffset = next4Bytes(f);

    //find the length of the actual data so I can actually load it
    unsigned int bmpLength = fileLength - pixelDataOffset;

    //no need to store the header data size
    fileMoveForward(f, 4);

    //load the width and height
    unsigned int bmpWidth = next4Bytes(f);
    unsigned int bmpHeight = next4Bytes(f);

    //load the number of color planes, I dont know what the hell this is
    //unsigned short numColorPlanes = next2Bytes(f);
    next2Bytes(f);

    //load bits per pixel
    unsigned short bitsPerPixel = next2Bytes(f);

    //get the compression mode, I sure hope there isnt any
    unsigned int compressionMode = next4Bytes(f);
    if(compressionMode != 0){
        fclose(f);
        free(ret);
        return NULL;
    }

    //I don't need anymore data
    //go back to beginning and go forward by the offset
    fseek(f, 0, SEEK_SET); 
    fileMoveForward(f, pixelDataOffset);

    //read all pixel data
    BMPPixel* pixels = malloc(sizeof(BMPPixel) * bmpLength / 3);

    //only supported modes
    if(bitsPerPixel == 24){
        for(int i = 0; i < bmpLength; i += 3){
            BMPPixel pix;

            pix.b = nextByte(f);
            pix.g = nextByte(f);
            pix.r = nextByte(f);

            Color close = ColorGetClosest(allColors, size, pix.r, pix.g, pix.b);
            pix.color = close.index;
            
            pixels[i / 3] = pix;
        }
    }
    else if(bitsPerPixel == 32){
        for(int i = 0; i < bmpLength; i += 4){
            BMPPixel pix;

            pix.b = nextByte(f);
            pix.g = nextByte(f);
            pix.r = nextByte(f);

            nextByte(f);

            Color close = ColorGetClosest(allColors, size, pix.r, pix.g, pix.b);
            pix.color = close.index;

            pixels[i] = pix;
        }
    }
    else{
        fclose(f);
        free(ret);
        return NULL;
    }

    ret->pixels = pixels;
    ret->width = bmpWidth;
    ret->height = bmpHeight;

    fclose(f);
    return ret;
}

void BMPFree(BMPData* data){
    free(data->pixels);
    free(data);
}

int IsBMP(const char* file){
    //if it is a bmp, the first two bytes should be BM
    FILE* f = fopen(file, "rb");

    char b1 = nextByte(f);
    char b2 = nextByte(f);

    fclose(f);

    //those two characters are B followed by M, if they are in that order, the computer thinks the file is a bmp
    return (b1 == 0x42 && b2 == 0x4D);
}

BMPPixel* BMPGetPixel(BMPData* data, int x, int y){
    x %= data->width;
    y %= data->height;
    return &data->pixels[(y * data->width) + x];
}

BMPPixel* BMPSamplePixel(BMPData* data, float x, float y){
    return BMPGetPixel(data, (((float)data->width - 1) * x), (((float)data->height - 1) * y));
}

void BMPDraw(BMPData* data, unsigned int x, unsigned int y, unsigned int sizex, unsigned int sizey, int backgroundTransparency){
    for(int j = y; j < y + sizey; j++){
        for(int i = x; i < sizex; i++){
            char output = '0';
            BMPPixel* pixel = BMPSamplePixel(data, (float)i / sizex, (float)j / sizey);

            if(pixel->color == BACKGROUND_COLOR && backgroundTransparency){
                continue;
            }

            attron(COLOR_PAIR(pixel->color));
            
            mvprintw(sizey - j, i, "%c", output);
        }
    }
}





