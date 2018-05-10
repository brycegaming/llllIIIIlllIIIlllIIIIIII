#ifndef INCLUDE_MATRIX22
#define INCLUDE_MATRIX22

#include "Vector2.h"

#define UP {0, 1}
#define RIGHT {1, 0}

//can mult matrix:
//vec2: -> vec2
//matrix(same size) -> matrix(same size)
//dot product -> vec2
//normalize
//determinate
//invert
//rotote
//translate

/**
 * stores information representing a 2D matrix
 * [][]
 * [][]
 * */
typedef struct matrix{
    float lh;
    float rh;
    float ll;
    float rl;
}Matrix22;

/**
 * creates an identity matrix
 * */
Matrix22 Matrix22Create();

/**
 * multiplies the matrix by a scalar and returns
 * a new one
 * */
Matrix22 Matrix22MultScalar(Matrix22* matrix, float scalar);

/**
 * multiplies the matrix by another matrix
 * */
Matrix22 Matrix22MultMatrix22(Matrix22* matrix, Matrix22* matrix2);

/**
 * sets the matrix to identity
 * */
void Matrix22SetIdentity(Matrix22* matrix);

/**
 * loads one matrix into the next
 * */
Matrix22 Matrix22Load(Matrix22* src, Matrix22* dest);

/**
 * adds one matrix to the next
 * */
Matrix22 Matrix22Add (Matrix22* lop, Matrix22* rop);

/**
 * subtracts one matrix from another
 * */
Matrix22 Matrix22Sub (Matrix22* lop, Matrix22* rop);

/**
 * transforms the Matrix by a vector
 * and puts the result in a new vector
 * */
Vector2 Matrix22Transform(Matrix22* matrix, Vector2* op);

/**
 * returns the transpose of the matrix (makes the rows the collums and the collums the rows)
 * */
Matrix22 Matrix22Transpose(Matrix22* matrix);

/**
 * returns the inverse of the passeed matrix
 * */
int Matrix22Invert(Matrix22* matrix, Matrix22* dest);

/**
 * returns the determinant of the matrix
 * */
float Matrix22Deter(Matrix22* matrix);

/**
 * negates the matrix
 * */
void negate(Matrix22* matrix);

#endif
