#ifndef TREASUREMATERIAL_HPP
#define TREASUREMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class TreasureMaterial : public PBRMaterial
{

  public:
    TreasureMaterial()
        : PBRMaterial(
          Texture ("assets/textures/treasure/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/treasure/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/treasure/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/treasure/normal.png", TextureType::Normal),
          Texture ("assets/textures/treasure/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "TreasureMaterial";
    }
};
    
class TreasureGoldMaterial : public PBRMaterial
{

  public:
    TreasureGoldMaterial()
        : PBRMaterial(
          Texture ("assets/textures/treasure/albedo_gold.png", TextureType::Diffuse), 
          Texture ("assets/textures/treasure/roughness_gold.png", TextureType::Roughness),
          Texture ("assets/textures/treasure/metallic_gold.png", TextureType::Metallic),
          Texture ("assets/textures/treasure/normal_gold.png", TextureType::Normal),
          Texture ("assets/textures/treasure/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "TreasureGoldMaterial";
    }
};

#endif // TREASUREMATERIAL_HPP
