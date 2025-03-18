#ifndef BASICMATERIAL_HPP
#define BASICMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/Material.hpp"

class BasicMaterial : public Material {

public:
    BasicMaterial(Texture diffuseTexture) {
        textures.push_back(diffuseTexture);
    }

};

#endif // BASICMATERIAL_HPP