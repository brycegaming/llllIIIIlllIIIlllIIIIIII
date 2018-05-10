#include "include/Vector3.h"

Vector3 Vec3Create(float x, float y, float z){
    Vector3 ret;

    ret.x = x;
    ret.y = y;
    ret.z = z;

    return ret;
}

float Vec3Magnitude(const Vector3* vec3){
    return sqrt(vec3->x * vec3->x + vec3->y * vec3->y + vec3->z * vec3->z);
}

void Vec3Free(Vector3* vector){
    free(vector);
}

Vector3 Vec3Sub(const Vector3* Lop, const Vector3* Rop){
    return Vec3Create(Lop->x - Rop->x, Lop->y - Rop->y, Lop->z - Rop->z);
}

Vector3 Vec3Add(const Vector3* Lop, const Vector3* Rop){
    return Vec3Create(Lop->x + Rop->x, Lop->y + Rop->y, Lop->z + Rop->z);
}

Vector3 Vec3Mul(const Vector3* Lop, const Vector3* Rop){
    return Vec3Create(Lop->x * Rop->x, Lop->y * Rop->y, Lop->z * Rop->z);
}

Vector3 Vec3Div(const Vector3* Lop, const Vector3* Rop){
    return Vec3Create(Lop->x / Rop->x, Lop->y / Rop->y, Lop->z / Rop->z);
}

Vector3 Vec3Scale(const Vector3* Lop, float scale){
    return Vec3Create(Lop->x * scale, Lop->y * scale, Lop->z * scale);
}

 float Vec3Distance(const Vector3* one, const Vector3* two){
     Vector3 relativePosition = Vec3Sub(one, two);
     return Vec3Magnitude(&relativePosition);
 }

 float Vec3Dot(const Vector3* one, const Vector3* two){
     return sqrt(one->x * two->x + one->y * two->y + one->z * two->z);
 }
 
 Vector3 Vec3GetNormalized(const Vector3* vec){
    Vector3 ret;

    float mag = Vec3Magnitude(vec);
    ret.x = vec->x / mag;
    ret.y = vec->y / mag;
    ret.z = vec->z / mag;

    return ret;
 }

 Vector3 Vec3Cross(const Vector3* one, const Vector3* two){
     Vector3 ret;

     ret.x = (one->y * two->z) - (one->z * two->y);
     ret.y = (one->z * two->x) - (one->x * two->z);
     ret.z = (one->x * two->y) - (one->y * two->x);

     return ret;
 }

 void Vec3Load(Vector3* l, const Vector3* r){
    l->x = r->x;
    l->y = r->y;
    l->z = r->z;
 }



