#ifndef PBRMATERIAL_HPP
#define PBRMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/Material.hpp"

class PBRMaterial : public Material
{

public:
  PBRMaterial(Texture diffuseTexture, Texture roughnessTexture, Texture metallicTexture)
  {

    if (diffuseTexture.getType() != TextureType::Diffuse) {
        std::cout << "Error: texture is not a diffuse texture" << std::endl;
        return;
    }

    textures[TextureType::Diffuse] = diffuseTexture;

    if (roughnessTexture.getType() != TextureType::Roughness) {
        std::cout << "Error: texture is not a roughness texture" << std::endl;
        return;
    }

    textures[TextureType::Roughness] = roughnessTexture;

    if (metallicTexture.getType() != TextureType::Metallic) {
        std::cout << "Error: texture is not a metallic texture" << std::endl;
        return;
    }

    textures[TextureType::Metallic] = metallicTexture;
  }

};

#endif // PBRMATERIAL_HPP