#pragma once
#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <unordered_map>
#include <string>
#include <memory>
#include "Shader.h"
#include "Texture.h"

class AssetManager {
public:
    static AssetManager& getInstance();

    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

    // Method to load and add a shader to the hashmap
    void loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
    std::shared_ptr<Shader> getShader(const std::string& name) const;

    void loadTexture(const std::string& name, const std::string& filename);
    std::shared_ptr<Texture> getTexture(const std::string& name) const;
private:
    AssetManager() = default;

    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures;

};

#endif // ASSET_MANAGER_H