#ifndef PBRMATERIAL_HPP
#define PBRMATERIAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "materials/Texture.hpp"
#include "materials/Material.hpp"

class PBRMaterial : public Material
{

public:
  PBRMaterial(const std::vector<Texture> &textures)
      : Material(textures) {}

};

#endif // PBRMATERIAL_HPP