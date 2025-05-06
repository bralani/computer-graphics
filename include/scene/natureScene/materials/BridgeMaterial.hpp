#ifndef BRIDGEMATERIAL_HPP
#define BRIDGEMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class BridgeMaterial : public PBRMaterial
{

  public:
    BridgeMaterial()
        : PBRMaterial(
          Texture ("assets/textures/bridge/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/bridge/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/bridge/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/bridge/normal.png", TextureType::Normal),
          Texture ("assets/textures/bridge/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "BridgeMaterial";
    }
};
    

#endif // BRIDGEMATERIAL_HPP
