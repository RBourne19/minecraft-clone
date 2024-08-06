#include "BlockProperty.h"


BlockProperties::BlockProperties() : transparent(true), topTex(0), botTex(0), leftTex(0), rightTex(0), frontTex(0), backTex(0) {};
BlockProperties::BlockProperties(bool transparent, glm::ivec2 texture) : transparent(transparent), topTex(texture), botTex(texture), leftTex(texture), rightTex(texture), frontTex(texture), backTex(texture) {


};
BlockProperties::BlockProperties(bool transparent, glm::ivec2 topTex, glm::ivec2 botTex, glm::ivec2 leftTex, glm::ivec2 rightTex, glm::ivec2 frontTex, glm::ivec2 backTex) :
    transparent(transparent), topTex(topTex), botTex(botTex), leftTex(leftTex), rightTex(rightTex), frontTex(frontTex), backTex(backTex) {};

