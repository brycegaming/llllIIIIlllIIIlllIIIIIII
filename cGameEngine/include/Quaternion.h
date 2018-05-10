#ifndef INCLUDE_QUATERNION
#define INCLUDE_QUATERNION

#include "defs.h"
#include "Matrix44.h"
#include "Vector3.h"
#include "Vector4.h"

/**
 * represents a 3D rotation that can be converted easily to a matrix
 * */
typedef struct Quat{
    float x;
    float y;
    float z;
    float w;
}Quat;

/**
 * creates a new quaternion on stack
 * */
Quat QuatCreate(float x, float y, float z, float w);

/**
 * generate Quaternion from vector3
 * */
Quat QuatCreateFromEuler(Vector3* vec3);

/**
 * sets a Quaternion from x and y
 * */
void QuatSetxy(Quat* quat, float x, float y);

/**
 * sets a Quaternion from x and y
 * */
void QuatSetxyz(Quat* quat, float x, float y, float z);

/**
 * sets a Quaternion from x and y
 * */
void QuatSetxyzw(Quat* quat, float x, float y, float z, float w);

/**
 * converts a quaterniono to a rotation matrix
 * */
void QuatToMatrix44(Quat* src, Matrix44* dest);

/**
 * rotations the quaternion on the x Axis
 * */
void QuatRotateX(Quat* src, float angle);

/**
 * rotates a quaternion on the y axis
 * */
void QuatRotateY(Quat* src, float angle);

/**
 * rotates a quaternion on the z axis
 * */
void QuatRotateZ(Quat* src, float angle);

/**
 * sets the quaternion to identity
 * */
void QuatSetIdentity(Quat* quat);

/**
 * returns the length of the quat
 * */
float QuatLength(Quat* quat);

/**
 * returns the length of the quaternion squared
 * */
float QuatLengthSquared(Quat* quat);

/**
 * normalizes the quaternion
 * */
void QuatNormalize(Quat* src, Quat* dest);

/**
 * returns the angle between quats
 **/
float QuatDot(Quat* left, Quat* right);

/**
 * negates the quat
 * */
void QuatNegate(Quat* quat);

/**
 * scales the quaternion by a given float
 * */
void QuatScale(float scale, Quat* src, Quat* dest);

/**
 * multiplies two quaternions together
 * */
void QuatMult(Quat* left, Quat* right, Quat* dest);

/**
 * multiplies the left quaternion by the inverse of the 
 * quaternion on the right
 * the expression appears as so dest = (left*(1/right))
 * */
void QuatMultInverse(Quat* left, Quat* right, Quat* dest);

/**
 * rotates the quaternion on an axis
 * xyz are the axis and w is the angle
 * */
void QuatSetFromAxisAngle(Quat* quat, Vector4* vec4);

/**
 * rotates a matrix by the quaternion
 **/
void QuatRotateMatrix(Quat* src, Matrix44* dest);

#endif
