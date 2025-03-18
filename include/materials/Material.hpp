#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <map>
#include <iostream>
#include "materials/Texture.hpp"

class Material {
protected:
    std::map<TextureType, Texture> textures;

public:
    Material(const std::map<TextureType, Texture>& textures)
        : textures(textures) {}

    Material() = default;
    virtual ~Material() = default;

    Texture* getTexture(TextureType type) {
        auto it = textures.find(type);
        return (it != textures.end()) ? &it->second : nullptr;
    }

};

#endif // MATERIAL_HPP