#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include "GameHeaders.h"

enum BLOCK_TYPE {   AIR,
                    DIRT, 
                    STONE, 
                    GRASS, 
                    GLASS, 
                    WATER, 
                    SAND,
                    WOOD,
                    LEAF,
                    BEDROCK,
                    PLANK
};
enum BLOCK_FACE { TOP, BOTTOM, NORTH, WEST, SOUTH, EAST, NONE };

struct Block {
    public:
        BLOCK_TYPE type;
        Block(BLOCK_TYPE type);
        Block();
    private:
};


void updateBlockTextures();

extern GLubyte indices[36];
extern GLfloat vertices[72];
#endif