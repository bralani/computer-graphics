#ifndef TendaMATERIAL_HPP
#define TendaMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class TendaMaterial : public PBRMaterial
{

  public:
    TendaMaterial()
        : PBRMaterial(
          Texture ("assets/textures/tenda/albedo.jpg", TextureType::Diffuse), 
          Texture ("assets/textures/tenda/ao.jpg", TextureType::Roughness),
          Texture ("assets/textures/tenda/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/tenda/normal.png", TextureType::Normal),
          Texture ("assets/textures/tenda/ao.jpg", TextureType::AmbientOcclusion)
        )
    {
      setTilingFactor(5);
    }

    std::string getClassName() const override
    {
        return "TendaMaterial";
    }
};

#endif // TendaMATERIAL_HPP
