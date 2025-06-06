#ifndef FIENILE_MATERIAL_HPP
#define FIENILE_MATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class TettoFienileMaterial : public PBRMaterial
{

  public:
    TettoFienileMaterial()
        : PBRMaterial(
          Texture ("assets/textures/fienile/tetto/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/fienile/tetto/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/fienile/tetto/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/fienile/tetto/normal.png", TextureType::Normal),
          Texture ("assets/textures/fienile/tetto/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "TettoFienileMaterial";
    }
};
    
class PlanksFienileMaterial : public PBRMaterial
{

  public:
    PlanksFienileMaterial()
        : PBRMaterial(
          Texture ("assets/textures/fienile/planks/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/fienile/planks/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/fienile/planks/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/fienile/planks/normal.png", TextureType::Normal),
          Texture ("assets/textures/fienile/planks/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "PlanksFienileMaterial";
    }
};

class BoardsFienileMaterial : public PBRMaterial
{

  public:
    BoardsFienileMaterial()
        : PBRMaterial(
          Texture ("assets/textures/fienile/boards/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/fienile/boards/roughness.png", TextureType::Roughness),
          Texture ("assets/textures/fienile/boards/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/fienile/boards/normal.png", TextureType::Normal),
          Texture ("assets/textures/fienile/boards/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "BoardsFienileMaterial";
    }
};
#endif // FIENILE_MATERIAL_HPP
