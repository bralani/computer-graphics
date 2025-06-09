#ifndef HOUSE3MATERIAL_HPP
#define HOUSE3MATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class House3BrickMaterial : public PBRMaterial
{

  public:
    House3BrickMaterial()
        : PBRMaterial(
          Texture ("assets/textures/house3/brick/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/house3/brick/roughness.jpg", TextureType::Roughness),
          Texture ("assets/textures/house3/brick/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/house3/brick/normal.png", TextureType::Normal),
          Texture ("assets/textures/house3/brick/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "House3BrickMaterial";
    }
};  

class House3ConcreteMaterial : public PBRMaterial
{

  public:
    House3ConcreteMaterial()
        : PBRMaterial(
          Texture ("assets/textures/house3/concrete/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/house3/concrete/roughness.jpg", TextureType::Roughness),
          Texture ("assets/textures/house3/concrete/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/house3/concrete/normal.png", TextureType::Normal),
          Texture ("assets/textures/house3/concrete/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "House3ConcreteMaterial";
    }
};  

class House3RoofMaterial : public PBRMaterial
{

  public:
    House3RoofMaterial()
        : PBRMaterial(
          Texture ("assets/textures/house3/roof/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/house3/roof/roughness.jpg", TextureType::Roughness),
          Texture ("assets/textures/house3/roof/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/house3/roof/normal.png", TextureType::Normal),
          Texture ("assets/textures/house3/roof/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "House3RoofMaterial";
    }
};  


class House3RoughWoodMaterial : public PBRMaterial
{

  public:
    House3RoughWoodMaterial()
        : PBRMaterial(
          Texture ("assets/textures/house3/rough_wood/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/house3/rough_wood/roughness.jpg", TextureType::Roughness),
          Texture ("assets/textures/house3/rough_wood/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/house3/rough_wood/normal.png", TextureType::Normal),
          Texture ("assets/textures/house3/rough_wood/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "House3RoughWoodMaterial";
    }
};  
class House3SandstoneMaterial : public PBRMaterial
{

  public:
    House3SandstoneMaterial()
        : PBRMaterial(
          Texture ("assets/textures/house3/sandstone/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/house3/sandstone/roughness.jpg", TextureType::Roughness),
          Texture ("assets/textures/house3/sandstone/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/house3/sandstone/normal.png", TextureType::Normal),
          Texture ("assets/textures/house3/sandstone/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "House3SandstoneMaterial";
    }
};  
class House3PlanksMaterial : public PBRMaterial
{

  public:
    House3PlanksMaterial()
        : PBRMaterial(
          Texture ("assets/textures/house3/planks/albedo.png", TextureType::Diffuse), 
          Texture ("assets/textures/house3/planks/roughness.jpg", TextureType::Roughness),
          Texture ("assets/textures/house3/planks/metallic.png", TextureType::Metallic),
          Texture ("assets/textures/house3/planks/normal.png", TextureType::Normal),
          Texture ("assets/textures/house3/planks/ao.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "House3PlanksMaterial";
    }
};  

#endif // HOUSE3MATERIAL_HPP
