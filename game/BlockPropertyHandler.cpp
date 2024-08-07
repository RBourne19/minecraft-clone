#include "BlockPropertyHandler.h"

BlockPropertyHandler::BlockPropertyHandler() :
    blockPropertiesMap(
        {
            {AIR, BlockProperties(true, glm::ivec2(-1, -1))},
            {DIRT, BlockProperties(false, glm::ivec2(2, 0))},
            {STONE, BlockProperties(false, glm::ivec2(1, 0))},
            {GRASS, BlockProperties(false, glm::ivec2(0, 0), glm::ivec2(2, 0), glm::ivec2(3, 0), glm::ivec2(3, 0), glm::ivec2(3, 0) ,glm::ivec2(3, 0))},
            {GLASS, BlockProperties(true, glm::ivec2(1,3))},
            {WATER, BlockProperties(true, glm::ivec2(13, 12))},
            {SAND, BlockProperties(false, glm::ivec2(2, 1))},
            {WOOD, BlockProperties(false, glm::ivec2(5,1), glm::ivec2(5,1), glm::ivec2(4,1), glm::ivec2(4,1), glm::ivec2(4,1), glm::ivec2(4,1))},
            {LEAF, BlockProperties(true, glm::ivec2(4, 3))},
            {BEDROCK, BlockProperties(false, glm::ivec2(1, 1))},
            {PLANK, BlockProperties(false, glm::ivec2(4, 0))},



        }
) {};

BlockPropertyHandler& BlockPropertyHandler::getInstance() {
    static BlockPropertyHandler instance;
    return instance;
};

glm::ivec2 BlockPropertyHandler::getTexture(BLOCK_TYPE type, glm::ivec3 direction) {
    BlockProperties bp = blockPropertiesMap[type];

    switch (direction.x)
    {
    case -1:
        return bp.leftTex;
        break;
    case 1:
        return bp.rightTex;
        break;
    default:
        break;
    }
    switch (direction.y)
    {
    case -1:
        return bp.botTex;
        break;
    case 1:
        return bp.topTex;
        break;
    default:
        break;
    }
    switch (direction.z)
    {
    case -1:
        return bp.frontTex;
        break;
    case 1:
        return bp.backTex;
        break;
    default:
        break;
    }

    return glm::ivec2(-1, -1);
}