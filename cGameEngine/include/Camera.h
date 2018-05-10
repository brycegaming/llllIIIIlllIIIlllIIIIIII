#ifndef INCLUDE_CAMERA
#define INCLUDE_CAMERA

#include "defs.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Matrix22.h"
#include "Matrix44.h"

/**
 * specifies information reguarding a camera
 * including forward vector, up vector
 * position, etc
 * */
typedef struct cam{
    Vector3 position;
    Vector3 rotation;
    Vector3 lightPos;

    float fov;
    float zNear;
    float zFar;
    float aspect;

    Matrix44 projection;
    Matrix44 view;
}Camera;

/**
 * creates a new camera
 * */
Camera CameraCreate(float fov, float aspectRatio, float zNear, float zFar);

/**
 * recalculates the projection matrix for the camera
 * using values that are currently in the camera struct
 * */
void CameraRecalculateProjection(Camera* camera);

/**
 * calculates the camera view Matrix
 * */
void CameraCalculateViewMatrix(Camera* camera);

#endif
