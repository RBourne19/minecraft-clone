#pragma once
#ifndef VERTEX_H
#define VERTEX_H
#include "GameHeaders.h"

class Vertex {
public:
	//might be able to do this unsigned
	Vertex(const glm::ivec3& position, const glm::bvec2& uv);
	uint32_t data = 0;
	void offsetPosition(uint32_t x, uint32_t y, uint32_t z);

	void setUv(bool x, bool y);

	void setTexture(uint8_t x, uint8_t y);
	void setTextureVec(glm::ivec2 vec);
	void setOcclusion(uint8_t level);

	glm::ivec3 getPos();

	Vertex();
private:


};

#endif // VERTEX_H
