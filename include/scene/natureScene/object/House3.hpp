#ifndef HOUSE3OBJECT_HPP
#define HOUSE3OBJECT_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/House3.hpp"

class House3 : public Object
{
public:
  House3() : Object()
  {

    
std::vector<glm::vec3> positions = {
    { -60.5993f, -7.7171f, 129.3690f },
    { 148.7292f, -10.3683f, 158.0770f },
    { 175.8382f, -10.7267f, 1.2079f },
    { 150.7684f, -8.5449f, -4.4048f },
    { 63.0775f, -9.5214f, 182.3867f }
};

std::vector<glm::vec3> rotations = {
    { 0.0000f, -122.0000f, 0.0000f },
    { 0.0000f, -85.0000f, 0.0000f },
    { 0.0000f, 42.0000f, 0.0000f },
    { 0.0000f, 151.0000f, 0.0000f },
    { 0.0000f, -32.0000f, 0.0000f }
};

std::vector<glm::vec3> scales = {
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f }
};


    auto meshes = std::vector<std::shared_ptr<Mesh>>();

    for (size_t i = 0; i < positions.size(); ++i)
    {
      auto house = std::make_shared<House3Mesh>();
      house->transform.setPosition(positions[i]);
      house->transform.setRotation(rotations[i]);
      house->transform.setScale(scales[i]);
      meshes.push_back(house);
    }

    this->setMeshes(meshes);
  }
};

#endif // HOUSE3OBJECT_HPP