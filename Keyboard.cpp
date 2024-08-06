#include "Keyboard.h"

Keyboard::Keyboard() : firstMouse(true) {};

void Keyboard::setKey(unsigned char key, bool state) {
    keys[key] = state;
}
bool Keyboard::getKey(unsigned char key) {
    return keys[key];
}

void Keyboard::mouseMotion(double xpos, double ypos, Camera* camera) {
    
}