#include "VertexArray.h"
#include "GameHeaders.h"

VertexArray::VertexArray() {
    // Generate and bind the Vertex Array Object (VAO)
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Unbind the VAO and VBO to avoid accidental modification
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

VertexArray::~VertexArray() {
    // Clean up the VBO and VAO
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void VertexArray::bind() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexArray::setData(const std::vector<GLfloat>& data, GLuint stride, GLuint offset) {
    bind(); // Ensure VAO and VBO are bound
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
    unbind(); // Unbind VAO and VBO
}

void VertexArray::setAttribute(GLuint index, GLint size, GLenum type, GLuint stride, void* offset) {
    bind(); // Ensure VAO and VBO are bound
    glVertexAttribPointer(index, size, type, false,  stride, offset);
    glEnableVertexAttribArray(index);
    unbind(); // Unbind VAO and VBO
}

void VertexArray::setAttributeI(GLuint index, GLint size, GLenum type, GLuint stride, void* offset) {
    bind(); // Ensure VAO and VBO are bound
    glVertexAttribIPointer(index, size, type, stride, offset);
    glEnableVertexAttribArray(index);
    unbind(); // Unbind VAO and VBO
}