#ifndef SANDMATERIAL_HPP
#define SANDMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class SandMaterial : public PBRMaterial
{

  public:
    SandMaterial()
        : PBRMaterial(
          Texture ("assets/textures/sand/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/sand/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/sand/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/sand/normal.png", TextureType::Normal),
          Texture ("assets/textures/sand/ao.png", TextureType::AmbientOcclusion)
        )
    {
        this->setTilingFactor(2);
    }

    std::string getClassName() const override
    {
        return "SandMaterial";
    }
};
    

#endif // SANDMATERIAL_HPP
