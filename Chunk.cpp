#include "Chunk.h"
#include "Frustum.h"
#include "AssetManager.h"
#include "Tree.h"
#define WATER_LEVEL 60

Chunk::Chunk(GLfloat chunkX, GLfloat chunkZ) : chunkX(chunkX), chunkZ(chunkZ), solid(1000000), transparent(10000), generated(false) {
};


void Chunk::generateTerrain(FastNoiseLite& noise, World& world) {
    for (int x = 0; x < CHUNK_WIDTH; ++x) {
        for (int z = 0; z < CHUNK_WIDTH; ++z) {
            float nx = ((chunkX * CHUNK_WIDTH + x) / 4.0f) - .5f;
            float nz = ((chunkZ * CHUNK_WIDTH + z) / 4.0f) - .5f;
            float height = 2 * noise.GetNoise(2 * nx, 2 * nz);
            height = (height + 1) * 0.5f * (CHUNK_HEIGHT - 1);
            height = fmax(0, fmin(CHUNK_HEIGHT - 1, height));
            int terrainHeight = static_cast<int>(height);

            for (int y = 0; y < CHUNK_HEIGHT; ++y) {

                if (terrainHeight <= WATER_LEVEL) {
                    //OCEAN STUFF
                    if (y < terrainHeight) {
                        blocks[x][y][z] = Block(SAND);
                    }
                    else if (WATER_LEVEL >= y) {
                        blocks[x][y][z] = Block(WATER);
                    }

                }

                else if (y == terrainHeight + 1) {
                    //generate tree
                    float treeNoise = noise.GetNoise(float(chunkX * CHUNK_WIDTH + x) * y, float(chunkZ * CHUNK_WIDTH + z) * y);
                    if (treeNoise > .7) {
                        Structure* tree = new Tree(treeNoise);
                        for (const auto& v : tree->blocks) {
                            glm::ivec3 coord = std::get<0>(v) + glm::ivec3(x, y, z);
                            Block b = std::get<1>(v);

                            if (coord.x >= 0 && coord.x < CHUNK_WIDTH && coord.z >= 0 && coord.z < CHUNK_WIDTH && coord.y >= 0 && coord.y < CHUNK_HEIGHT) {
                                blocks[coord.x][coord.y][coord.z] = b;
                            }
                            else {
                                world.addToBlockBuffer(glm::ivec3(coord.x + (CHUNK_WIDTH * chunkX), coord.y, coord.z + (CHUNK_WIDTH * chunkZ)), b);
                            }

                        }
                    }
                }
                else if (y == terrainHeight) {
                    blocks[x][y][z] = Block(GRASS);
                }
                else if (y < terrainHeight) {
                    if (terrainHeight - y < 4) {
                        blocks[x][y][z] = Block(DIRT); 
                    }
                    else {
                        blocks[x][y][z] = Block(STONE);
                    }
                }
                if (y == 0) {
                    blocks[x][y][z] = Block(BEDROCK);
                }
            }
        }
    }
    generated = true;
};

//Checks if coordinates are within chunk, if not then get block from world
Block* Chunk::getBlockAt(const glm::ivec3& coords, World& world) {

    //make sure its in height range at some point
    if (coords.x < 0 || coords.x >= CHUNK_WIDTH || coords.z < 0 || coords.z >= CHUNK_WIDTH) {
        //get in world
        glm::vec3 worldCoords = glm::ivec3(coords.x + (CHUNK_WIDTH * chunkX), coords.y, coords.z + (CHUNK_WIDTH * chunkZ));
        return world.getBlockByCoords(worldCoords);
    }
    else {
        return &blocks[coords.x][coords.y][coords.z];
    }
    //fix to nullptr later
    return new Block(AIR);
}


void Chunk::generateMesh(World& world, Player& player) {
    const std::array<glm::ivec3, 6> offsetsToCheck = { {
     {1, 0, 0},
     {-1, 0, 0},
     {0, 1, 0},
     {0, -1, 0},
     {0, 0, 1},
     {0, 0, -1},
  } };


    solidVertices = 0;
    transparentVertices = 0;

    for (int x = CHUNK_WIDTH - 1; x >= 0; x--) {
        for (int y = CHUNK_HEIGHT - 1; y >= 0; y--) {
            for (int z = CHUNK_WIDTH - 1; z >= 0; z--) {
                Block* b = &blocks[x][y][z];
                if (b->type == AIR) continue;

                glm::ivec3 currCoord = glm::ivec3(x, y, z);
                glm::ivec3 worldCoord = glm::ivec3(x + (CHUNK_WIDTH * chunkX), y, z + (CHUNK_WIDTH * chunkZ));

                if (!Frustum::getInstance().isBoxInFrustum(worldCoord, worldCoord + glm::ivec3(1, 1, 1))) continue;

                for (const glm::ivec3& offsetVector : offsetsToCheck) {

                    

                    //check if player can even see this side of the block

                    switch (offsetVector.x) {
                    case 1:
                        if (player.pos.x < worldCoord.x + 1) continue;
                        break;

                    case -1:
                        if (player.pos.x > worldCoord.x) continue;
                        break;
                    default:
                        break;
                    }

                    switch (offsetVector.y) {
                    case 1:
                        if ((player.pos.y + player.headYOffset) < (worldCoord.y + 1)) continue;
                        break;

                    case -1:
                        if ((player.pos.y + player.headYOffset) > worldCoord.y) continue;
                        break;


                    default:
                        break;
                    }

                    switch (offsetVector.z) {
                    case 1:
                        if (player.pos.z < worldCoord.z + 1) continue;
                        break;

                    case -1:
                        if (player.pos.z > worldCoord.z) continue;
                        break;


                    default:
                        break;
                    }

                    //check the position of the adjacent blocks using the offsets
                    Block* adjacent = getBlockAt(currCoord + offsetVector, world);

                    if (!adjacent) continue;

                    bool s = (BlockPropertyHandler::getInstance().blockPropertiesMap[adjacent->type].transparent == BlockPropertyHandler::getInstance().blockPropertiesMap[b->type].transparent && adjacent->type != AIR);
                    if (s || adjacent->type == b->type) continue;


                    for (const auto& blockVertex : BlockMesh::getVerticesFromDirection(offsetVector)) {
                        Vertex vertex = blockVertex;
                        vertex.offsetPosition(x, y, z);
                        vertex.setTextureVec(BlockPropertyHandler::getInstance().getTexture(b->type, offsetVector));

                        if (offsetVector.y == -1) {
                            vertex.setOcclusion(0);
                        }
                        else {
                            vertex.setOcclusion(calcAmbOcc(currCoord, vertex.getPos() - currCoord, world));

                        }

                        if (BlockPropertyHandler::getInstance().blockPropertiesMap[b->type].transparent) {
                            transparent.at(transparentVertices) = vertex;
                            transparentVertices += 1;
                        }
                        else {
                            solid.at(solidVertices) = vertex;
                            solidVertices += 1;
                        }
                        
                    }


                }
            
            }
        }
    }
}

