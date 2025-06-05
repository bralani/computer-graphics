#ifndef MULINOMATERIAL_HPP
#define MULINOMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class RuotaMulinoMaterial : public PBRMaterial
{

  public:
    RuotaMulinoMaterial()
        : PBRMaterial(
          Texture ("assets/textures/mulino/ruota_albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/mulino/ruota_roughness.png", TextureType::Roughness),
          Texture ("assets/textures/mulino/ruota_metallic.png", TextureType::Metallic),
          Texture ("assets/textures/mulino/ruota_normal.png", TextureType::Normal),
          Texture ("assets/textures/mulino/ruota_ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "RuotaMulinoMaterial";
    }
};  

#endif // MULINOMATERIAL_HPP
