#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <map>
#include <iostream>
#include "materials/Texture.hpp"

class Material {
protected:
    std::map<TextureType, Texture> textures;
    int tilingFactor = 1;
    float opacity = 1.0f;

public:
    Material(const std::map<TextureType, Texture>& textures)
        : textures(textures) {}

    Material() = default;
    virtual ~Material() = default;

    Texture* getTexture(TextureType type) {
        auto it = textures.find(type);
        return (it != textures.end()) ? &it->second : nullptr;
    }

    int getTilingFactor() const {
        return tilingFactor;
    }

    void setTilingFactor(int factor) {
        tilingFactor = factor;
    }

    float getOpacity() const {
        return opacity;
    }

    void setOpacity(float newOpacity) {
        opacity = newOpacity;
    }

    virtual std::string getClassName() const {
        return "Material";
    }

};

#endif // MATERIAL_HPP