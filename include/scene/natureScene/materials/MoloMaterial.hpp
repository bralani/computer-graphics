#ifndef MOLOMATERIAL_HPP
#define MOLOMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class SupportoMoloMaterial : public PBRMaterial
{

  public:
    SupportoMoloMaterial()
        : PBRMaterial(
          Texture ("assets/textures/molo/supporto_albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/molo/supporto_roughness.png", TextureType::Roughness),
          Texture ("assets/textures/molo/supporto_metallic.png", TextureType::Metallic),
          Texture ("assets/textures/molo/supporto_normal.png", TextureType::Normal),
          Texture ("assets/textures/molo/supporto_ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "SupportoMoloMaterial";
    }
};  

class PaliMoloMaterial : public PBRMaterial
{

  public:
    PaliMoloMaterial()
        : PBRMaterial(
          Texture ("assets/textures/molo/pali_albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/molo/pali_roughness.png", TextureType::Roughness),
          Texture ("assets/textures/molo/pali_metallic.png", TextureType::Metallic),
          Texture ("assets/textures/molo/pali_normal.png", TextureType::Normal),
          Texture ("assets/textures/molo/pali_ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "PaliMoloMaterial";
    }
};  


class PasserellaMoloMaterial : public PBRMaterial
{

  public:
    PasserellaMoloMaterial()
        : PBRMaterial(
          Texture ("assets/textures/molo/passerella_albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/molo/passerella_roughness.png", TextureType::Roughness),
          Texture ("assets/textures/molo/passerella_metallic.png", TextureType::Metallic),
          Texture ("assets/textures/molo/passerella_normal.png", TextureType::Normal),
          Texture ("assets/textures/molo/passerella_ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "PasserellaMoloMaterial";
    }
};  

#endif // MOLOMATERIAL_HPP
