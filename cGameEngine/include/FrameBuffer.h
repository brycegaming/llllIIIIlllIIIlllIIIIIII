#ifndef INCLUDE_FRAME_BUFFER
#define INCLUDE_FRAME_BUFFER

#include "defs.h"

/**
 * holds information reguarding a current frame
 * */
typedef struct FrameBuffer{
    frameBuffer_t* frame;
    depthBuffer_t* depth;

    int frameWidth;
    int frameHeight;
}FrameBuffer;

/**
 * creates a new frameBuffer
 * */
FrameBuffer* FrameBufferCreate(int frameWidth, int frameHeight);

/**
 * frees the data in a frame buffer
 * */
void FrameBufferFree(FrameBuffer* frameBuffer);

/**
 * reallocates the frame buffer
 * */
void FrameBufferReallocate(FrameBuffer* frame, int frameWidth, int frameHeight);

/**
 * renders the frame buffer onto the screen at a specific point and size
 * */
void FrameBufferRender(FrameBuffer** buffers, int* bufferIndex, int x, int y, int sizex, int sizey);

/**
 * clears specified buffers in a frame buffer
 * */
void FrameBufferClear(FrameBuffer* buffer, int buffers, int clearColor);

#endif
