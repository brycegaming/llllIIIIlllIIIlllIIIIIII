#include "include/GameObject.h"
#include "include/Ncurses.h"

GameObject* GOCreate(Model* model, const char* tag, struct Window* window){
    GameObject* ret = malloc(sizeof(GameObject));

    //set basis information
    ret->model = model;

    //if the window happens to be NULL, when the render process occurs, it will check for this and set it in the main window
    ret->window = window;   

    //set the tag
    strcpy(ret->tag, tag);

    ret->rendering = 1;

    //init all else to zero
    ret->transform.position.x = 0;
    ret->transform.position.y = 0;
    ret->transform.position.z = 0;

    ret->transform.scale.x = 1;
    ret->transform.scale.y = 1;
    ret->transform.scale.z = 1;
    
    ret->transform.rotation.x = 0;
    ret->transform.rotation.y = 0;
    ret->transform.rotation.z = 0;

    //set the velocities to 0
    ret->physics.velocity.x = 0;
    ret->physics.velocity.y = 0;
    ret->physics.velocity.z = 0;

    ret->physics.acceleration.x = 0;
    ret->physics.acceleration.y = 0;
    ret->physics.acceleration.z = 0;

    ret->physics.angularVelocity.x = 0;
    ret->physics.angularVelocity.y = 0;
    ret->physics.angularVelocity.z = 0;

    ret->physics.angularAcceleration.x = 0;
    ret->physics.angularAcceleration.y = 0;
    ret->physics.angularAcceleration.z = 0;

    ret->cullBackFaces = 1;

    //default the texture coord to 0
    ret->texture = 0;

    return ret;
}

void GOUpdatePhysics(GameObject* object, float delta){
    object->transform.position.x += object->physics.velocity.x * delta;
    object->transform.position.y += object->physics.velocity.y * delta;
    object->transform.position.z += object->physics.velocity.z * delta;

    object->physics.velocity.x += object->physics.acceleration.x * delta;
    object->physics.velocity.y += object->physics.acceleration.y * delta;
    object->physics.velocity.z += object->physics.acceleration.z * delta;

    object->transform.rotation.x += object->physics.angularVelocity.x * delta;
    object->transform.rotation.y += object->physics.angularVelocity.y * delta;
    object->transform.rotation.z += object->physics.angularVelocity.z * delta;

    object->physics.angularVelocity.x += object->physics.angularAcceleration.x * delta;
    object->physics.angularVelocity.y += object->physics.angularAcceleration.y * delta;
    object->physics.angularVelocity.z += object->physics.angularAcceleration.z * delta;
}

void GOFree(GameObject* object){
    //ModelFree(object->model);
    free(object);
}



