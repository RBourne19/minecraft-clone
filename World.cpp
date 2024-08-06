#include "World.h"
#include "AssetManager.h"
#include "Frustum.h"
#include <algorithm> 
#include <thread>
#include <future>

using namespace std;

World::World(int seed) : seed(seed) {
	noise.SetSeed(seed);
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	

}

void World::init(Player& player) {
	va = new VertexArray();
	va->setAttributeI(0, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void*)offsetof(Vertex, data));

	int ySpawn =  2 * noise.GetNoise(-0.5f, -0.5f);
	ySpawn = (ySpawn + 1) * 0.5f * (CHUNK_HEIGHT - 1);
	ySpawn = fmax(0, fmin(CHUNK_HEIGHT - 1, ySpawn));
	player.setPosition(glm::fvec3(0, floor(ySpawn), 0));
}

void World::addToBlockBuffer(glm::ivec3 coord, Block b) {
	blockBuffer.emplace_back(coord, b);
}

void World::clearBlockBuffer() {

	//reduces unneccessary reads and saves of chunks
	unordered_map< tuple<int, int>, Chunk*, ChunkHash, ChunkEqual> tempChunkMap;


	for (const auto& bt : blockBuffer) {
		const auto& pos = std::get<0>(bt);
		const auto& block = std::get<1>(bt);
		
		Chunk* c = getChunkByCoords(glm::ivec2(pos.x, pos.z));
		glm::ivec3 blockCoords = glm::ivec3(pos.x, pos.y, pos.z);
		
		blockCoords.x = blockCoords.x % CHUNK_WIDTH;
		blockCoords.z = blockCoords.z % CHUNK_WIDTH;
		blockCoords.x = (blockCoords.x < 0) ? blockCoords.x + CHUNK_WIDTH : blockCoords.x;
		blockCoords.z = (blockCoords.z < 0) ? blockCoords.z + CHUNK_WIDTH : blockCoords.z;


		if (c) {
			
			//maybe switch set block to account for this math????
			c->setBlock(blockCoords, block.type);
		}
		else {
			int chunkX = pos.x >= 0 ? pos.x / CHUNK_WIDTH : ((pos.x + 1) / CHUNK_WIDTH) - 1;
			int chunkZ = pos.z >= 0 ? pos.z / CHUNK_WIDTH : ((pos.z + 1) / CHUNK_WIDTH) - 1;
			auto it = tempChunkMap.find(make_tuple(chunkX, chunkZ));
			if (it == tempChunkMap.end()) {
				Chunk* s = new Chunk(chunkX, chunkZ);
				tempChunkMap[make_tuple(chunkX, chunkZ)] =  s;
				s->loadChunk("./chunks/");
				s->setBlock(blockCoords, block.type);
			}
			else {
				it->second->setBlock(blockCoords, block.type);
			}
		}
	}
	//save tempmap
	for (const auto& entry : tempChunkMap) {
		Chunk* chunk = entry.second;
		chunk->saveChunk("./chunks/");
	}

	blockBuffer.clear();
}

//this very much needs to be reorganized bobert
//fix by splitting into things that need to be updated vs things that need to be built/rendered
void World::render(Player& player, glm::mat4& mvp) {
	va->bind();

	AssetManager::getInstance().getTexture("default")->bindTexture();


	int chunkX = floor(player.pos.x);
	int chunkZ = floor(player.pos.z);
	chunkX = chunkX >= 0 ? chunkX / CHUNK_WIDTH : ((chunkX + 1) / CHUNK_WIDTH) - 1;
	chunkZ = chunkZ >= 0 ? chunkZ / CHUNK_WIDTH : ((chunkZ + 1) / CHUNK_WIDTH) - 1;
	if (chunkX != player.chunkCoord.x || chunkZ != player.chunkCoord.y) {

		glm::ivec2 newChunkCoord = glm::ivec2(chunkX, chunkZ);
		glm::ivec2 offset = newChunkCoord - player.chunkCoord;
		updateChunkMap(newChunkCoord);
		player.chunkCoord = newChunkCoord;
	}



	if (blockBuffer.size() != 0) {
		clearBlockBuffer();
	}

	vector<future<void>> futures;
	for (const auto &entry : chunkMap) {
		Chunk* chunk = entry.second;
		if (!Frustum::getInstance().isBoxInFrustum(chunk->getChunkWorldCoords(), chunk->getChunkWorldCoords() + glm::vec3(CHUNK_WIDTH, CHUNK_HEIGHT, CHUNK_WIDTH))) continue;

		futures.emplace_back(async(launch::async, &Chunk::generateMesh, chunk, ref(*this), ref(player)));
	}

	for (auto& future : futures) {
		future.get();
	}

	tuple<int, int> playerChunk = make_tuple(chunkX, chunkZ);
	vector<Chunk*> sortedChunks = sortChunksByDistance(chunkMap, playerChunk);


	for (Chunk* chunk : sortedChunks) {
		if (!Frustum::getInstance().isBoxInFrustum(chunk->getChunkWorldCoords(), chunk->getChunkWorldCoords() + glm::vec3(CHUNK_WIDTH, CHUNK_HEIGHT, CHUNK_WIDTH))) continue;
		chunk->renderOpaque(mvp);
		chunk->renderTransparent(mvp);
	}

	//could be own function
	if (player.focusFace == NONE) return;
	shared_ptr<Shader> outlineShader = AssetManager::getInstance().getShader("outline");

	outlineShader->use();

	vector<Vertex> outlineVertices;
	outlineVertices.resize(6 * 6);
	outlineShader->setMat4("MVP", glm::translate(mvp, player.focusPos));

	int32_t vertexCount = 0;
	for (const auto& face : BlockMesh::vertices) {
		for (const auto& vertex : face) {
			outlineVertices.at(vertexCount) = vertex;
			vertexCount++;
		}
	}

	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), outlineVertices.data(), GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	va->unbind();

}

