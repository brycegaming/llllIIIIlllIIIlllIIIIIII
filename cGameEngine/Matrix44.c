#include "include/Matrix44.h"

/**
code written based off lwjgl matrix math
*/

Matrix44 Matrix44Create(){
    Matrix44 ret;

    Matrix44SetIdentity(&ret);

    return ret;
}

void Matrix44SetIdentity(Matrix44* matrix){
    matrix->m00 = 1.0f;
    matrix->m01 = 0.0f;
    matrix->m02 = 0.0f;
    matrix->m03 = 0.0f;
    matrix->m10 = 0.0f;
    matrix->m11 = 1.0f;
    matrix->m12 = 0.0f;
    matrix->m13 = 0.0f;
    matrix->m20 = 0.0f;
    matrix->m21 = 0.0f;
    matrix->m22 = 1.0f;
    matrix->m23 = 0.0f;
    matrix->m30 = 0.0f;
    matrix->m31 = 0.0f;
    matrix->m32 = 0.0f;
    matrix->m33 = 1.0f;
}

void Matrix44SetZero(Matrix44* matrix){
    matrix->m00 = 0.0f;
    matrix->m01 = 0.0f;
    matrix->m02 = 0.0f;
    matrix->m03 = 0.0f;
    matrix->m10 = 0.0f;
    matrix->m11 = 0.0f;
    matrix->m12 = 0.0f;
    matrix->m13 = 0.0f;
    matrix->m20 = 0.0f;
    matrix->m21 = 0.0f;
    matrix->m22 = 0.0f;
    matrix->m23 = 0.0f;
    matrix->m30 = 0.0f;
    matrix->m31 = 0.0f;
    matrix->m32 = 0.0f;
    matrix->m33 = 0.0f;
}

void Matrix44Load(Matrix44* src, Matrix44* dest){
    dest->m00 = src->m00;
    dest->m01 = src->m01;
    dest->m02 = src->m02;
    dest->m03 = src->m03;
    dest->m10 = src->m10;
    dest->m11 = src->m11;
    dest->m12 = src->m12;
    dest->m13 = src->m13;
    dest->m20 = src->m20;
    dest->m21 = src->m21;
    dest->m22 = src->m22;
    dest->m23 = src->m23;
    dest->m30 = src->m30;
    dest->m31 = src->m31;
    dest->m32 = src->m32;
    dest->m33 = src->m33;
}

void Matrix44Add(Matrix44* left, Matrix44* right, Matrix44* dest){
    dest->m00 = left->m00 + right->m00;
    dest->m01 = left->m01 + right->m01;
    dest->m02 = left->m02 + right->m02;
    dest->m03 = left->m03 + right->m03;
    dest->m10 = left->m10 + right->m10;
    dest->m11 = left->m11 + right->m11;
    dest->m12 = left->m12 + right->m12;
    dest->m13 = left->m13 + right->m13;
    dest->m20 = left->m20 + right->m20;
    dest->m21 = left->m21 + right->m21;
    dest->m22 = left->m22 + right->m22;
    dest->m23 = left->m23 + right->m23;
    dest->m30 = left->m30 + right->m30;
    dest->m31 = left->m31 + right->m31;
    dest->m32 = left->m32 + right->m32;
    dest->m33 = left->m33 + right->m33;    
}

void Matrix44Sub(Matrix44* left, Matrix44* right, Matrix44* dest){
    dest->m00 = left->m00 - right->m00;
    dest->m01 = left->m01 - right->m01;
    dest->m02 = left->m02 - right->m02;
    dest->m03 = left->m03 - right->m03;
    dest->m10 = left->m10 - right->m10;
    dest->m11 = left->m11 - right->m11;
    dest->m12 = left->m12 - right->m12;
    dest->m13 = left->m13 - right->m13;
    dest->m20 = left->m20 - right->m20;
    dest->m21 = left->m21 - right->m21;
    dest->m22 = left->m22 - right->m22;
    dest->m23 = left->m23 - right->m23;
    dest->m30 = left->m30 - right->m30;
    dest->m31 = left->m31 - right->m31;
    dest->m32 = left->m32 - right->m32;
    dest->m33 = left->m33 - right->m33;    
}

