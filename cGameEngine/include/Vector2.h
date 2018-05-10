#ifndef INCLUDE_VECTOR2
#define INCLUDE_VECTOR2

#include "defs.h"
#include <math.h>

/**
 * stores information about locations, positions, rotations, scales, etc
 * you will cast them to an int when working with positons because there is
 * no need to store the floating point precision when working with the positions on the console
 * */
typedef struct vec {
    float x;
    float y;
}Vector2;

/**
 * finds the magnitude of the vector
 * */
 float Vec2Magnitude( Vector2* vector2); 

/**
 * creates and returns a vector2 created on stack by value
 * */
 Vector2 Vec2Create(float x, float y);

/**
 * creates and returns a vector2 created on heap memory
 * */
 Vector2* Vec2Allocate(float x, float y);

/**
 * frees the allocated memory of a vector2
 * */
 void Vec2Free(Vector2* mem);

/**
 * subtracts two vectors and returns the result by value
 * */
 Vector2 Vec2Sub( Vector2* Lop,  Vector2* Rop);

/**
 * adds two vectors and returns the result by value
 * */
 Vector2 Vec2Add( Vector2* Lop,  Vector2* Rop);

/**
 * multiples two vectors and returns the result by value
 * */
 Vector2 Vec2Mul( Vector2* Lop,  Vector2* Rop);

/**
 * divides two vectors and returns the result by value
 * */
 Vector2 Vec2Div( Vector2* Lop,  Vector2* Rop);

/**
 * scales a vector by a single floating point value
 * and returns the result by value
 * */
 Vector2 Vec2Scale( Vector2* Lop, float scale);

/**
 * finds the distance between two vectors
 * */
 float Vec2Distance( Vector2* one,  Vector2* two);

/**
 * returns the dot product of the two vectors
 * */
 float Vec2Dot( Vector2* one,  Vector2* two);

/**
 * normalizes the vector
 * */
 void Vec2Normalize(Vector2* vec);

/**
 * returns the normalized version of the vector
 * */
 Vector2 Vec2GetNormalized( Vector2* vec);

/**
 * copys the vector and returns it
 * */
 Vector2 Vec2Copy( Vector2* vector);

#endif 




