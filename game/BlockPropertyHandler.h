#pragma once
#include "GameHeaders.h"
#include "BlockProperty.h"

class BlockPropertyHandler {
public: 
    std::unordered_map<BLOCK_TYPE, BlockProperties> blockPropertiesMap;

    static BlockPropertyHandler& getInstance();
    glm::ivec2 getTexture(BLOCK_TYPE type, glm::ivec3 direction);

private:

    BlockPropertyHandler();

};