void Matrix44MultMatrix44(Matrix44* left, Matrix44* right, Matrix44* dest){
    float m00 = left->m00 * right->m00 + left->m10 * right->m01 + left->m20 * right->m02 + left->m30 * right->m03;
    float m01 = left->m01 * right->m00 + left->m11 * right->m01 + left->m21 * right->m02 + left->m31 * right->m03;
    float m02 = left->m02 * right->m00 + left->m12 * right->m01 + left->m22 * right->m02 + left->m32 * right->m03;
    float m03 = left->m03 * right->m00 + left->m13 * right->m01 + left->m23 * right->m02 + left->m33 * right->m03;
    float m10 = left->m00 * right->m10 + left->m10 * right->m11 + left->m20 * right->m12 + left->m30 * right->m13;
    float m11 = left->m01 * right->m10 + left->m11 * right->m11 + left->m21 * right->m12 + left->m31 * right->m13;
    float m12 = left->m02 * right->m10 + left->m12 * right->m11 + left->m22 * right->m12 + left->m32 * right->m13;
    float m13 = left->m03 * right->m10 + left->m13 * right->m11 + left->m23 * right->m12 + left->m33 * right->m13;
    float m20 = left->m00 * right->m20 + left->m10 * right->m21 + left->m20 * right->m22 + left->m30 * right->m23;
    float m21 = left->m01 * right->m20 + left->m11 * right->m21 + left->m21 * right->m22 + left->m31 * right->m23;
    float m22 = left->m02 * right->m20 + left->m12 * right->m21 + left->m22 * right->m22 + left->m32 * right->m23;
    float m23 = left->m03 * right->m20 + left->m13 * right->m21 + left->m23 * right->m22 + left->m33 * right->m23;
    float m30 = left->m00 * right->m30 + left->m10 * right->m31 + left->m20 * right->m32 + left->m30 * right->m33;
    float m31 = left->m01 * right->m30 + left->m11 * right->m31 + left->m21 * right->m32 + left->m31 * right->m33;
    float m32 = left->m02 * right->m30 + left->m12 * right->m31 + left->m22 * right->m32 + left->m32 * right->m33;
    float m33 = left->m03 * right->m30 + left->m13 * right->m31 + left->m23 * right->m32 + left->m33 * right->m33;

    dest->m00 = m00;
    dest->m01 = m01;
    dest->m02 = m02;
    dest->m03 = m03;
    dest->m10 = m10;
    dest->m11 = m11;
    dest->m12 = m12;
    dest->m13 = m13;
    dest->m20 = m20;
    dest->m21 = m21;
    dest->m22 = m22;
    dest->m23 = m23;
    dest->m30 = m30;
    dest->m31 = m31;
    dest->m32 = m32;
    dest->m33 = m33;
}

void Matrix44Transform(Matrix44* left, Vector4* right, Vector4* dest){
    float x = left->m00 * right->x + left->m10 * right->y + left->m20 * right->z + left->m30 * right->w;
    float y = left->m01 * right->x + left->m11 * right->y + left->m21 * right->z + left->m31 * right->w;
    float z = left->m02 * right->x + left->m12 * right->y + left->m22 * right->z + left->m32 * right->w;
    float w = left->m03 * right->x + left->m13 * right->y + left->m23 * right->z + left->m33 * right->w;

    dest->x = x;
    dest->y = y;
    dest->z = z;
    dest->w = w;
}

void Matrix44Scale(Vector3* vec, Matrix44* src, Matrix44* dest){
    dest->m00 = src->m00 * vec->x;
    dest->m01 = src->m01 * vec->x;
    dest->m02 = src->m02 * vec->x;
    dest->m03 = src->m03 * vec->x;
    dest->m10 = src->m10 * vec->y;
    dest->m11 = src->m11 * vec->y;
    dest->m12 = src->m12 * vec->y;
    dest->m13 = src->m13 * vec->y;
    dest->m20 = src->m20 * vec->z;
    dest->m21 = src->m21 * vec->z;
    dest->m22 = src->m22 * vec->z;
    dest->m23 = src->m23 * vec->z;
}

