#include "include/Quaternion.h"

/**
code written based off lwjgl Quaternionn math
*/

Quat QuatCreate(float x, float y, float z, float w){
    Quat  ret;

    ret.x = x;
    ret.y = y;
    ret.z = z;
    ret.w = w;

    return ret;
}

void QuatToMatrix44(Quat* src, Matrix44* dest){
}

void QuatRotateX(Quat* src, float angle){
}

void QuatRotateY(Quat* src, float angle){
}

void QuatRotateZ(Quat* src, float angle){
}

void QuatSetxy(Quat* quat, float x, float y){
    quat->x = x;
    quat->y = y;
}

void QuatSetxyz(Quat* quat, float x, float y, float z){
    quat->x = x;
    quat->y = y;
    quat->z = z;
}

void QuatSetxyzw(Quat* quat, float x, float y, float z, float w){
    quat->x = x;
    quat->y = y;
    quat->z = z;
    quat->w = w;
}

void QuatSetIdentity(Quat* quat){
    quat->x = 0;
    quat->y = 0;
    quat->z = 0;
    quat->w = 1;
}

float QuatLength(Quat* quat){
    return sqrt(quat->x * quat->x + quat->y * quat->y + quat->z * quat->z + quat->w * quat->w);
}

void QuatNormalize(Quat* src, Quat* dest){
    float invl = 1 / QuatLength(src);

    QuatSetxyzw(dest, src->x * invl, src->y * invl, src->z * invl, src->w * invl);
}

float QuatDot(Quat* left, Quat* right){
    return left->x * right->x + left->y * right->y + left->z * right->z + left->w * right->w; 
} 

void QuatNegate(Quat* quat){
    quat->x = -quat->x;
    quat->y = -quat->y;
    quat->z = -quat->z;
    quat->w = -quat->w;
}

void QuatScale(float scale, Quat* src, Quat* dest){
    dest->x = src->x * scale;
    dest->y = src->y * scale;
    dest->z = src->z * scale;
    dest->w = src->w * scale;
}

void QuatMult(Quat* left, Quat* right, Quat* dest){
    QuatSetxyzw(dest, left->x * right->w + left->w * right->x + left->y * right->z
            - left->z * right->y, left->y * right->w + left->w * right->y
            + left->z * right->x - left->x * right->z, left->z * right->w
            + left->w * right->z + left->x * right->y - left->y * right->x,
            left->w * right->w - left->x * right->x - left->y * right->y
            - left->z * right->z);
}

float QuatLengthSquared(Quat* quat){
    return quat->x * quat->x + quat->y * quat->y + quat->z * quat->z + quat->w * quat->w;
}

void QuatMultInverse(Quat* left, Quat* right, Quat* dest){
    float n = QuatLengthSquared(right);

    /**
     * dont divide by zero
     * */
    if(n == 0){
        n = 1;
    }
    else{
        n = 1 / n;
    }

    QuatSetxyzw(dest, (left->x * right->w - left->w * right->x - left->y
                * right->z + left->z * right->y)
            * n, (left->y * right->w - left->w * right->y - left->z
                * right->x + left->x * right->z)
            * n, (left->z * right->w - left->w * right->z - left->x
                * right->y + left->y * right->x)
            * n, (left->w * right->w + left->x * right->x + left->y
                * right->y + left->z * right->z)
            * n);
}

void QuatSetFromAxisAngle(Quat* quat, Vector4* vec4){
    quat->x = vec4->x;
    quat->y = vec4->y;
    quat->z = vec4->z;

    float n = (float) sqrt(quat->x * quat->x + quat->y * quat->y + quat->z * quat->z);
    float s = (float) (sin(0.5 * vec4->w) / n);

    quat->x *= s;
    quat->y *= s;
    quat->z *= s;
    quat->w = (float) cos(0.5 * vec4->w);
}

//code taken from http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
void QuatRotateMatrix(Quat* q, Matrix44* dest){
    float sqw = q->w*q->w;
    float sqx = q->x*q->x;
    float sqy = q->y*q->y;
    float sqz = q->z*q->z;

    float invs = 1 / (sqx + sqy + sqz + sqw);
    dest->m00 = ( sqx - sqy - sqz + sqw)*invs; 
    dest->m11 = (-sqx + sqy - sqz + sqw)*invs;
    dest->m22 = (-sqx - sqy + sqz + sqw)*invs;

    float tmp1 = q->x*q->y;
    float tmp2 = q->z*q->w;
    dest->m10 = 2.0f * (tmp1 + tmp2)*invs;
    dest->m01 = 2.0f * (tmp1 - tmp2)*invs;

    tmp1 = q->x*q->z;
    tmp2 = q->y*q->w;
    dest->m20 = 2.0f * (tmp1 - tmp2)*invs;
    dest->m02 = 2.0f * (tmp1 + tmp2)*invs;
    tmp1 = q->y*q->z;
    tmp2 = q->x*q->w;
    dest->m21 = 2.0f * (tmp1 + tmp2)*invs;
    dest->m12 = 2.0f * (tmp1 - tmp2)*invs;
}





