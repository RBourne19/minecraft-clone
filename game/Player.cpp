#include "Player.h"


Player::Player(GLfloat x, GLfloat y, GLfloat z, float pitch, float yaw)
    : pos(glm::fvec3(x, y, z)), vel(glm::fvec3(0)), acc(glm::fvec3(0)), pitch(pitch), yaw(yaw), speed(10.0f), headYOffset(1.75), focusFace(NONE), focusPos(glm::vec3(-1,-1,-1)) {}


void Player::setPosition(glm::fvec3 position) {
    pos = position;
}

void Player::updatePlayerMovement(Keyboard& keyboard) {
    float dirX = cos(yaw * (M_PI / 180.0f));
    //y doesnt really matter right now
    //float dirY = sin(pitch * (M_PI / 180.0f));
    float dirZ = sin(yaw * (M_PI / 180.0f));

    float length = sqrt(dirX * dirX + dirZ * dirZ);
    dirX /= length;
    //dirY /= length;
    dirZ /= length;

    float rightX = cos((yaw + 90) * (M_PI / 180.0f));
    float rightZ = sin((yaw + 90) * (M_PI / 180.0f));
    length = sqrt(rightX * rightX + rightZ * rightZ);
    rightX /= length;
    rightZ /= length;
    float moveX = 0.0f;
    float moveY = 0.0f;
    float moveZ = 0.0f;
    if (keyboard.getKey(GLFW_KEY_W)) {
        // forward
        moveX += dirX;
        moveZ += dirZ;
    }
    if (keyboard.getKey(GLFW_KEY_S)) {
        // backward
        moveX -= dirX;
        moveZ -= dirZ;
    }
    if (keyboard.getKey(GLFW_KEY_A)) {
        // left
        moveX -= rightX;
        moveZ -= rightZ;
    }
    if (keyboard.getKey(GLFW_KEY_D)) {
        // right
        moveX += rightX;
        moveZ += rightZ;
    }
    if (keyboard.getKey(GLFW_KEY_SPACE)) {
        vel.y = 5;
    }
    if (keyboard.getKey(GLFW_KEY_LEFT_SHIFT)) {
        pos.y -= 1;
    }
    


    float moveLength = sqrt(moveX * moveX + moveZ * moveZ);
    if (moveLength > 0.0f) {
        moveX /= moveLength;
        moveZ /= moveLength;
    }
    // Set player velocity based on the combined movement vector
    vel.x = moveX * speed;
    vel.z = moveZ * speed;
}

void Player::update(GLfloat deltaTime, World& world) {
    deltaTime = .016f;
    vel += acc * deltaTime;

    glm::fvec3 newPos = glm::fvec3(pos);
        if (world.getBlockByCoords(pos + glm::fvec3(vel.x * deltaTime, 0, 0))->type != AIR || world.getBlockByCoords(pos + glm::fvec3(vel.x * deltaTime, headYOffset, 0))->type != AIR) {
            if (vel.x > 0) {
                newPos.x = ceil(pos.x) - deltaTime;
            }
            else {
                newPos.x = floor(pos.x) + deltaTime;
            }
            vel.x = 0;

        }

        if (world.getBlockByCoords(pos + glm::fvec3(0, 0, vel.z * deltaTime))->type != AIR || world.getBlockByCoords(pos + glm::fvec3(0, headYOffset, vel.z * deltaTime))->type != AIR) {
            if (vel.z > 0) {
                newPos.z = ceil(pos.z) - deltaTime;
            }
            else {
                newPos.z = floor(pos.z) + deltaTime;
            }
            
            vel.z = 0;
        }

        if (world.getBlockByCoords(pos + glm::fvec3(0, vel.y * deltaTime, 0))->type != AIR) {
            vel.y = 0;
            acc.y = 0;
            newPos.y = floor(pos.y);
        }
        else if (world.getBlockByCoords(pos + glm::fvec3(0, vel.y *  deltaTime + headYOffset, 0))->type != AIR) {
            vel.y = 0;
        }
        else {
            acc.y = -9.8;
        }
    
    newPos += vel * deltaTime;
    pos = newPos;

    Raycast ray = Raycast::Raycast(glm::vec3(pos.x, pos.y + headYOffset, pos.z), glm::vec2(yaw, pitch), .05, 4);
    std::tuple<glm::vec3, BLOCK_FACE> focusBlock = ray.raycastBlock(world);
    focusPos = std::get<0>(focusBlock);
    focusFace= std::get<1>(focusBlock);
    
}

