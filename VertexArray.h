#pragma once
#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "GameHeaders.h"
#include <vector>

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void bind();
    void unbind();
    void setData(const std::vector<GLfloat>& data, GLuint stride, GLuint offset);
    void setAttributeI(GLuint index, GLint size, GLenum type, GLuint stride, void* offset);
    void setAttribute(GLuint index, GLint size, GLenum type, GLuint stride, void* offset);

private:
    GLuint vao;
    GLuint vbo;
};

#endif // VERTEXARRAY_H