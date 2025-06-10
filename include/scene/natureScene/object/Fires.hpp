#ifndef FIREOBJECT_HPP
#define FIREOBJECT_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Fire.hpp"

class Fires : public Object
{
public:
  Fires() : Object()
  {

std::vector<glm::vec3> positions = {
    { -32.0654f, -6.6896f, 124.3616f },
    { 73.5852f, -5.5483f, -36.8194f },
    { 132.3955f, -6.2044f, -2.4577f }
};

std::vector<glm::vec3> rotations = {
    { 45.5377f, 158.4668f, 0.0000f },
    { 44.0075f, 158.4338f, -1.3683f },
    { 45.5377f, 158.4668f, 0.0000f }
};

std::vector<glm::vec3> scales = {
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f }
};


    auto meshes = std::vector<std::shared_ptr<Mesh>>();

    for (size_t i = 0; i < positions.size(); ++i)
    {
      auto rock = std::make_shared<FireRockMesh>();
      rock->transform.setPosition(positions[i]);
      rock->transform.setRotation(rotations[i]);
      rock->transform.setScale(scales[i]);
      meshes.push_back(rock);

      auto wood = std::make_shared<FireWoodMesh>();
      wood->transform.setPosition(positions[i]);
      wood->transform.setRotation(rotations[i]);
      wood->transform.setScale(scales[i]);
      meshes.push_back(wood);
    }

    this->setMeshes(meshes);
  }

};

#endif // FIREOBJECT_HPP