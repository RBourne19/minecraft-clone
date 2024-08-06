#pragma once
#ifndef VERTARRAY_H
#define VERTARRAY_H
#include "GameHeaders.h"



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

#endif // VERTARRAY_H