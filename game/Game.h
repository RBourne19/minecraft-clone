#pragma once
#ifndef GAME_H
#define GAME_H
#include "Skybox.h"

#include "GameHeaders.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "World.h"
#include "Player.h"
#include "BlockPropertyHandler.h"

class Skybox;

class Game {
public:
    Game(int seed);
    Game();
    void update(GLfloat deltaTime);
    void render(glm::mat4& mvp);
    void init();
    void mouseMotion(double xpos, double ypos, Mouse& mouse);
    void keyboardInput(Keyboard& keyboard);
    void mouseClick(int button, int action, int mods);
    glm::mat4 getGameView();

    Skybox skybox;

private:

    bool runGame;
    World world;
    Player player;
    Camera camera;
};

#endif