#include "include/Ncurses.h"
#include "include/GameObject.h"
#include "include/defs.h"
#include "include/Matrix22.h"
#include "include/Quaternion.h"
#include "include/Time.h"
#include <math.h>
#include "include/Texture.h"
#include "include/Panel.h"

/**
 * renders a single fragment to the screen applying all shader functionality
 * to render directly to the screen, pass the frame buffer as NULL
 * */
static int renderFragment(FrameBuffer* frameBuffer, TriVert* data);

/**
 * renders a triangle onto the screen
 * */
static void renderTriangle(TriVert* allVertInfo, Camera* camera, FrameBuffer* buffer, int drawMode, GameObject* object);

/**
 * renders the entire scene
 * */
static void render(GOList* instance, FrameBuffer* buffer, Camera* cam);

/**
 * renders a game object
 * */
static void renderObject(GameObject* object, Camera* cam, FrameBuffer* instance, int mode);

/**
 * transforms a vertex from -1 to 1 to proper position on window
 * */
static Vertex transformVertex(Vertex vertex, int maxx, int maxy, Matrix44* transformationMatrix);

/**
 * finds the max vertex positions of the triagle
 * */
static void getMinMax(const Vertex* v1, const Vertex* v2, const Vertex* v3, Vector2* xMax, Vector2* yMax);

/**
 * renders a panel to the screen
 * */
static void renderPanel(FrameBuffer* instance, Panel* panel);

//for finding the fps when buffering the frame
int renderBufferFPS = 0;

int bufferIndex = 0;
FrameBuffer* buffers[2];
thread_t renderBuffers;

int rendering = 0;
int* run;

/**
 * used to double buffer the render process
 * basically, this thread renders stuff and when it is done, it switches to another buffer and does it again
 * while the other thread is presenting the rendered information, this thread is writing a new buffer
 * Why is this an optimization? It actually isnt when dealing with small amounts of objects and triangles, it starts to show how powerful it is when there are many many triangles
 * In the previous system, we were only drawing the pixels that were written that frame to the screen, that is great, as long as we don't want a background and other stuff
 * it is also very very slow when objects take up a large part of the screen.
 * With this solution, the efficiency is only capped by the time it takes to render a buffer, or by the time it takes to present a buffer
 * this leads to much more consistent fps although slower with low poly
 * you can think of this as only doing the slower of these two slow processes per frame instead of both of them per frame so it should lead to twice the fps and it will be noticable when there are many models in the game
 * */
void* BufferRender(void* i){
    Instance* instance = (Instance*)i;
    buffers[0] = instance->mainFrame;
    buffers[1] = instance->swapFrame;

    Timer bufferTimer = TimerCreate();

    Timer bufferFPSCounter = TimerCreate();

    float bufferDelta = 0;

    while(*run){
        //update the timer so I can find how long it took to render the buffer
        TimerUpdate(&bufferTimer);

        FrameBufferClear(buffers[bufferIndex ^ 1], BR_COLOR_BUFFER_BIT | BR_DEPTH_BUFFER_BIT, CLEAR_COLOR);

        //render the frame buffer
        CameraCalculateViewMatrix(&instance->camera);
        
        render(instance->objects, buffers[bufferIndex ^ 1], &instance->camera);

        TimerUpdate(&bufferFPSCounter);
        renderBufferFPS = bufferFPSCounter.currentFPS;

        //render the menus
        Panel* p = instance->menus;
        while(p){
            renderPanel(buffers[bufferIndex ^ 1], p);
            p = p->next;
        }

        //record the time it took to render the frame in seconds and convert it to milliseconds
        bufferDelta = TimerUpdate(&bufferTimer);

        bufferIndex ^= 1;

        //use the calculated difference in time to adjust frame delay
        sleep_ms(FRAME_TIME_MS - (bufferDelta * 1000));
    }

    return NULL;
}

//Vector3 lightPos = {0, 0, 10};

