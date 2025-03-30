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

        if (diffuseTexture.getType() != TextureType::Diffuse) {
            std::cout << "Error: texture is not a diffuse texture" << std::endl;
            return;
        }

        textures[TextureType::Diffuse] = diffuseTexture;
    }


    std::string getClassName() const override {
        return "BasicMaterial";
    }

};

#endif // BASICMATERIAL_HPP