#ifndef TORCHMATERIAL_HPP
#define TORCHMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class TorchMaterial : public PBRMaterial
{

  public:
    TorchMaterial()
        : PBRMaterial(
          Texture ("assets/textures/torch/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/torch/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/torch/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/torch/normal.png", TextureType::Normal),
          Texture ("assets/textures/torch/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "TorchMaterial";
    }
};
    

#endif // TORCHMATERIAL_HPP
