#include "include/Camera.h"

/**
 * creates a new projection matrix
 * */
void createProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar, Matrix44* matrix);

Camera CameraCreate(float fov, float aspectRatio, float zNear, float zFar){
    Camera ret;

    ret.position.x = 0;
    ret.position.y = 0;
    ret.position.z = 0;

    ret.rotation.x = 0;
    ret.rotation.y = 0;
    ret.rotation.z = 0;

    ret.fov = fov;
    ret.zNear = zNear;
    ret.zFar = zFar;
    ret.aspect = aspectRatio;

    ret.lightPos.x = 0;
    ret.lightPos.y = 0;
    ret.lightPos.z = 0;

    Matrix44 projection = Matrix44Create();
    createProjectionMatrix(fov, aspectRatio, zNear, zFar, &projection);

    ret.projection = projection;

    Matrix44 view = Matrix44Create();
    ret.view = view;

    CameraCalculateViewMatrix(&ret);
    return ret;
}

void createProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar, Matrix44* matrix){
    float tanHalfFovy = (float)tanf(fov / 2.0f);
    matrix->m00 = 1.0f/(aspectRatio * tanHalfFovy);
    matrix->m11 = 1.0f/tanHalfFovy;
    matrix->m22 = -(zFar + zNear) / (zFar - zNear);
    matrix->m23 = -1.0f;
    matrix->m32 = -(2.0f * zFar * zNear) / (zFar - zNear);
}

void CameraRecalculateProjection(Camera* camera){
    createProjectionMatrix(camera->fov, camera->aspect, camera->zNear, camera->zFar, &camera->projection);
}

void CameraCalculateViewMatrix(Camera* camera){
    Matrix44SetIdentity(&camera->view);

    Vector3 vec = Vec3Create(1, 0, 0);
    Matrix44Rotate((float)camera->rotation.y, &vec, &camera->view, &camera->view);

    vec.x = 0;
    vec.y = 1;
    Matrix44Rotate((float)camera->rotation.x, &vec, &camera->view, &camera->view);

    vec.x = -camera->position.x;
    vec.y = -camera->position.y;
    vec.z = -camera->position.z;

    Matrix44Translate(&vec, &camera->view, &camera->view);
}




