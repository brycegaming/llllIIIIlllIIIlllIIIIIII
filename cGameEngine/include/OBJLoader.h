#include <stdlib.h>
#include <stdio.h>

//#define OBJL_DEBUG
#ifndef OBJLOADER_H
#define OBJLOADER_H

/**
 * a linked list holding two floating point values
 * */
typedef struct vec2LL{
    float x; 
    float y; 
    struct vec2LL* next;
} vec2LL; //Linked list of vec2 objects

/**
 * linked list of vector3 values
 * */
typedef struct vec3LL{
    float x;
    float y;
    float z;
    struct vec3LL* next;
} vec3LL; //Linked list of vec2 objects

/**
 * a linked list holding integer values: used for 
 * storing loaded indices of the model
 * */
typedef struct indLL{
    unsigned int ind;
    struct indLL* next;
} indLL; //Linked list of indicies

/**
 * holds all informaiton assiciated with an obj model
 * */
typedef struct {
    vec3LL* normList;
    vec3LL* vertList;
    vec2LL* texList;
    indLL* indList;
    indLL* texIndList;
    indLL* normIndList;
} ModelData;

/**
 * returns model data found in an obj file
 * */
ModelData OBJLoadData(const char* fileName);

/**
 * frees loaded data
 * */
void OBJFreeData(ModelData* fd);

#endif
