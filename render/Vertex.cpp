#include "Vertex.h"


Vertex::Vertex(const glm::ivec3& position, const glm::bvec2& uv)  {
	offsetPosition(position.x, position.y, position.z);
	setUv(uv.x, uv.y);
};

Vertex::Vertex() {
	data = 0;
};
// y: 0-8 x: 9-13, z: 14-18
void Vertex::offsetPosition(uint32_t x, uint32_t y, uint32_t z) {
	data += y;
	data += x << 9;
	data += z << 14;
	
}

glm::ivec3 Vertex::getPos() {
	return { (data >> 9) & 0x1fu, data & 0x1ffu, (data >> 14) & 0x1fu };
};

//uvx: 19 uvy: 20
void Vertex::setUv(bool x, bool y) {
	uint8_t uv = x | (y << 1);

	data += uv << 19;
}
//tile index: 21-28
void Vertex::setTexture(uint8_t x, uint8_t y) {
	uint8_t uv = x | (y << 4);

	data += uv << 21;
}

void Vertex::setTextureVec(glm::ivec2 vec) {
	setTexture(vec.x, vec.y);
}

void Vertex::setOcclusion(uint8_t occlusionLevel) {
	data |= occlusionLevel << 29;
}