char MainLoop(int* running, Instance* instance, char (*inputCallback)(float, int*)){
    run = running;

    buffers[0] = instance->mainFrame;
    buffers[1] = instance->swapFrame;

    //int err = pthread_create(&renderBuffers, NULL, BufferRender, instance);
    ThreadCreate(&renderBuffers, BufferRender, (void*)instance);

    Timer mainFps = TimerCreate();
    Timer renderTimer = TimerCreate();
    float renderDelta = 0;
    float delta = 0;

    while(*running){
        //lightPos = instance->camera.position;
        TimerUpdate(&renderTimer);

        erase();

        int startx, starty, sizex, sizey;
        startx = 0;
        starty = 0;
        sizex = (TERMINAL_COLS + 1);
        sizey = (TERMINAL_LINES + 1);

        //render the scene
        FrameBufferRender(buffers, &bufferIndex, startx, starty, sizex, sizey);

        //output the current frames
        attron(COLOR_PAIR(WHITE));
        
        //output basic debug info
        mvprintw(0, 0, "FPS main: %d", mainFps.currentFPS);
        mvprintw(1, 0, "FPS thread: %d", renderBufferFPS);

        //collect user input for later use
        inputCallback(delta, running);

        //allow user to output text here
        refresh();

        //get the total time to render the frame
        renderDelta = TimerUpdate(&renderTimer);

        //update the physics of each and every object
        GOList* objects = instance->objects;

        while(objects){
            GOUpdatePhysics(objects->object, delta);
            objects = objects->next;
        }

        //update the menus
        Panel* p = instance->menus;
        while(p){
            //we have found the focused window
            if(!p->next){
                PanelUpdate(p);

                break;
            }

            p = p->next;
        }

        //lock framerate
        sleep_ms(FRAME_TIME_MS - (renderDelta * 1000));
        
        //find the delta value for next frame
        delta = TimerUpdate(&mainFps);

        //if its windows 32, I don't have a good way of getting the time yet, so I will just assume the FPS is around 60 and call it good
        //it wont work most of the time, but it is better than nothing
        if(instance->paused){
            delta = 0;
        }

        //sleep_ms(4);
        //if this thread is reading from the buffer the other is writing to, it is time to mutex lock it, otherwise, it is time to mutex unlock it
        //pthread_mutex_unlock(renderBuffers);
    }

    //pthread_detach(renderBuffers);

    //I cannot do this in the future, I need to make the render buffer immediately exit when the code gets to here
    sleep_ms(100);

    return 0x30;
}

static void renderPanel(FrameBuffer* buffer, Panel* panel){
    char* text = panel->text;
    char* options = panel->options;

    //clear all the stuff beneath the panel and draw the border
    //also draw the characters to the right location
    for(int i = panel->startx; i < panel->startx + panel->scalex; i++){
        for(int j = panel->starty; j < panel->starty + panel->scaley; j++){
            if(j > buffer->frameHeight){
                break;
            }

            char character = ' ';

            if(j == panel->starty + panel->scaley - 1 || j == panel->starty){
                character = '_';
            }
           
            if(i == panel->startx + panel->scalex - 1 || i == panel->startx){
                if(j != panel->starty && j != panel->starty + panel->scaley){
                    character = '|';
                }
            }

            buffer->frame[(j * buffer->frameWidth) + i] = (WHITE << 8) | character;
        }
    }
    
    //draw the prompt text to the buffer
    int cursx, cursy;
    cursx = panel->startx + panel->textOffsetX;
    cursy = panel->starty + panel->textOffsetY;

    while(*text){
        if(cursy > buffer->frameHeight){
            break;
        }

        if(*text == '~'){
            cursx = panel->startx + panel->textOffsetX;
            cursy ++; 
            text++;

            continue;
        }

        buffer->frame[(cursy * (int)buffer->frameWidth) + cursx] = (panel->textColor << 8) | *text;

        text ++; 
        cursx ++;
    }

    //draw the options to the menu now
    cursx = panel->startx + panel->textOffsetX;
    cursy += 2;
    int currop = 0;

    while(*options){
        if(cursy > buffer->frameHeight){
            break;
        }

        //if it is the next option, dont render the charcter and just move on
        if(*options == '~'){
            cursx = panel->startx + panel->textOffsetX;
            cursy ++; 
            options++;
            currop++;

            continue;
        }

        if(currop == panel->currentOption){
            buffer->frame[(cursy * (int)buffer->frameWidth) + cursx] = (panel->selectionColor << 8) | *options;
        }
        else{
            buffer->frame[(cursy * (int)buffer->frameWidth) + cursx] = (panel->optionColor << 8) | *options;
        }

        cursx ++;
        options ++; 
    }
}

