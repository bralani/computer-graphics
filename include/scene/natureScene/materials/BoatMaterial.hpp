#ifndef BOATMATERIAL_HPP
#define BOATMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class BoatMaterial : public PBRMaterial
{

  public:
    BoatMaterial()
        : PBRMaterial(
          Texture ("assets/textures/boat/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/boat/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/boat/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/boat/normal.png", TextureType::Normal),
          Texture ("assets/textures/boat/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "BoatMaterial";
    }
};
    

#endif // BOATMATERIAL_HPP
