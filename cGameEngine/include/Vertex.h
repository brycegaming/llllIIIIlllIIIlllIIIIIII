#ifndef INCLUDE_VERTEX
#define INCLUDE_VERTEX

#include "Vector2.h"
#include "Vector3.h"
#include "defs.h"

/**
 * holds information reguarding a specified vertex
 * this is processed by the renderer
 * */
typedef struct vert{
    Vector3 position;
}Vertex;

/**
 * defines a model
 * models are a set of vertices that can be rendered
 * */
typedef struct Model{
    Vertex* verts;
    Vector2* texCoords;
    Vector3* normals;

    int* indices;
    int* texIndices;
    int* normalIndices;
    
    int vertCount;
    int indCount;
}Model;

/**
 * creates a vertex
 * */
Vertex VertexCreate(float x, float y, float z);

/**
 * creates a vertex from a vector2
 * */
Vertex VertexCreateFromVec2(const Vector2* vec);

/**
 * creates a model based on passed Vector2 positions
 * */
//Model* ModelCreate(Vertex* positions, int* indices, Vector2* tCoords, int* tInd, Vector3* normals, int* nInd, int normalCount, int tCoordCount, int vertexCount, int indCnt);
Model* ModelCreate(Vertex* positions, Vector2* textureCoords, Vector3* normals, int* vertexIndices, int* textureIndices, 
        int* normalIndices, int normalCount, int textureCount, int vertexCount, int indCnt);

/**
 * loads a model from an obj file
 * */
Model* ModelLoad(const char* path);

/**
 * frees memory associated with model
 * */
void ModelFree(Model* model);

#endif