void Matrix44Rotate(float angle, Vector3* axis, Matrix44* src, Matrix44* dest){
    float c = (float) cosf(angle);
    float s = (float) sinf(angle);

    float oneminusc = 1.0f - c;

    float xy = axis->x*axis->y;
    float yz = axis->y*axis->z;
    float xz = axis->x*axis->z;
    float xs = axis->x*s;
    float ys = axis->y*s;
    float zs = axis->z*s;

    float f00 = axis->x*axis->x*oneminusc+c;
    float f01 = xy*oneminusc+zs;
    float f02 = xz*oneminusc-ys;

    float f10 = xy*oneminusc-zs;
    float f11 = axis->y*axis->y*oneminusc+c;
    float f12 = yz*oneminusc+xs;
    
    float f20 = xz*oneminusc+ys;
    float f21 = yz*oneminusc-xs;
    float f22 = axis->z*axis->z*oneminusc+c;

    float t00 = src->m00 * f00 + src->m10 * f01 + src->m20 * f02;
    float t01 = src->m01 * f00 + src->m11 * f01 + src->m21 * f02;
    float t02 = src->m02 * f00 + src->m12 * f01 + src->m22 * f02;
    float t03 = src->m03 * f00 + src->m13 * f01 + src->m23 * f02;
    float t10 = src->m00 * f10 + src->m10 * f11 + src->m20 * f12;
    float t11 = src->m01 * f10 + src->m11 * f11 + src->m21 * f12;
    float t12 = src->m02 * f10 + src->m12 * f11 + src->m22 * f12;
    float t13 = src->m03 * f10 + src->m13 * f11 + src->m23 * f12;

    dest->m20 = src->m00 * f20 + src->m10 * f21 + src->m20 * f22;
    dest->m21 = src->m01 * f20 + src->m11 * f21 + src->m21 * f22;
    dest->m22 = src->m02 * f20 + src->m12 * f21 + src->m22 * f22;
    dest->m23 = src->m03 * f20 + src->m13 * f21 + src->m23 * f22;
    dest->m00 = t00;
    dest->m01 = t01;
    dest->m02 = t02;
    dest->m03 = t03;
    dest->m10 = t10;
    dest->m11 = t11;
    dest->m12 = t12;
    dest->m13 = t13;
}

void Matrix44Translate(Vector3* vec, Matrix44* src, Matrix44* dest){
    dest->m30 += src->m00 * vec->x + src->m10 * vec->y + src->m20 * vec->z;
    dest->m31 += src->m01 * vec->x + src->m11 * vec->y + src->m21 * vec->z;
    dest->m32 += src->m02 * vec->x + src->m12 * vec->y + src->m22 * vec->z;
    dest->m33 += src->m03 * vec->x + src->m13 * vec->y + src->m23 * vec->z;
}

void Matrix44TranslateVec2(Vector2* vec, Matrix44* src, Matrix44* dest){
    dest->m30 += src->m00 * vec->x + src->m10 * vec->y;
    dest->m31 += src->m01 * vec->x + src->m11 * vec->y;
    dest->m32 += src->m02 * vec->x + src->m12 * vec->y;
    dest->m33 += src->m03 * vec->x + src->m13 * vec->y;
}

void Matrix44Negate(Matrix44* matrix){
    matrix->m00 = -matrix->m00;
    matrix->m01 = -matrix->m01;
    matrix->m02 = -matrix->m02;
    matrix->m03 = -matrix->m03;
    matrix->m10 = -matrix->m10;
    matrix->m11 = -matrix->m11;
    matrix->m12 = -matrix->m12;
    matrix->m13 = -matrix->m13;
    matrix->m20 = -matrix->m20;
    matrix->m21 = -matrix->m21;
    matrix->m22 = -matrix->m22;
    matrix->m23 = -matrix->m23;
    matrix->m30 = -matrix->m30;
    matrix->m31 = -matrix->m31;
    matrix->m32 = -matrix->m32;
    matrix->m33 = -matrix->m33;    
}