/**
 * finds the barry centric coord of the passed triangle
 * */
static float sign (Vector2* p1, Vector2* p2, Vector2* p3){
    return (p1->x - p3->x) * (p2->y - p3->y) - (p2->x - p3->x) * (p1->y - p3->y);
}

int PointInTriangle (Vector2* pt, Vertex* vert1, Vertex* vert2, Vertex* vert3){
    int b1, b2, b3;

    Vector2 v1Pos = Vec2Create(vert1->position.x, vert1->position.y);
    Vector2 v2Pos = Vec2Create(vert2->position.x, vert2->position.y);
    Vector2 v3Pos = Vec2Create(vert3->position.x, vert3->position.y);

    b1 = sign(pt, &v1Pos, &v1Pos) < 0.0f;
    b2 = sign(pt, &v2Pos, &v2Pos) < 0.0f;
    b3 = sign(pt, &v3Pos, &v3Pos) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}

void render(GOList* objects, FrameBuffer* buffer, Camera* cam){
    while(objects){
        //render if the object should render
        if(objects->object->rendering)
            renderObject(objects->object, cam, buffer, RENDER_TRIANGLE_FILL);

        //GOUpdatePhysics(objects->object);
        objects = objects->next;
    }
}

static void renderTriangle(TriVert* allVertInfo, Camera* cam,
        FrameBuffer* buffer, int drawMode, GameObject* object){

    //get the position in model view space
    Vertex v1 = transformVertex(*allVertInfo->v1, buffer->frameWidth, buffer->frameHeight, allVertInfo->finalMatrix);
    Vertex v2 = transformVertex(*allVertInfo->v2, buffer->frameWidth, buffer->frameHeight, allVertInfo->finalMatrix);
    Vertex v3 = transformVertex(*allVertInfo->v3, buffer->frameWidth, buffer->frameHeight, allVertInfo->finalMatrix);

    //get the position in world space
    /**
    Vertex worldv1 = transformVertex(*allVertInfo->v1, buffer->frameWidth, buffer->frameHeight, allVertInfo->transformMatrix);
    Vertex worldv2 = transformVertex(*allVertInfo->v2, buffer->frameWidth, buffer->frameHeight, allVertInfo->transformMatrix);
    Vertex worldv3 = transformVertex(*allVertInfo->v3, buffer->frameWidth, buffer->frameHeight, allVertInfo->transformMatrix);
    */

    //projection space backface culling
    if(object->cullBackFaces){
        Vector3 bv0 = v1.position;
        Vector3 bv1 = v2.position;
        Vector3 bv2 = v3.position;

        Vector3 U = Vec3Sub(&bv1, &bv0);
        Vector3 V = Vec3Sub(&bv2, &bv0);
        Vector3 C = Vec3Cross(&U, &V);

        if(C.z >= 0){
            return;
        }
    }

    //projection space near culling
    if(v1.position.z < 0 || v2.position.z < 0 || v3.position.z < 0){
        return;
    }

    //far culling
    if(v1.position.z > cam->zFar || v2.position.z > cam->zFar || v3.position.z > cam->zFar){
        return;
    }

    Vector2* texCoord1 = allVertInfo->texCoord1;
    Vector2* texCoord2 = allVertInfo->texCoord2;
    Vector2* texCoord3 = allVertInfo->texCoord3;

    //world normal positions
    Vector4 n1 = Vec4CreateFromVec3(*allVertInfo->n1);
    Vector4 n2 = Vec4CreateFromVec3(*allVertInfo->n2);
    Vector4 n3 = Vec4CreateFromVec3(*allVertInfo->n3);

    //transform the normals
    Matrix44Transform(allVertInfo->transformMatrix, &n1, &n1);
    Matrix44Transform(allVertInfo->transformMatrix, &n2, &n2);
    Matrix44Transform(allVertInfo->transformMatrix, &n3, &n3);

    //world vertex positions
    Vector4 worldv1 = Vec4CreateFromVec3(allVertInfo->v1->position);
    worldv1.w = 1.0f;
    Vector4 worldv2 = Vec4CreateFromVec3(allVertInfo->v2->position);
    worldv2.w = 1.0f;
    Vector4 worldv3 = Vec4CreateFromVec3(allVertInfo->v3->position);
    worldv3.w = 1.0f;

    //transform the vertices
    Matrix44Transform(allVertInfo->transformMatrix, &worldv1, &worldv1);
    Matrix44Transform(allVertInfo->transformMatrix, &worldv2, &worldv2);
    Matrix44Transform(allVertInfo->transformMatrix, &worldv3, &worldv3);

    switch(drawMode){
        case RENDER_POINTS: //probably will never implement this 
        case RENDER_LINES: //probably will never implement this
        case RENDER_TRIANGLE_FILL:
        {
            Vector2 x, y;
            getMinMax(&v1, &v2, &v3, &x, &y);

            if(x.x < 0.0f){
                x.x = 0.0f;
            }
            else if(x.x > buffer->frameWidth){
                //return;
                x.x = buffer->frameWidth;
            }

            if(x.y > buffer->frameWidth){
                x.y = buffer->frameWidth;
            }
            else if(x.y < 0.0f){
                //return;
                x.y = 0.0f;
            }

            if(y.x < 0.0f){
                y.x = 0.0f;
            }
            else if(y.x > buffer->frameHeight){
                //return;
                y.x = buffer->frameHeight;
            }

            if(y.y > buffer->frameHeight){
                y.y = buffer->frameHeight;
            }
            else if(y.y < 0.0f){
                //return;
                y.y = 0.0f;
            }

            for(int j = y.x; j <= y.y; j++){
                int draw = 0;

                for(int i = x.x; i < x.y; i++){
                    float wv1 = ((v2.position.y - v3.position.y) * ((float)i - v3.position.x) +
                            (v3.position.x - v2.position.x) * ((float)j - v3.position.y)) /
                        ((v2.position.y - v3.position.y) * (v1.position.x - v3.position.x) +
                         (v3.position.x - v2.position.x) * (v1.position.y - v3.position.y));

                    float wv2 = ((v3.position.y - v1.position.y) * ((float)i - v3.position.x) +
                            (v1.position.x - v3.position.x) * ((float)j - v3.position.y)) /
                        ((v2.position.y - v3.position.y) * (v1.position.x - v3.position.x) +
                         (v3.position.x - v2.position.x) * (v1.position.y - v3.position.y));

                    float wv3 = 1.0f - wv1 - wv2;

                    int one = (wv1 < 0);
                    int two = (wv2 < 0);
                    int three = (wv3 < 0);

                    //is the point in the triangle
                    if((one == two) && (two == three)){
                        //if(PointInTriangle(&point, v1, v2, v3)){
                        //check depth information
                        //interpolate across the vertices to find the z position of the fragment
                        //yay time to use some more barycentric interpolation
                        float fragz = (v1.position.z * wv1) + (v2.position.z * wv2) + (v3.position.z * wv3);
                        fragz /= cam->zFar;

                        Vector2 fragTexCoord;
                        fragTexCoord.x = (double)(texCoord1->x * wv1) + (texCoord2->x * wv2) + (texCoord3->x * wv3);
                        fragTexCoord.y = (double)(texCoord1->y * wv1) + (texCoord2->y * wv2) + (texCoord3->y * wv3);

                        Vertex fragPos;
                        fragPos.position.x = i;
                        fragPos.position.y = j;
                        fragPos.position.z = fragz;

                        //calculate fragment normal from other vertex normals
                        Vector3 fragNormal;
                        fragNormal.x = (double)(n1.x * wv1) + (n2.x * wv2) + (n3.x * wv3);
                        fragNormal.y = (double)(n1.y * wv1) + (n2.y * wv2) + (n3.y * wv3);
                        fragNormal.z = (double)(n1.z * wv1) + (n2.z * wv2) + (n3.z * wv3);

                        //get the world position of the fragment
                        Vector3 worldFragPos;
                        worldFragPos.x = (double)(worldv1.x * wv1) + (worldv2.x * wv2) + (worldv3.x * wv3);
                        worldFragPos.y = (double)(worldv1.y * wv1) + (worldv2.y * wv2) + (worldv3.y * wv3);
                        worldFragPos.z = (double)(worldv1.z * wv1) + (worldv2.z * wv2) + (worldv3.z * wv3);

                        TriVert fragVert;
                        fragVert.v1 = &fragPos;
                        fragVert.n2 = &worldFragPos;
                        fragVert.n1 = &fragNormal;
                        fragVert.n3 = &cam->lightPos;

                        fragVert.texCoord1 = &fragTexCoord;
                        fragVert.transformMatrix = allVertInfo->transformMatrix;

                        if(renderFragment(buffer, &fragVert))
                            draw = 1;
                    }
                    else{
                        if(draw){
                            //break;
                        }
                    }
                }
            }
        }
    }
}

