#ifndef WALLMATERIAL_HPP
#define WALLMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class WallMaterial : public PBRMaterial
{

  public:
    WallMaterial()
        : PBRMaterial(
          Texture ("assets/textures/walls/albedo.jpg", TextureType::Diffuse), 
          Texture ("assets/textures/walls/roughness.jpg", TextureType::Roughness),
          Texture ("assets/textures/walls/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/walls/normal.png", TextureType::Normal),
          Texture ("assets/textures/walls/ao.jpg", TextureType::AmbientOcclusion)
        )
    {
      this->setTilingFactor(20);
    }

    std::string getClassName() const override
    {
        return "WallMaterial";
    }
};

#endif // WALLMATERIAL_HPP
