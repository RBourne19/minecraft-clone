#pragma once
#include "GameHeaders.h"
#include "Block.h"

struct BlockProperties {
    //textures
public:
    glm::ivec2 topTex, botTex, leftTex, rightTex, frontTex, backTex;
    bool transparent;

    BlockProperties();
    BlockProperties(bool transparent, glm::ivec2 texIdx);
    BlockProperties(bool transparent, glm::ivec2 topTex, glm::ivec2 botTex, glm::ivec2 leftTex, glm::ivec2 rightTex, glm::ivec2 frontTex, glm::ivec2 backTex);
private:

};