uint8_t Chunk::calcAmbOcc(const glm::ivec3& blockPos, const glm::ivec3& vertOffset, World& world) {
    
    glm::ivec3 blockDirection = glm::sign(glm::vec3(vertOffset) - glm::vec3(0.5));

    Block* blockAdjacentXY = this->getBlockAt(blockPos + blockDirection * glm::ivec3(1, 1, 0), world);
    uint8_t isBlockAdjacentXY = (blockAdjacentXY && blockAdjacentXY->type != AIR) ? 1 : 0;

    Block* blockAdjacentYZ = this->getBlockAt(blockPos + blockDirection * glm::ivec3(0, 1, 1), world);
    uint8_t isBlockAdjacentYZ = (blockAdjacentYZ && blockAdjacentYZ->type != AIR) ? 1 : 0;

    if (isBlockAdjacentXY && isBlockAdjacentYZ) {
        return 0;
    }

    Block* blockDiagonal = this->getBlockAt(blockPos + (blockDirection * glm::ivec3(1, 1, 1)), world);
    uint8_t isBlockDiagonal = (blockDiagonal && blockDiagonal->type != AIR) ? 1 : 0;

    return 3 - (isBlockAdjacentXY + isBlockAdjacentYZ + isBlockDiagonal);
}
    


void Chunk::renderOpaque(glm::mat4& mvp) {
    
    std::shared_ptr<Shader> s = AssetManager::getInstance().getShader("opaque");
    s->use();
    s->setMat4("MVP", glm::translate(mvp, glm::vec3(this->getChunkCoords() * CHUNK_WIDTH)));

    glBufferData(GL_ARRAY_BUFFER, solidVertices * sizeof(Vertex), solid.data(), GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, solidVertices);

    
}

void Chunk::renderTransparent(glm::mat4& mvp) {
    

    std::shared_ptr<Shader> s = AssetManager::getInstance().getShader("transparent");
    s->use();
    s->setMat4("MVP", glm::translate(mvp, glm::vec3(this->getChunkCoords() * CHUNK_WIDTH)));

    glBufferData(GL_ARRAY_BUFFER, transparentVertices * sizeof(Vertex), transparent.data(), GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, transparentVertices);
}

void Chunk::setBlock(glm::ivec3& coords, BLOCK_TYPE type) {

    if (coords.x >= CHUNK_WIDTH || coords.x < 0 || coords.y < 0 || coords.y >= CHUNK_HEIGHT || coords.z < 0 || coords.z >= CHUNK_WIDTH) {
        assert(true && "Cannot set block out of bonds");
    }
    else {

        blocks[coords.x][coords.y][coords.z] = Block(type);
    }

}

glm::ivec3 Chunk::getChunkCoords() {
    return glm::ivec3(chunkX, 0, chunkZ);
}

glm::vec3 Chunk::getChunkWorldCoords() {
    return glm::ivec3(chunkX * CHUNK_WIDTH, 0, chunkZ * CHUNK_WIDTH);
}

void Chunk::loadChunk(const string filepath) {
    const string filename = filepath + "chunk_" + to_string(chunkX) + "_" + to_string(chunkZ) + ".txt";

    ifstream file(filename, ios::binary);

    if (!file) {
        return;
    }
    file.read(reinterpret_cast<char*>(&generated), sizeof(generated));

    file.read(reinterpret_cast<char*>(&chunkX), sizeof(chunkX));
    file.read(reinterpret_cast<char*>(&chunkZ), sizeof(chunkZ));

    size_t dataSize = CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_WIDTH;

    file.read(reinterpret_cast<char*>(blocks), dataSize * sizeof(Block));

    // Close the file
    file.close();
}

void Chunk::saveChunk(const string filepath) {

    const string filename = filepath + "chunk_" + to_string(chunkX) + "_" + to_string(chunkZ) + ".txt";
    std::ofstream file(filename, ios::binary | ios::out);

    if (!file) {
        return;
    }


    file.write(reinterpret_cast<const char*>(&generated), sizeof(generated));

    file.write(reinterpret_cast<const char*>(&chunkX), sizeof(chunkX));
    file.write(reinterpret_cast<const char*>(&chunkZ), sizeof(chunkZ));

    size_t dataSize = CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_WIDTH;

    file.write(reinterpret_cast<const char*>(blocks), dataSize * sizeof(Block));


    
    file.close();
}