#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "GameHeaders.h"
#include "Block.h"
#include "Keyboard.h"
#include "World.h"
#include "Raycast.h"

class World;

class Player {
public:
    GLfloat headYOffset;
    glm::fvec3 pos;      // Position
    glm::vec3 focusPos;
    glm::ivec2 chunkCoord;
    Player(GLfloat x, GLfloat y, GLfloat z, float pitch, float yaw);

    float   pitch, yaw, speed;

    //kinda redundant but oh well
    //currently focused bloc
    BLOCK_FACE focusFace = NONE;
    void update(GLfloat deltaTime, World& world);
    void updatePlayerMovement(Keyboard& keyboard);
    void placeBlock(BLOCK_TYPE type);
    void destroyBlock();
    void setPosition(glm::fvec3 pos);
private:
    glm::fvec3 vel;
    glm::fvec3 acc; // Acceleration
};


#endif