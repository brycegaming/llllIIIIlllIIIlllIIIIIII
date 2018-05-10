#ifndef INCLUDE_MATRIX44
#define INCLUDE_MATRIX44

#include "defs.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"
//#include "Matrix22.h"

/**
 * defines a transformation matri
 * */
typedef struct transformMatrix{
    //data of the  matrix
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
}Matrix44;

/**
 * creates a new 4x4 matrix and sets it to identity
 * */
Matrix44 Matrix44Create();

/**
 * sets the passed matrix to identity
 * */
void Matrix44SetIdentity(Matrix44* matrix);

/**
 * sets all values in the matrix to zero
 * */
void Matrix44SetZero(Matrix44* matrix);

/**
 * loads one matrix into the other
 * */
void Matrix44Load(Matrix44* src, Matrix44* dest);

/**
 * adds two matrices together
 * */
void Matrix44Add(Matrix44* left, Matrix44* right, Matrix44* dest);

/**
 * subtracts the two matrices
 * */
void Matrix44Sub(Matrix44* left, Matrix44* right, Matrix44* dest);

/**
 * multiplies the matrices
 * */
void Matrix44MultMatrix44(Matrix44* left, Matrix44* right, Matrix44* dest);

/**
 * transforms a vector by the matrix
 * */
void Matrix44Transform(Matrix44* left, Vector4* right, Vector4* dest);

/**
 * scales the matrix
 * */
void Matrix44Scale(Vector3* vec, Matrix44* src, Matrix44* dest);

/**
 * rotates the matrix around an axis
 * */
void Matrix44Rotate(float angle, Vector3* axis, Matrix44* src, Matrix44* dest);

/**
 * translates the matrix
 * */
void Matrix44Translate(Vector3* vec, Matrix44* src, Matrix44* dest);

/**
 * translates the matrix by a vector2
 * */
void Matrix44TranslateVec2(Vector2* vec, Matrix44* src, Matrix44* dest);

/**
 * negates the matrix
 * */
void Matrix44Negate(Matrix44* matrix);

#endif
