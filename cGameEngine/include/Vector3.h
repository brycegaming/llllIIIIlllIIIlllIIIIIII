#ifndef INCLUDE_VECTOR3
#define INCLUDE_VECTOR3

#include "defs.h"
#include <math.h>

typedef struct Vec3{
    float x;
    float y;
    float z;
}Vector3;

/**
 * creates a new vector3
 * */
Vector3 Vec3Create(float x, float y, float z);

/**
 * finds the magnitude of a 3D vector
 * */
float Vec3Magnitude(const Vector3* vec3);

/**
 * frees a dynamically allocated vec3
 * */
void Vec3Free(Vector3* vector);

/**
 * subtracts two vectors and returns the result by value
 * */
 Vector3 Vec3Sub(const Vector3* Lop, const Vector3* Rop);

/**
 * adds two vectors and returns the result by value
 * */
 Vector3 Vec3Add(const Vector3* Lop, const Vector3* Rop);

/**
 * multiples two vectors and returns the result by value
 * */
 Vector3 Vec3Mul(const Vector3* Lop, const Vector3* Rop);

/**
 * divides two vectors and returns the result by value
 * */
 Vector3 Vec3Div(const Vector3* Lop, const Vector3* Rop);

/**
 * finds the distance between two vectors
 * */
 float Vec3Distance(const Vector3* one, const Vector3* two);

 /**
  * returns the dot product of two vector3
  * */
 float Vec3Dot(const Vector3* one, const Vector3* two);
 
 /**
  * returns the normalized version of a vector
  * */
 Vector3 Vec3GetNormalized(const Vector3* vec);

 /**
  * finds the cross product of a vector3
  * */
 Vector3 Vec3Cross(const Vector3* one, const Vector3* two);

 /**
  * loads the seocnd vector into the first
  * */
 void Vec3Load(Vector3* l, const Vector3* r);

#endif