Chunk* World::getChunkByCoords(const glm::ivec2& chunkCoords) {
	//fix this, from old project
	int blockX = floor(chunkCoords.x);
	int blockZ = floor(chunkCoords.y);
	int chunkX = blockX >= 0 ? chunkCoords.x / CHUNK_WIDTH : ((blockX + 1) / CHUNK_WIDTH) - 1;
	int chunkZ = blockZ >= 0 ? chunkCoords.y / CHUNK_WIDTH : ((blockZ + 1) / CHUNK_WIDTH) - 1;
	auto it = this->chunkMap.find(make_tuple(chunkX, chunkZ));
	if (it != this->chunkMap.end()) {
		return it->second;
	}
	return nullptr;
}

Block* World::getBlockByCoords(const glm::fvec3& coords) {
	glm::ivec3 blockCoords = glm::ivec3(floor(coords.x), floor(coords.y), floor(coords.z));
	
	if (blockCoords.y < 0 || blockCoords.y >= CHUNK_HEIGHT) {
		return nullptr;
	}
	Chunk* currChunk = getChunkByCoords(glm::ivec2(blockCoords.x, blockCoords.z));
	if (currChunk) {
		//make this conversion a function itself bobert
		blockCoords.x = blockCoords.x % CHUNK_WIDTH;
		blockCoords.z = blockCoords.z % CHUNK_WIDTH;
		blockCoords.x = (blockCoords.x < 0) ? blockCoords.x + CHUNK_WIDTH : blockCoords.x;
		blockCoords.z = (blockCoords.z < 0) ? blockCoords.z + CHUNK_WIDTH : blockCoords.z;
		return currChunk->getBlockAt(blockCoords, *this);
	}
	else {
		return nullptr;
	}

}

void World::setBlockByCoords(const glm::vec3& coords, BLOCK_TYPE type) {
	glm::ivec3 blockCoords = glm::ivec3(floor(coords.x), floor(coords.y), floor(coords.z));
	Chunk* currChunk = this->getChunkByCoords(glm::ivec2(blockCoords.x, blockCoords.z));
	
	if (currChunk) {
		blockCoords.x = blockCoords.x % CHUNK_WIDTH;
		blockCoords.z = blockCoords.z % CHUNK_WIDTH;
		blockCoords.x = (blockCoords.x < 0) ? blockCoords.x + CHUNK_WIDTH : blockCoords.x;
		blockCoords.z = (blockCoords.z < 0) ? blockCoords.z + CHUNK_WIDTH : blockCoords.z;
		currChunk->setBlock(blockCoords, type);
	}
	
}

double squaredDistance(const tuple<int, int>& a, const tuple<int, int>& b) {
	int dx = get<0>(a) - get<0>(b);
	int dy = get<1>(a) - get<1>(b);
	return dx * dx + dy * dy;
}


vector<Chunk*> World::sortChunksByDistance(
	const unordered_map<tuple<int, int>, Chunk*, ChunkHash, ChunkEqual>& chunkMap,
	const tuple<int, int>& referencePoint) {

	vector<tuple<int, int>> keys;
	for (const auto& pair : chunkMap) {
		keys.push_back(pair.first);
	}

	sort(keys.begin(), keys.end(), [&](const tuple<int, int>& a, const tuple<int, int>& b) {
		return squaredDistance(a, referencePoint) > squaredDistance(b, referencePoint);
		});

	vector<Chunk*> sortedChunks;
	for (const auto& key : keys) {
		sortedChunks.push_back(chunkMap.at(key));
	}

	return sortedChunks;
}

void World::updateChunkMap(glm::ivec2& newCenter) {

	for (int x = newCenter.x - RENDER_DISTANCE; x <= newCenter.x + RENDER_DISTANCE; x++)
	{
		for (int z = newCenter.y - RENDER_DISTANCE; z <= newCenter.y + RENDER_DISTANCE; z++)
		{

			tuple<int, int> coord = make_tuple(x, z);
			if (pow(get<0>(coord) - newCenter.x, 2) + pow(get<1>(coord) - newCenter.y, 2) > pow(RENDER_DISTANCE, 2)) continue;
			auto c = chunkMap.find(coord);
			if (c == chunkMap.end()) {
				Chunk* s = new Chunk(x, z);
				s->loadChunk("./chunks/");
				if (!s->generated) {
					s->generateTerrain(noise, (*this));
				}
				chunkMap[coord] = s;
			}

		}
		
	}

	

	for (const auto& entry : chunkMap) {
		Chunk* chunk = entry.second;
		glm::ivec3 chunkCoords = chunk->getChunkCoords();
		if (pow(chunkCoords.x - newCenter.x, 2) + pow(chunkCoords.z - newCenter.y, 2) > pow(RENDER_DISTANCE, 2)) {
			entry.second->saveChunk("./chunks/");
			chunkMap.erase(entry.first);

			delete entry.second;
		}
	}
	chunkMap.rehash(0);
}

