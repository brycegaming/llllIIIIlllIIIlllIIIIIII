#include "include/Color.h"
#include <stdio.h>
#include <string.h>

int ColorsInitBase8(int startPair, int background, Color* colors){
    Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.index = 1;

    init_pair(1, COLOR_WHITE, background);

    colors[0] = color;

    color.r = 255;
    color.g = 0;
    color.b = 0;
    color.index = 2;

    init_pair(2, COLOR_RED, background);

    colors[1] = color;

    color.r = 0;
    color.g = 255;
    color.b = 0;
    color.index = 3;

    init_pair(3, COLOR_GREEN, background);

    colors[2] = color;

    color.r = 0;
    color.g = 0;
    color.b = 255;
    color.index = 4;

    init_pair(4, COLOR_BLUE, background);

    colors[3] = color;

    color.r = 0;
    color.g = 255;
    color.b = 255;
    color.index = 5;

    init_pair(5, COLOR_CYAN, background);

    colors[4] = color;

    color.r = 255;
    color.g = 255;
    color.b = 0;
    color.index = 6;

    init_pair(6, COLOR_YELLOW, background);

    colors[5] = color;

    color.r = 255;
    color.g = 0;
    color.b = 255;
    color.index = 7;

    init_pair(7, COLOR_MAGENTA, background);

    colors[6] = color;

    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.index = 8;

    init_pair(8, COLOR_BLACK, background);

    colors[7] = color;
    
    return 1;
}

int ColorsInit(int startPair, int background, Color* colors, int size, const char* colorFile){
    return ColorsInitBase8(startPair, background, colors);

    Color* hColors = colors;

    FILE* col = fopen(colorFile, "r");

    char input;
    int bufferLen = 20;
    char buffer[bufferLen];
    buffer[bufferLen - 1] = 0;
    int bufferIndex = 0;
    
    int r = -1;
    int g = -1;
    int b = -1;
    int index = -1;

    while((input = fgetc(col)) != EOF){
        if(input == ',' || input == '\n' || input == '\r'){
            buffer[bufferIndex + 1] = 0;

            int value = atoi(buffer);

            bufferIndex = 0;

            for(int i = 0; i < bufferLen; i++){
                buffer[i] = 32;
            }

            //set it to the correct input value
            if(index == -1){
                index = value;
            }
            else if(r == -1){
                r = value;
            }
            else if(g == -1){
                g = value;
            }
            else if(b == -1){
                b = value;
            }
            else{
                //save the color and go
                Color c;
                c.r = r;
                c.g = g;
                c.b = b;
                c.index = index;

                r = -1;
                g = -1;
                b = -1;
                index = -1;

                //save the color
                *colors = c;

                colors ++;
                index = value;
            }

            continue;
        }

        buffer[bufferIndex] = input;
        bufferIndex ++;
    }

    fclose(col);

    //init the colors first
    for(int i = 0; i < size; i++){
        init_color(i, hColors[i].r, hColors[i].g, hColors[i].b);
    }

    //init the color pairs with background colors
    for(int i = 0; i < size; i++){
        init_pair(startPair + i, i, COLOR_BLACK);
    }
    
    return 0;
}

Color ColorGetClosest(Color* colors, int size, int r, int g, int b){
    Color ret;

    int minScoreIndex = -1;
    int minScore = 0x7FFFFFFF;

    for(int i = 0; i < size; i++){
        int score = 0;
        
        int rScore = (int)abs(colors[i].r - r);
        int gScore = (int)abs(colors[i].g - g);
        int bScore = (int)abs(colors[i].b - b);
        rScore *= rScore;
        gScore *= gScore;
        bScore *= bScore;

        score = rScore + gScore + bScore;

        if(score < minScore){
            minScore = score;
            minScoreIndex = i;
        }
    }

    ret = colors[minScoreIndex];

    return ret;
}




