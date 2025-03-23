#ifndef ROCKMATERIAL_HPP
#define ROCKMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class RockMaterial : public PBRMaterial
{

  public:
    RockMaterial()
        : PBRMaterial(
          Texture ("assets/textures/rock/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/rock/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/rock/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/rock/normal.png", TextureType::Normal),
          Texture ("assets/textures/rock/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }
};
    

#endif // ROCKMATERIAL_HPP
