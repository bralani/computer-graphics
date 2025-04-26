#ifndef TREEMATERIAL_HPP
#define TREEMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/PBRMaterial.hpp"

class TreeWoodMaterial : public PBRMaterial
{

  public:
    TreeWoodMaterial()
        : PBRMaterial(
          Texture ("assets/textures/tree/albedo_wood.png", TextureType::Diffuse), 
          Texture ("assets/textures/tree/roughness_wood.png", TextureType::Roughness),
          Texture ("assets/textures/tree/metallic_wood.png", TextureType::Metallic),
          Texture ("assets/textures/tree/normal_wood.png", TextureType::Normal),
          Texture ("assets/textures/tree/ao_wood.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "TreeWoodMaterial";
    }
};


class TreeLeavesMaterial : public PBRMaterial
{

  public:
    TreeLeavesMaterial()
        : PBRMaterial(
          Texture ("assets/textures/tree/albedo_leaves.png", TextureType::Diffuse), 
          Texture ("assets/textures/tree/roughness_leaves.png", TextureType::Roughness),
          Texture ("assets/textures/tree/metallic_leaves.png", TextureType::Metallic),
          Texture ("assets/textures/tree/normal_leaves.png", TextureType::Normal),
          Texture ("assets/textures/tree/ao_leaves.png", TextureType::AmbientOcclusion)
        )
    {
    }

    std::string getClassName() const override
    {
        return "TreeLeavesMaterial";
    }
};
    

#endif // TREEMATERIAL_HPP
