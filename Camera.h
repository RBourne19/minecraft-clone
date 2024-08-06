#pragma once
#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "GameHeaders.h"

class Camera
{
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
public:
    Camera(float yaw, float pitch);
    void moveCameraAngle(float xOffset, float yOffset);
    glm::mat4 getViewMatrix();
    void updateCameraVectors();
    void updateCameraPosition(glm::fvec3& pos);
    void updateCameraAngle(GLfloat yaw, GLfloat pitch);
    void mouseMotion(double x, double y);

    GLfloat getYaw();
    GLfloat getPitch();
};

#endif