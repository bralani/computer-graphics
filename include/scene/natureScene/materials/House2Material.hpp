#ifndef HOUSE2MATERIAL_HPP
#define HOUSE2MATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class House2Material : public PBRMaterial
{

  public:
    House2Material()
        : PBRMaterial(
          Texture ("assets/textures/house2/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/house2/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/house2/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/house2/normal.png", TextureType::Normal),
          Texture ("assets/textures/house2/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "House2Material";
    }
};  

#endif // HOUSE2MATERIAL_HPP
