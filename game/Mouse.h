#pragma once
#ifndef MOUSE_H
#define MOUSE_H
#include "GameHeaders.h"


class Mouse
{
private:
    bool firstMouse;
    float lastMouseX, lastMouseY;
public:
    
    Mouse();
    glm::vec2 firstPersonAngleChange(double x, double y);
};


#endif