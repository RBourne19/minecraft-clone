#include "App.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "AssetManager.h"
#include "Frustum.h"


#define SCR_WIDTH 800
#define SCR_HEIGHT 600

App::App(GLFWwindow* window) : window(window) {

};



void App::update() {

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    game.keyboardInput(keyboard);
    game.update(deltaTime);
    glMatrixMode(GL_MODELVIEW);
    glm::mat4 view = game.getGameView();
    
    glm::mat4 MVP = projection * view * model;

    Frustum::getInstance().update(MVP);
    game.skybox.update(projection, game.getGameView(), deltaTime);
    game.render(MVP);


}
void App::setWindow(GLFWwindow* window) {
    window = window;
}

void App::init() {
    projection = glm::perspective(glm::radians(45.0f), (float)displayWidth / (float)displayHeight, 0.01f, (float)((RENDER_DISTANCE)*(CHUNK_WIDTH + 2)));


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    AssetManager::getInstance().loadShader("opaque", "vertShader.glsl", "fragShader.glsl");
    AssetManager::getInstance().loadShader("transparent", "transparentVert.glsl", "transparentFrag.glsl");
    AssetManager::getInstance().loadShader("outline", "outlineVertShader.glsl", "outlineFragShader.glsl");
    AssetManager::getInstance().loadShader("skybox", "skyboxVert.glsl", "skyboxFrag.glsl");

    AssetManager::getInstance().loadTexture("default", "texture-atlas.png");
    AssetManager::getInstance().loadTexture("skybox", "sky.png");

    AssetManager::getInstance().getTexture("default")->bindTexture();

    game.init();
}

void App::mouseHandler(GLFWwindow* window, double xpos, double ypos) {
    game.mouseMotion(xpos, ypos, mouse);
}

void App::mouseInputHandler(GLFWwindow* window, int button, int action, int mods) {
    game.mouseClick(button, action, mods);
}

void App::keyboardHandler(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        keyboard.setKey(key, true);

    }
    if (action == GLFW_RELEASE) {
        keyboard.setKey(key, false);

    }
    if (keyboard.getKey(GLFW_KEY_ESCAPE)){
        exit(0);
    }
    

}