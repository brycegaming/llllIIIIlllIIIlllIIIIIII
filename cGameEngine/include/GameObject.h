#ifndef INCLUDE_GAMEOBJECT
#define INCLUDE_GAMEOBJECT

#include "defs.h"
#include "Vector2.h"
#include "Vertex.h"

/*
 * information about position, scale and rotation
 * */
typedef struct GOTransform{
    Vector3 position;   //current linear position
    Vector3 scale;      //current scale
    Vector3 rotation;     //current rotation
}Transform;

/**
 * handles the updating of physics in gameobjects
 * the rotations are done in floats representing the angle
 * it is best to keep the angles mod 360
 * */
typedef struct GOPhysics{
    Vector3 velocity;           //the current linear movement speed and direction
    Vector3 acceleration;       //the linear acceleration
    Vector3 angularVelocity;      //the rotational velocity
    Vector3 angularAcceleration;  //the rotational acceleration
}Physics;

/**
 * handles gameobjects
 * */
typedef struct GO{
    char tag[20];                    //the tag of the object for searching
    Physics physics;                 //current information about the objects movement and rotations
    Transform transform;             //the location of the object on the window
    struct Window* window;           //the window which the object appears on
    Model* model;                    //the model the object is rendered with (the set of vertices to be razterized with the selected render process)
    uint8_t texture;
    int rendering;
    int cullBackFaces;
    //add the function* for the AI
}GameObject;

/**
 * creates a game object and inits all information besides the model and tag and window to nothing
 * if the window equals NULL, it sets it in the main window
 * */
GameObject* GOCreate(Model* model, const char* tag, struct Window* window);

/**
 * frees a gameobject
 * */
void GOFree(GameObject* object);

/**
 * changes physics variables based on GO information
 * */
void GOUpdatePhysics(GameObject* object, float delta);

#endif
