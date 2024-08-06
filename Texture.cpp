#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include "Texture.h"

using namespace std;

Texture::Texture(const string& f) : filename(f) {
    unsigned char* data = stbi_load(filename.c_str(), &atlasWidth, &atlasHeight, &nrChannels, 0);
    if (data) {
        glGenTextures(1, &textureAtlas);

        glBindTexture(GL_TEXTURE_2D, textureAtlas);


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, atlasWidth, atlasHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlasWidth, atlasHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        }

        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else {
        printf("Failed to load texture atlas\n");
    }
};

void Texture::bindTexture() {
    glBindTexture(GL_TEXTURE_2D, textureAtlas);
}