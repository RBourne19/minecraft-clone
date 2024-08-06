#pragma once
#ifndef WORLD_H
#define WORLD_H
#include "GameHeaders.h"
#include "Player.h"
#include "Chunk.h"
#include "VertexArray.h"

using namespace std;

class Chunk;
class Player;

struct ChunkHash {
    size_t operator()(const tuple<int, int>& key) const {
        auto hash1 =  hash<int>{}( get<0>(key));
        auto hash2 =  hash<int>{}( get<1>(key));
        return hash1 ^ (hash2 << 1); // Combine the hashes
    }
};
struct ChunkEqual {
    bool operator()(const  tuple<int, int>& lhs, const tuple<int, int>& rhs) const {
        return lhs == rhs;
    }
};
class World {

public:
     unordered_map< tuple<int, int>, Chunk*, ChunkHash, ChunkEqual> chunkMap;
    
    void render(Player& player, glm::mat4& mvp);
    void updateChunkMap(glm::ivec2& newCenter);
    World(int seed);
    void init(Player& player);
    Block* getBlockByCoords(const glm::fvec3& coords);
    Chunk* getChunkByCoords(const glm::ivec2& chunkCoords);
    void setBlockByCoords(const glm::vec3& coords, BLOCK_TYPE type);
     vector<Chunk*> sortChunksByDistance(
        const unordered_map<tuple<int, int>, Chunk*, ChunkHash, ChunkEqual>& chunkMap,
        const tuple<int, int>& referencePoint);

     void loadChunk(glm::ivec2 chunkCoord, Chunk& chunk);
     void saveChunk(Chunk& chunk);

     void addToBlockBuffer(glm::ivec3 coord, Block b);
     void clearBlockBuffer();
private:
    int seed;
    string filename;
    FastNoiseLite noise;
    VertexArray* va = nullptr;
    //all the blocks that needed to be placed from structures which span chunks
    vector<tuple<glm::ivec3, Block>>  blockBuffer;
};
#endif 
