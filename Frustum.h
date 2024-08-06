#pragma once
#include "GameHeaders.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <iostream>

//Singleton frustum class :)
class Frustum {
public:
    Frustum(const Frustum&) = delete;
    Frustum& operator=(const Frustum&) = delete;

    static Frustum& getInstance() {
        static Frustum instance;
        return instance;
    }

    void update(const glm::mat4& mvpMatrix) {
        planes[0] = glm::vec4(
            mvpMatrix[0][3] + mvpMatrix[0][0],
            mvpMatrix[1][3] + mvpMatrix[1][0],
            mvpMatrix[2][3] + mvpMatrix[2][0],
            mvpMatrix[3][3] + mvpMatrix[3][0]
        );

        planes[1] = glm::vec4(
            mvpMatrix[0][3] - mvpMatrix[0][0],
            mvpMatrix[1][3] - mvpMatrix[1][0],
            mvpMatrix[2][3] - mvpMatrix[2][0],
            mvpMatrix[3][3] - mvpMatrix[3][0]
        );

        planes[2] = glm::vec4(
            mvpMatrix[0][3] + mvpMatrix[0][1],
            mvpMatrix[1][3] + mvpMatrix[1][1],
            mvpMatrix[2][3] + mvpMatrix[2][1],
            mvpMatrix[3][3] + mvpMatrix[3][1]
        );

        planes[3] = glm::vec4(
            mvpMatrix[0][3] - mvpMatrix[0][1],
            mvpMatrix[1][3] - mvpMatrix[1][1],
            mvpMatrix[2][3] - mvpMatrix[2][1],
            mvpMatrix[3][3] - mvpMatrix[3][1]
        );

        planes[4] = glm::vec4(
            mvpMatrix[0][3] + mvpMatrix[0][2],
            mvpMatrix[1][3] + mvpMatrix[1][2],
            mvpMatrix[2][3] + mvpMatrix[2][2],
            mvpMatrix[3][3] + mvpMatrix[3][2]
        );

        planes[5] = glm::vec4(
            mvpMatrix[0][3] - mvpMatrix[0][2],
            mvpMatrix[1][3] - mvpMatrix[1][2],
            mvpMatrix[2][3] - mvpMatrix[2][2],
            mvpMatrix[3][3] - mvpMatrix[3][2]
        );

        for (auto& plane : planes) {
            float length = glm::length(glm::vec3(plane));
            plane /= length;
        }
    }

    bool isBoxInFrustum(const glm::vec3& min, const glm::vec3& max) const {
        for (const auto& plane : planes) {
            glm::vec3 positiveVertex = min;
            if (plane.x >= 0) positiveVertex.x = max.x;
            if (plane.y >= 0) positiveVertex.y = max.y;
            if (plane.z >= 0) positiveVertex.z = max.z;

            if (glm::dot(glm::vec3(plane), positiveVertex) + plane.w < 0) {
                return false;
            }
        }
        return true;
    }

private:
    Frustum() {}

    std::array<glm::vec4, 6> planes;
};