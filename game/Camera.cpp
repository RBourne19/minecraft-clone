#include "Camera.h"

Camera::Camera(float yaw, float pitch)
    : position(glm::vec3(0.0f, 0.0f, 1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)), front(glm::vec3(0.0f, 0.0f, -1.0f)), yaw(yaw), pitch(pitch) {
    position = position;
    worldUp = up;
    updateCameraVectors();
}

GLfloat Camera::getYaw() {
    return yaw;
}

GLfloat Camera::getPitch() {
    return pitch;
}

void Camera::updateCameraPosition(glm::fvec3& pos) {
    position = pos;
}

void Camera::updateCameraVectors() {
    glm::vec3 tempFront;
    tempFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    tempFront.y = sin(glm::radians(pitch));
    tempFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    // Normalize front vector
    front = glm::normalize(tempFront);

    // Calculate right and up vectors
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::updateCameraAngle(GLfloat yaw, GLfloat pitch) {
    this->yaw = yaw;
    this->pitch = pitch;
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}



void Camera::moveCameraAngle(float xOffset, float yOffset) {

    yaw += xOffset;
    //doing += inverts it, just a reminder
    pitch += yOffset;
    if (pitch > 90.0f) {
        pitch = 89.0f;
    }
    else if (pitch < -90.0f) {
        pitch = -89.0f;
    }

    //just to keep it safe cause there could be a chance it overflows if someone spins too much
    if (yaw > 360.0f) {
        yaw -= 360.0f;
    }
    else if (this->yaw < 0) {
        yaw += 360.0f;
    }
    updateCameraVectors();

};

