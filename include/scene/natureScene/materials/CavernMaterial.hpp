#ifndef CAVERNMATERIAL_HPP
#define CAVERNMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class CavernMaterial : public PBRMaterial
{

  public:
    CavernMaterial()
        : PBRMaterial(
          Texture ("assets/textures/cavern/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/cavern/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/cavern/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/cavern/normal.png", TextureType::Normal),
          Texture ("assets/textures/cavern/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "CavernMaterial";
    }
};
    

#endif // CAVERNMATERIAL_HPP
