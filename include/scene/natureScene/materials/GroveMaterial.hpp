#ifndef GROVEMATERIAL_HPP
#define GROVEMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class GroveMaterial : public PBRMaterial
{

  public:
    GroveMaterial()
        : PBRMaterial(
          Texture ("assets/textures/grove/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/grove/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/grove/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/grove/normal.png", TextureType::Normal),
          Texture ("assets/textures/grove/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "GroveMaterial";
    }
};
    

#endif // GROVEMATERIAL_HPP
