#include "AssetManager.h"
#include <iostream> 

AssetManager& AssetManager::getInstance() {
    static AssetManager instance;
    return instance;
}

// Method to load and add a shader to the hashmap
void AssetManager::loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) {
    std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexPath, fragmentPath);

    shaders[name] = shader;

    std::cout << "Shader " << name << " loaded.\n"; 
}

std::shared_ptr<Shader> AssetManager::getShader(const std::string& name) const {
    auto it = shaders.find(name);
    if (it != shaders.end()) {
        return it->second;
    }
    std::cout << "Shader " << name << " not found.\n"; 
    return nullptr;
}

void AssetManager::loadTexture(const std::string& name, const std::string& filename) {
    std::shared_ptr<Texture> texture = std::make_shared<Texture>(filename);

    textures[name] = texture;

    std::cout << "Texture " << name << " loaded.\n";
}

std::shared_ptr<Texture> AssetManager::getTexture(const std::string& name) const {
    auto it = textures.find(name);
    if (it != textures.end()) {
        return it->second;
    }
    std::cout << "Texture " << name << " not found.\n";
    return nullptr;
}