#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include <GLFW/glfw3.h>


class Texture {

public:



    std::string filename;
    GLuint textureAtlas;
    int atlasWidth, atlasHeight, nrChannels;

    explicit Texture(const std::string& filename);

    void bindTexture();

};
#endif

