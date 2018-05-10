#include "include/Vertex.h"
#include "include/OBJLoader.h"

Model* ModelCreate(Vertex* positions, Vector2* tCoords, Vector3* normals, int* vertexIndices, int* textureIndices, 
        int* normalIndices, int vertexCount, int textureCount, int normalCount, int indCnt){

    Model* ret = malloc(sizeof(Model));

    //set the number of vertices
    ret->vertCount = vertexCount;

    //allocate positions array
    Vertex* pos = malloc(sizeof(Vertex) * vertexCount);
    Vertex* head = pos;
    
    //set the positions to the correct values
    for(int i = 0; i < vertexCount; i++){
        pos->position.x = positions->position.x;
        pos->position.y = positions->position.y;
        pos->position.z = positions->position.z;
        
        //increment the position pointer
        pos++;
        positions++;
    }

    ret->verts = head;

    //copy the new indicies
    int* newInd = malloc(sizeof(int) * indCnt);
    int* indHead = newInd;

    for(int i = 0; i < indCnt; i++){
        *newInd = *vertexIndices; 
        newInd ++;
        vertexIndices ++;
    }

    //copy the texture coords to a list of Vector2
    Vector2* textureCoords = malloc(sizeof(Vector2) * textureCount);

    for(int i = 0; i < textureCount; i++){
        textureCoords[i].x = tCoords[i].x;
        textureCoords[i].y = tCoords[i].y;
    }

    //copy the texture coord indices
    int* textureCoordIndices = malloc(sizeof(int) * indCnt);

    for(int i = 0; i < indCnt; i++){
        textureCoordIndices[i] = textureIndices[i];
    }

    //copy normal data
    Vector3* norms = malloc(sizeof(Vector3) * normalCount);

    for(int i = 0; i < normalCount; i++){
        norms[i].x = normals[i].x;
        norms[i].y = normals[i].y;
        norms[i].z = normals[i].z;
    }

    //copy normal index data
    int* normInd = malloc(sizeof(int) * indCnt);

    for(int i = 0; i < indCnt; i++){
        normInd[i] = normalIndices[i];
    }

    //load final data
    ret->indices = indHead;
    ret->indCount = indCnt;
    ret->texCoords = textureCoords;
    ret->texIndices = textureCoordIndices;
    ret->normals = norms;
    ret->normalIndices = normInd;
    
    return ret;

}

void ModelFree(Model* model){
    free(model->verts);
    free(model->indices);
    free(model->texCoords);
    free(model->texIndices);
    free(model->normalIndices);
    free(model->normals);
    free(model);
}

Vertex VertexCreateFromVec2(const Vector2* vec){
    Vertex ret;

    ret.position.x = vec->x;
    ret.position.y = vec->y;

    return ret;
}

Vertex VertexCreate(float x, float y, float z){
    Vertex ret;

    ret.position.x = x;
    ret.position.y = y;
    ret.position.z = z;

    return ret;
}

Model* ModelLoad(const char* path){
    Model* ret;

    ModelData modelData = OBJLoadData(path);
    
    //load index data
    indLL* indList = modelData.indList;
    int indCount = 0;

    while(indList){
        indList = indList->next;
        indCount ++;
    }

    indList = modelData.indList;
    int indices[indCount];

    for(int i = 0; i < indCount; i++){
        indices[i] = indList->ind - 1;
        indList = indList->next;
    }

    //load vertex data
    vec3LL* vertList = modelData.vertList;
    int vertexCount = 0;

    while(vertList){
        vertList = vertList->next;
        vertexCount++;
    }

    Vertex vertices[vertexCount];
    vertList = modelData.vertList;

    for(int i = 0; i < vertexCount; i++){
        vertices[i] = VertexCreate(vertList->x, vertList->y, vertList->z);
        vertList = vertList->next;
    }

    //load the texture coord info
    vec2LL* texCoordList = modelData.texList;
    int texCoordCount = 0;

    while(texCoordList){
        texCoordList = texCoordList->next;
        texCoordCount ++;
    }

    Vector2 tCoords[texCoordCount];
    texCoordList = modelData.texList;

    for(int i = 0; i < texCoordCount; i++){
        tCoords[i].x = texCoordList->x;
        tCoords[i].y = texCoordList->y;
        
        texCoordList = texCoordList->next;
    }

    //load texture indices
    int texCoordIndices[indCount];
    indLL* texIndList = modelData.texIndList;

    for(int i = 0; i < indCount; i++){
        texCoordIndices[i] = texIndList->ind - 1;
        texIndList = texIndList->next;
    }

    //load the normal indices
    indLL* normalIndList = modelData.normIndList;
    int normalIndices[indCount];

    for(int i = 0; i < indCount; i++){
        normalIndices[i] = normalIndList->ind - 1;
        normalIndList = normalIndList->next;
    }

    //load the normals
    vec3LL* normalList = modelData.normList;
    int normalCount = 0;

    while(normalList){
        normalCount ++;
        normalList = normalList->next;
    }

    Vector3 normals[normalCount];
    normalList = modelData.normList;

    for(int i = 0; i < normalCount; i++){
        normals[i].x = normalList->x;
        normals[i].y = normalList->y;
        normals[i].z = normalList->z;

        normalList = normalList->next;
    }
    
    OBJFreeData(&modelData);

    //ret = ModelCreate(vertices, indices, tCoords, texCoordIndices, vertexCount, texCoordCount, indCount);
    ret = ModelCreate(vertices, tCoords, normals, indices, texCoordIndices, normalIndices, vertexCount, texCoordCount, normalCount, indCount);

    return ret;
}