void renderObject(GameObject* object, Camera* camera, FrameBuffer* buffer, int mode){
    //transform verticies to screen coords from (0 to WINDOW_WIDTH)-> (-1 to 1) and (0 to WINDOW_HEIGHT) -> (-1 to 1)
    Matrix44 transformationMatrix = Matrix44Create();

    Vector3 vec;

    //apply the projection matrix
    //Matrix44MultMatrix44(&transformationMatrix, &camera->projection, &transformationMatrix);
    //Matrix44MultMatrix44(&transformationMatrix, &camera->view, &transformationMatrix);

    //translation
    vec.x = object->transform.position.x;
    vec.y = object->transform.position.y;
    vec.z = object->transform.position.z;
    Matrix44Translate(&vec, &transformationMatrix, &transformationMatrix);

    //scale
    Matrix44 scaleMatrix = Matrix44Create();
    vec.x = object->transform.scale.x;
    vec.y = object->transform.scale.y;
    vec.z = object->transform.scale.z;
    Matrix44Scale(&vec, &scaleMatrix, &scaleMatrix);

    Matrix44 rotationMatrix = Matrix44Create();
    vec.x = 1; vec.y = 0; vec.z = 0;
    Matrix44Rotate(object->transform.rotation.x, &vec, &rotationMatrix, &rotationMatrix);

    vec.x = 0; vec.y = 1; vec.z = 0;
    Matrix44Rotate(object->transform.rotation.y, &vec, &rotationMatrix, &rotationMatrix);

    vec.x = 0; vec.y = 0; vec.z = 1;
    Matrix44Rotate(object->transform.rotation.z, &vec, &rotationMatrix, &rotationMatrix);

    Matrix44MultMatrix44(&transformationMatrix, &scaleMatrix, &transformationMatrix);
    Matrix44MultMatrix44(&transformationMatrix, &rotationMatrix, &transformationMatrix);

    Matrix44 finalTrans;
    Matrix44MultMatrix44(&camera->view, &transformationMatrix, &finalTrans);
    Matrix44MultMatrix44(&camera->projection, &finalTrans, &finalTrans);

    //bind the texture for the object
    TextureBind(object->texture);

    //loop through each of the indices
    int indCount = object->model->indCount;
    int* ind = object->model->indices;

    for(int k = 0; k < indCount; k += 3){
        Vertex vert1, vert2, vert3;
        vert1 = object->model->verts[ind[k + 0]];
        vert2 = object->model->verts[ind[k + 1]];
        vert3 = object->model->verts[ind[k + 2]];

        TriVert allVertInfo;
        allVertInfo.v1 = &vert1;
        allVertInfo.v2 = &vert2;
        allVertInfo.v3 = &vert3;

        //set the texture coords
        Vector2 t1 = object->model->texCoords[object->model->texIndices[k + 0]];
        Vector2 t2 = object->model->texCoords[object->model->texIndices[k + 1]];
        Vector2 t3 = object->model->texCoords[object->model->texIndices[k + 2]];

        Vector3 n1 = object->model->normals[object->model->normalIndices[k + 0]];
        Vector3 n2 = object->model->normals[object->model->normalIndices[k + 1]];
        Vector3 n3 = object->model->normals[object->model->normalIndices[k + 2]];

        allVertInfo.texCoord1 = &t1;
        allVertInfo.texCoord2 = &t2;
        allVertInfo.texCoord3 = &t3;

        allVertInfo.n1 = &n1;
        allVertInfo.n2 = &n2;
        allVertInfo.n3 = &n3;

        allVertInfo.transformMatrix = &transformationMatrix;
        allVertInfo.finalMatrix = &finalTrans;

        renderTriangle(&allVertInfo, camera, buffer, mode, object);
    }
}

