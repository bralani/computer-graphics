#ifndef GROUNDMATERIAL_HPP
#define GROUNDMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class GroundMaterial : public PBRMaterial
{

  public:
    GroundMaterial()
        : PBRMaterial(
          Texture ("assets/textures/ground/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/ground/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/ground/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/ground/normal.png", TextureType::Normal),
          Texture ("assets/textures/ground/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "GroundMaterial";
    }
};

class GroundCollisionMaterial : public PBRMaterial
{

  public:
    GroundCollisionMaterial()
        : PBRMaterial(
          Texture ("assets/textures/cavern/ao.png", TextureType::Diffuse), 
          Texture ("assets/textures/cavern/ao.png", TextureType::Roughness),
          Texture ("assets/textures/cavern/ao.png", TextureType::Metallic),
          Texture ("assets/textures/cavern/ao.png", TextureType::Normal),
          Texture ("assets/textures/cavern/ao.png", TextureType::AmbientOcclusion)
        )
    {
      this->setOpacity(0.0f);
    }

    std::string getClassName() const override
    {
        return "GroundCollisionMaterial";
    }
}; 

#endif // GROUNDMATERIAL_HPP
