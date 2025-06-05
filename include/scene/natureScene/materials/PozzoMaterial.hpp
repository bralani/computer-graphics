#ifndef POZZOMATERIAL_HPP
#define POZZOMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class MurettoPozzoMaterial : public PBRMaterial
{

  public:
    MurettoPozzoMaterial()
        : PBRMaterial(
          Texture ("assets/textures/pozzo/stone_albedo.jpg", TextureType::Diffuse), 
          Texture ("assets/textures/pozzo/roughness.jpg", TextureType::Roughness),
          Texture ("assets/textures/pozzo/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/pozzo/stone_normal.jpg", TextureType::Normal),
          Texture ("assets/textures/pozzo/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "MurettoPozzoMaterial";
    }
};  

#endif // POZZOMATERIAL_HPP
