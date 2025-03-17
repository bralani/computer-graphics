#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"

class Material {
protected:
    std::vector<Texture> textures;

public:
    Material(const std::vector<Texture>& textures)
        : textures(textures) {}
    Material() = default;
    virtual ~Material() = default;
    
    std::vector<Texture> getTextures() const { return textures; }
};

#endif // MATERIAL_HPP