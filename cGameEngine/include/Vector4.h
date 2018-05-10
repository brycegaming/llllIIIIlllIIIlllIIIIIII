#ifndef INCLUDE_VECTOR4
#define INCLUDE_VECTOR4

#include "defs.h"
#include "Vector3.h"

/**
 * defines a 4 dimentional vector
 * */
typedef struct Vector4{
    float x;
    float y;
    float z;
    float w;
}Vector4;

/**
 * creates a new Vector4 
 * */
Vector4 Vec4Create(float x, float y, float z, float w);

/**
 * creates a vector4 from a vector3
 * */
Vector4 Vec4CreateFromVec3(Vector3 vector);

#endif
