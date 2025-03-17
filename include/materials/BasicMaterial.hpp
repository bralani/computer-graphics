#ifndef BASICMATERIAL_HPP
#define BASICMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/Material.hpp"

class BasicMaterial : public Material {

public:
    BasicMaterial(const std::vector<Texture>& textures)
        : Material(textures) {}
};

#endif // BASICMATERIAL_HPP