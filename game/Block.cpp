#include "Block.h"

#include "Texture.h"
GLfloat vertices[] = {
    0.0f, 0.0f, 1.0f,   // Vertex 0
    1.0f, 0.0f, 1.0f,   // Vertex 1
    1.0f, 1.0f, 1.0f,   // Vertex 2
    0.0f, 1.0f, 1.0f,   // Vertex 3

    // Back face
    0.0f, 0.0f, 0.0f,   // Vertex 4
    1.0f, 0.0f, 0.0f,   // Vertex 5
    1.0f, 1.0f, 0.0f,   // Vertex 6
    0.0f, 1.0f, 0.0f,   // Vertex 7

    // Left face
    0.0f, 0.0f, 0.0f,   // Vertex 8
    0.0f, 1.0f, 0.0f,   // Vertex 9
    0.0f, 1.0f, 1.0f,   // Vertex 10
    0.0f, 0.0f, 1.0f,   // Vertex 11

    // Right face
    1.0f, 0.0f, 0.0f,   // Vertex 12
    1.0f, 0.0f, 1.0f,   // Vertex 13
    1.0f, 1.0f, 1.0f,   // Vertex 14
    1.0f, 1.0f, 0.0f,   // Vertex 15

    // Top face
    0.0f, 1.0f, 1.0f,   // Vertex 16
    1.0f, 1.0f, 1.0f,   // Vertex 17
    1.0f, 1.0f, 0.0f,   // Vertex 18
    0.0f, 1.0f, 0.0f,   // Vertex 19

    // Bottom face
    0.0f, 0.0f, 0.0f,   // Vertex 20
    1.0f, 0.0f, 0.0f,   // Vertex 21
    1.0f, 0.0f, 1.0f,   // Vertex 22
    0.0f, 0.0f, 1.0f    // Vertex 23
};

GLubyte indices[] = {
    0,  1,  2,  3,    // Front face
    4,  5,  6,  7,    // Back face
    8,  9, 10, 11,    // Left face
    12, 13, 14, 15,   // Right face
    16, 17, 18, 19,   // Top face
    20, 21, 22, 23    // Bottom face
};




Block::Block(BLOCK_TYPE type) : type(type) {};
Block::Block() : type(AIR) {};
 


void updateBlockTextures() {
    
}