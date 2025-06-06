#ifndef FABBRO_MATERIAL_HPP
#define FABBRO_MATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class LegnoFabbroMaterial : public PBRMaterial
{

  public:
    LegnoFabbroMaterial()
        : PBRMaterial(
          Texture ("assets/textures/fabbro/legno/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/fabbro/legno/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/fabbro/legno/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/fabbro/legno/normal.png", TextureType::Normal),
          Texture ("assets/textures/fabbro/legno/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "LegnoFabbroMaterial";
    }
};

class ScudiFabbroMaterial : public PBRMaterial
{

  public:
    ScudiFabbroMaterial()
        : PBRMaterial(
          Texture ("assets/textures/fabbro/scudi/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/fabbro/scudi/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/fabbro/scudi/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/fabbro/scudi/normal.png", TextureType::Normal),
          Texture ("assets/textures/fabbro/scudi/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "ScudiFabbroMaterial";
    }
};

class SpadeFabbroMaterial : public PBRMaterial
{

  public:
    SpadeFabbroMaterial()
        : PBRMaterial(
          Texture ("assets/textures/fabbro/spade/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/fabbro/spade/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/fabbro/spade/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/fabbro/spade/normal.png", TextureType::Normal),
          Texture ("assets/textures/fabbro/spade/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "SpadeFabbroMaterial";
    }
};
#endif // FABBRO_MATERIAL_HPP
