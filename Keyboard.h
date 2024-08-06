#pragma once
#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "GameHeaders.h"
#include "Camera.h"

class Keyboard
{
private:
    bool keys[256];
    bool firstMouse;
    float lastMouseX, lastMouseY;
public:
    void setKey(unsigned char key, bool state);
    bool getKey(unsigned char key);

    void mouseMotion(double x, double y, Camera* camera);
    Keyboard();
};


#endif