#include "include/Vector4.h"

Vector4 Vec4Create(float x, float y, float z, float w){
    Vector4 ret;

    ret.x = x;
    ret.y = y;
    ret.z = z;
    ret.w = w;

    return ret;
}

Vector4 Vec4CreateFromVec3(Vector3 vector){
    Vector4 ret;

    ret.x = vector.x;
    ret.y = vector.y;
    ret.z = vector.z;
    ret.w = 0;

    return ret;
}
