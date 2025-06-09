#ifndef HOUSE2OBJECT_HPP
#define HOUSE2OBJECT_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/House2.hpp"

class House2 : public Object
{
public:
  House2() : Object()
  {

    std::vector<glm::vec3> positions = {
        {-35.9208f, -3.3242f, 11.2253f},
        {89.7363f, -4.7743f, 13.6093f},
        {122.2259f, -8.5021f, 158.2428f},
        {-119.0962f, -10.8344f, 88.9770f},
        {-102.9858f, -8.8518f, 109.5047f},
        {95.1671f, -6.9342f, 198.3516f}};

    std::vector<glm::vec3> rotations = {
        {0.0000f, -15.6874f, 0.0000f},
        {0.0000f, 20.8630f, 0.0000f},
        {0.0000f, -162.0032f, 0.0000f},
        {0.0000f, 79.1369f, 0.0000f},
        {0.0000f, 166.0404f, 0.0000f},
        {0.0000f, 76.9837f, 0.0000f}};

    std::vector<glm::vec3> scales = {
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f}};

    auto meshes = std::vector<std::shared_ptr<Mesh>>();

    for (size_t i = 0; i < positions.size(); ++i)
    {
      auto house = std::make_shared<House2Mesh>();
      house->transform.setPosition(positions[i]);
      house->transform.setRotation(rotations[i]);
      house->transform.setScale(scales[i]);
      meshes.push_back(house);
    }

    this->setMeshes(meshes);
  }
};

#endif // HOUSE2OBJECT_HPP