#pragma once
#ifndef RAYCAST_H
#define RAYCAST_H
#include "GameHeaders.h"
#include "Block.h"
#include "World.h"

class World;

class Raycast {
public:
	Raycast(glm::vec3 origin, glm::vec2 angles, GLfloat stepDistance, GLfloat maxDepth);

	std::tuple<glm::vec3, BLOCK_FACE> raycastBlock(World& world);

private:
	glm::vec3 origin;
	glm::vec2 angles;
	GLfloat maxDepth, stepDistance;


};


#endif // !RAYCAST_H
