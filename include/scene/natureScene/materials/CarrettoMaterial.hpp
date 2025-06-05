#ifndef CARRETTO_MATERIAL_HPP
#define CARRETTO_MATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class CarrettoMaterial : public PBRMaterial
{

  public:
    CarrettoMaterial()
        : PBRMaterial(
          Texture ("assets/textures/carretto/albedo.jpg", TextureType::Diffuse), 
          Texture ("assets/textures/carretto/roughness.jpg", TextureType::Roughness),
          Texture ("assets/textures/carretto/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/carretto/normal.jpg", TextureType::Normal),
          Texture ("assets/textures/carretto/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "CarrettoMaterial";
    }
};
    

#endif // CARRETTO_MATERIAL_HPP
