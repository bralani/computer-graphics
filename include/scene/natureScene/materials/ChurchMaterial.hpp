#ifndef CHURCHMATERIAL_HPP
#define CHURCHMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class ChurchMaterial : public PBRMaterial
{

  public:
    ChurchMaterial()
        : PBRMaterial(
          Texture ("assets/textures/church/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/church/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/church/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/church/normal.png", TextureType::Normal),
          Texture ("assets/textures/church/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "ChurchMaterial";
    }
};  

#endif // CHURCHMATERIAL_HPP
