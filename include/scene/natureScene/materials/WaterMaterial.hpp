#ifndef WATERMATERIAL_HPP
#define WATERMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class WaterMaterial : public PBRMaterial
{

  public:
    WaterMaterial()
        : PBRMaterial(
          Texture ("assets/textures/water/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/water/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/water/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/water/normal.png", TextureType::Normal),
          Texture ("assets/textures/water/ao.png", TextureType::AmbientOcclusion)
        )
    {
        this->setTilingFactor(150);
        this->setOpacity(0.7f);
    }

    std::string getClassName() const override
    {
        return "WaterMaterial";
    }
};
    

#endif // WATERMATERIAL_HPP
