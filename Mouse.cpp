#include "Mouse.h"


Mouse::Mouse() {};
//Returns first person change in yaw and pitch 
glm::vec2 Mouse::firstPersonAngleChange(double xpos, double ypos) {
    if (firstMouse) {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouse = false;
        return glm::vec2(0, 0);
    }

    float sensitivity = 0.01f;
    float yawOffset = xpos - lastMouseX;
    float pitchOffset = lastMouseY - ypos;
    lastMouseX = xpos;
    lastMouseY = ypos;

    yawOffset *= sensitivity;
    pitchOffset *= sensitivity;
    

    if (xpos != 400 || ypos != 300) {
        lastMouseX = 400;
        lastMouseY = 300;

    }
    return glm::vec2(yawOffset, pitchOffset);
}