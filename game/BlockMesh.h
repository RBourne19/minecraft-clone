#pragma once
#pragma once

#include "Vertex.h"
#include "Block.h"

struct BlockMesh {
    static const std::array<Vertex, 6>& getVerticesFromDirection(const glm::ivec3& vec) {
        assert(glm::abs(vec.x) + glm::abs(vec.y) + glm::abs(vec.z) == 1);

        switch (vec.x) {
        case 1:
            return vertices[1];
        case -1:
            return vertices[2];
        default:
            break;
        }

        switch (vec.y) {
        case 1:
            return vertices[0];
        case -1:
            return vertices[5];
        default:
            break;
        }

        switch (vec.z) {
        case 1:
            return vertices[4];
        case -1:
            return vertices[3];
        default:
            break;
        }

        assert(false);
        return vertices[0];
    }
    static const glm::vec3 offsetByFace(glm::vec3& pos, BLOCK_FACE face) {
        switch (face)
        {
        case TOP:
            return pos + glm::vec3(0, 1, 0);
        case BOTTOM:
            return pos + glm::vec3(0, -1, 0);


        case NORTH:
            return pos + glm::vec3(0, 0, 1);
        case WEST:
            
            return pos + glm::vec3(-1, 0, 0);

        case SOUTH:
            return pos + glm::vec3(0, 0, -1);

        case EAST:
            return pos + glm::vec3(1, 0, 0);

        case NONE:
            return pos;
            
        }
    }
    static const std::array<std::array<Vertex, 6>, 6> vertices;
};