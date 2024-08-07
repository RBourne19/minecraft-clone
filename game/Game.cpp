#include "Game.h"
#include "Mouse.h"
#include <iostream>


Game::Game(int seed) : runGame(false), world(seed), player(0, 200, 1, 0, 0), camera(-90.0f, 0.0f) {};
Game::Game() : runGame(false), world(0), player(0, 100, 0, 0, 0),  camera(-90.0f, 0.0f) {};
//should be a better way
void Game::mouseMotion(double xpos, double ypos, Mouse& mouse) {

    glm::vec2 angleOffset = mouse.firstPersonAngleChange(xpos, ypos);
    camera.moveCameraAngle(angleOffset.x, angleOffset.y);
    player.pitch = camera.getPitch();
    player.yaw = camera.getYaw();
}

void Game::mouseClick(int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        world.setBlockByCoords(player.focusPos, AIR);
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        glm::vec3 blockPos = BlockMesh::offsetByFace(player.focusPos, player.focusFace);
        if (1) {
            world.setBlockByCoords(blockPos, player.currentBlock);
        }

    }
    //add place block
}

void Game::init() {
    skybox.init();

    world.init(player);
    world.updateChunkMap(player.chunkCoord);
};

void Game::update(GLfloat deltaTime) {
    player.update(deltaTime, world);

    glm::vec3 newCameraPos = glm::fvec3(player.pos.x, player.pos.y + player.headYOffset, player.pos.z);

    camera.updateCameraPosition(newCameraPos);
};

void Game::render(glm::mat4& mvp) {
    glLoadIdentity();   
    
    skybox.render(mvp);


    world.render(player, mvp);

};

glm::mat4 Game::getGameView() {
    return camera.getViewMatrix();
}


void Game::keyboardInput(Keyboard& keyboard) {
    player.keyboardInputHandler(keyboard);
}