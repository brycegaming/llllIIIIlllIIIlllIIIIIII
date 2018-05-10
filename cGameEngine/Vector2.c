#include "include/Vector2.h"

float Vec2Magnitude(Vector2* vector2){
    return sqrt((vector2->x * vector2->x) + (vector2->y * vector2->y));
}

Vector2 Vec2Create(float x, float y){
    Vector2 ret;

    ret.x = x;
    ret.y = y;
    
    return ret;
}

Vector2* Vec2Allocate(float x, float y){
    Vector2* ret = (Vector2*) malloc(sizeof(Vector2));

    ret->x = x;
    ret->y = y;

    return ret;
}

void Vec2Free(Vector2* mem){
    free(mem);
}

Vector2 Vec2Sub( Vector2* Lop,  Vector2* Rop){
    return Vec2Create(Lop->x - Rop->x, Lop->y - Rop->y);
}

Vector2 Vec2Add( Vector2* Lop,  Vector2* Rop){
    return Vec2Create(Lop->x + Rop->x, Lop->y + Rop->y);
}

Vector2 Vec2Mul( Vector2* Lop,  Vector2* Rop){
    return Vec2Create(Lop->x * Rop->x, Lop->y * Rop->y);
}

Vector2 Vec2Div( Vector2* Lop,  Vector2* Rop){
    return Vec2Create(Lop->x / Rop->x, Lop->y / Rop->y);
}

Vector2 Vec2Scale( Vector2* Lop, float scale){
    return Vec2Create(Lop->x * scale, Lop->y * scale);
}

float Vec2Distance( Vector2* one,  Vector2* two){
    Vector2 relativePos = Vec2Sub(one, two);
    return Vec2Magnitude(&relativePos);
}

float Vec2Dot( Vector2* one,  Vector2* two){
    return ((one->x * two->x) + (one->y * two->y));
}

void Vec2Normalize(Vector2* vec){
    float mag = Vec2Magnitude(vec);
    vec->x /= mag;
    vec->y /= mag;
}

Vector2 Vec2GetNormalized( Vector2* vec){
    Vector2 cpy = Vec2Copy(vec);
    Vec2Normalize(&cpy);
    return cpy;
}

Vector2 Vec2Copy( Vector2* vector){
    Vector2 ret;

    ret.x = vector->x;
    ret.y = vector->y;

    return ret;
}

