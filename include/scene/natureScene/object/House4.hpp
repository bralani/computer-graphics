#ifndef HOUSE34BJECT_HPP
#define HOUSE34BJECT_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/House4.hpp"

class House4 : public Object
{
public:
  House4() : Object()
  {

    
std::vector<glm::vec3> positions = {
    { 158.0442f, -6.5151f, -25.3784f },
    { 146.5941f, -5.2898f, -27.8506f },
    { -42.8246f, -6.9549f, 131.9616f },
    { -30.5877f, -6.8743f, 136.8107f },
    { -33.8814f, -6.8843f, 150.1176f },
    { -46.0775f, -6.9549f, 143.7081f },
    { 43.7821f, -8.8844f, 173.2490f }
};

std::vector<glm::vec3> rotations = {
    { -0.0000f, 79.1518f, 0.0000f },
    { -0.0000f, 79.1518f, 0.0000f },
    { -0.0000f, 165.0127f, 0.0000f },
    { -0.0000f, 75.5131f, 0.0000f },
    { -0.0000f, 75.5131f, 0.0000f },
    { -0.0000f, 165.0127f, 0.0000f },
    { -0.0000f, -12.2543f, 0.0000f }
};

std::vector<glm::vec3> scales = {
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f }
};


    auto meshes = std::vector<std::shared_ptr<Mesh>>();

    for (size_t i = 0; i < positions.size(); ++i)
    {
      auto house = std::make_shared<House4Mesh>();
      house->transform.setPosition(positions[i]);
      house->transform.setRotation(rotations[i]);
      house->transform.setScale(scales[i]);
      meshes.push_back(house);
    }

    this->setMeshes(meshes);
  }
};

#endif // HOUSE4OBJECT_HPP