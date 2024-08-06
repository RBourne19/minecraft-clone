#pragma once
#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "GameHeaders.h"
#include "Block.h"





//a collection of relative points
class Structure {
public:
	std::vector<std::tuple<glm::ivec3, Block>> blocks;
private:
};




#endif // !STRUCTURE_H