static Vertex transformVertex(Vertex vertex, int maxx, int maxy, Matrix44* transformationMatrix){
    Vertex ret;

    Vector4 final;
    Vector4 prev = Vec4Create(vertex.position.x, vertex.position.y, vertex.position.z, 1);

    Matrix44Transform(transformationMatrix, &prev, &final);

    //vertex.position = Matrix22Transform(&finalTransform, &vertex.position);
    vertex.position.x = final.x / final.z;
    vertex.position.y = final.y / final.z;

    float maxDivX = maxx / 2.0f;
    float maxDivY = maxy / 2.0f;
    vertex.position.y *= -1;

    float newx = (maxDivX * vertex.position.x) + maxDivX;
    float newy = (maxDivY * vertex.position.y) + maxDivY;

    ret.position.x = newx;
    ret.position.y = newy;
    ret.position.z = final.z;

    return ret;
}

//char shades[] = {'#', '*', '+', '-', '.', ' '};
char shades[] = {'#', '&', '%', '*', '+', '-', '\'', '.', ' '};
int numShades = 9;

static int renderFragment(FrameBuffer* frameBuffer, TriVert* data){
    float x, y, z;
    x = data->v1->position.x;
    y = data->v1->position.y;
    z = data->v1->position.z;

    //should it render at this depth?
    depthBuffer_t depth = (depthBuffer_t)((float)z * DEPTH_BUFFER_MAX);
    int index = ((int)frameBuffer->frameWidth * (int)y) + (int)x;

    if(depth > frameBuffer->depth[index]){
        return 0;
    }

    //texture calculations
    double texX, texY;
    texX = data->texCoord1->x;
    texY = data->texCoord1->y;

    //normal data for lighting
    Vector3 fragNormal;
    fragNormal.x = data->n1->x;
    fragNormal.y = data->n1->y;
    fragNormal.z = data->n1->z;

    //get the world position of the light
    Vector3 lightPos = *data->n3;

    //get the world position of the fragment
    Vector3 worldPos = *data->n2;

    //get the position relative to the light
    Vector3 toLight;
    toLight = Vec3Sub(&lightPos, &worldPos);

    //normalize the damn vectors
    fragNormal = Vec3GetNormalized(&fragNormal);
    toLight = Vec3GetNormalized(&toLight);

    //get the brightness based on the dot product
    float nDot1 = Vec3Dot(&fragNormal, &toLight); 
    float brightness = MAX(nDot1, 0.3);

    //brightness = 1;

    //get the color at the relative location on the texture (use the texture coords)
    color_t color = TextureSample((double)texX * 1, (double)texY * 1);

    char character = '0';

    //invert
    brightness = 1 - brightness;
    brightness *= numShades;
    
    //brightness = 1;

    character = shades[(int)brightness];

    //scale brighness from 0 to the number of brightness nodes
    frameBuffer->frame[(int)(frameBuffer->frameWidth * (int)(y) + (int)(x))] = (color << 8) | character;

    //set new depth
    frameBuffer->depth[index] = depth;
    return 1; 
}

static void getMinMax(const Vertex* v1, const Vertex* v2, const Vertex* v3, Vector2* xMax, Vector2* yMax){
    float minx, maxx, miny, maxy;

    minx = (float)MINOF3(v1->position.x, v2->position.x, v3->position.x);
    maxx = (float)MAXOF3(v1->position.x, v2->position.x, v3->position.x);
    miny = (float)MINOF3(v1->position.y, v2->position.y, v3->position.y);
    maxy = (float)MAXOF3(v1->position.y, v2->position.y, v3->position.y);

    xMax->x = minx;
    xMax->y = maxx;
    yMax->x = miny;
    yMax->y = maxy;
}

