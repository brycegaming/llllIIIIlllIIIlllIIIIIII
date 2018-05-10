#include "include/FrameBuffer.h"
#include "string.h"

FrameBuffer* FrameBufferCreate(int frameWidth, int frameHeight){
    FrameBuffer* ret = (FrameBuffer*)malloc(sizeof(FrameBuffer));

    ret->frameWidth = frameWidth - 1;
    ret->frameHeight = frameHeight - 1;

    ret->depth = malloc(sizeof(depthBuffer_t) * frameWidth * frameHeight);
    ret->frame = malloc(sizeof(frameBuffer_t) * frameWidth * frameHeight);

    return ret;
}

void FrameBufferFree(FrameBuffer* frameBuffer){
    free(frameBuffer->depth);
    free(frameBuffer->frame);

    //just for good measure
    frameBuffer->frameWidth = 0;
    frameBuffer->frameHeight = 0;

    free(frameBuffer);
}

void FrameBufferReallocate(FrameBuffer* frameBuffer, int frameWidth, int frameHeight){
    free(frameBuffer->depth);
    free(frameBuffer->frame);

    frameBuffer->depth = malloc(sizeof(depthBuffer_t) * frameWidth * frameHeight);
    frameBuffer->frame = malloc(sizeof(frameBuffer_t) * frameWidth * frameHeight);
}

void FrameBufferClear(FrameBuffer* buffer, int buffersToClear, int colorClear){
    //if they want to clear the color buffer..
    if(buffersToClear & BR_COLOR_BUFFER_BIT){
        memset(buffer->frame, colorClear, sizeof(frameBuffer_t) * buffer->frameWidth * buffer->frameHeight);
    }

    //if they want to clear the depth buffer...
    if(buffersToClear & BR_DEPTH_BUFFER_BIT){
        memset(buffer->depth, DEPTH_BUFFER_MAX, sizeof(depthBuffer_t) * buffer->frameWidth * buffer->frameHeight);
    }
}

void FrameBufferRender(FrameBuffer** buffers, int* bufferIndex, int x, int y, int sizex, int sizey){
    for(int j = 0; j < sizey; j++){
        for(int i = 0; i < sizex; i++){
            float percx = (i) / ((float)sizex);
            float percy = (j + 1) / ((float)sizey);
            int samplex = (int)(buffers[*bufferIndex]->frameWidth * percx);
            int sampley = (int)(buffers[*bufferIndex]->frameHeight * percy);

            int value = buffers[*bufferIndex]->frame[((buffers[*bufferIndex]->frameWidth) * j) + i];

            char output = (char)value;
            char color = (value >> 8);

            if(value == 0){
                //attron(COLOR_PAIR(BACKGROUND_COLOR));
                //mvprintw(y + j, x + i, "%c", ' ');
                continue;
            }

            attron(COLOR_PAIR(color));

            mvprintw(y + j, x + i, "%c", output);
        }
    }
}
