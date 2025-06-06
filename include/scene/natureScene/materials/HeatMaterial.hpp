#ifndef HEATMATERIAL_HPP
#define HEATMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class HeatMaterial : public PBRMaterial
{

  public:
    HeatMaterial()
        : PBRMaterial(
          Texture ("assets/textures/heat/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/heat/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/heat/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/heat/normal.png", TextureType::Normal),
          Texture ("assets/textures/heat/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "HeatMaterial";
    }
};
    

#endif // HEATMATERIAL_HPP
