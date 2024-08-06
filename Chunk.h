#pragma once
#ifndef CHUNK_H
#define CHUNK_H
#include "GameHeaders.h"
#include "Block.h"
#include "Vertex.h"
#include "BlockMesh.h"
#include "BlockPropertyHandler.h"
#include "World.h"
#include "Structure.h"

using namespace std;
class World;
class Player;

class Chunk {
public:
	
	Chunk() : chunkX(0), chunkZ(0), solid(1000), transparent(1000), generated(false) {};
	Chunk(GLfloat x, GLfloat z);

	Block* getBlockAt(const glm::ivec3& coords, World& world);

	void generateTerrain(FastNoiseLite& noise, World& world);
	void generateMesh(World& world, Player& player);
	void renderOpaque(glm::mat4& mvp);
	void renderTransparent(glm::mat4& mvp);
	//switch this to vec
	void setBlock(glm::ivec3&, BLOCK_TYPE type);
	void loadChunk(const string filepath);
	void saveChunk(const string filepath);
	uint8_t calcAmbOcc(const glm::ivec3& blockPos, const glm::ivec3& vertOffset, World& world);

	glm::vec3 getChunkWorldCoords();
	glm::ivec3 getChunkCoords();
	bool generated;

private:
	int solidVertices, transparentVertices = 0;
	int	chunkX, chunkZ; //position relative in the world
	Block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];
	std::vector<Vertex> solid;
	std::vector<Vertex> transparent;
};

#endif