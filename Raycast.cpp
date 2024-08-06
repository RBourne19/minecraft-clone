#include "Raycast.h"

Raycast::Raycast(glm::vec3 position, glm::vec2 angles, GLfloat stepDistance, GLfloat maxDepth) : origin(position), angles(angles), stepDistance(stepDistance), maxDepth(maxDepth) {};


std::tuple<glm::vec3, BLOCK_FACE> Raycast::raycastBlock(World& world) {
	float yawRad = angles.x * (M_PI / 180.0f);
	float pitchRad = angles.y * (M_PI / 180.0f);
	float length = 0;
	glm::fvec3 step = glm::fvec3(cos(pitchRad) * cos(yawRad), sin(pitchRad), sin(yawRad) * cos(pitchRad));

	glm::fvec3 ray = glm::fvec3(origin);

	while (length <= maxDepth) {

		const Block* b = world.getBlockByCoords(ray);

		if (b && b->type != AIR) {
			glm::vec3 blockPos = glm::vec3(floor(ray));
			glm::vec3 localPoint = ray - blockPos;
			BLOCK_FACE face = NONE;
			if (floor(ray.x - (step.x * stepDistance)) != blockPos.x) {
				if (ray.x - blockPos.x > .5f) {
					face = EAST;
				}
				else {
					face = WEST;
				}
				
			}
			else if (floor(ray.y - (step.y * stepDistance)) != blockPos.y) {
				if (ray.y - blockPos.y > .5f) {
					face = TOP;
				}
				else {
					face = BOTTOM;
				}
			}
			else if (floor(ray.z - (step.z * stepDistance)) != blockPos.z) {
				if (ray.z - blockPos.z > .5f) {
					face = NORTH;
				}
				else {
					face = SOUTH;
				}
			}
			return std::tuple<glm::vec3, BLOCK_FACE>(blockPos, face);

		}
		else {
			ray += (step * stepDistance);
			length += stepDistance;
		}
	}
	return std::tuple<glm::vec3, BLOCK_FACE>(glm::vec3(-1), NONE);

}