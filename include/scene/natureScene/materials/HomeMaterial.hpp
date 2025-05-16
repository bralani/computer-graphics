#ifndef HOMEMATERIAL_HPP
#define HOMEMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class HomeMaterial : public PBRMaterial
{

  public:
    HomeMaterial()
        : PBRMaterial(
          Texture ("assets/textures/home/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/home/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/home/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/home/normal.png", TextureType::Normal),
          Texture ("assets/textures/home/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "HomeMaterial";
    }
};
    

#endif // HOMEMATERIAL_HPP
