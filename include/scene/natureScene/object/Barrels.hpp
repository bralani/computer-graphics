#ifndef BARRELOBJECT_HPP
#define BARRELOBJECT_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Barrel.hpp"

class Barrels : public Object
{
public:
  Barrels() : Object()
  {
    std::vector<glm::vec3> positions = {
        {-21.3073f, -5.6057f, 133.1693f},
        {-76.4673f, -6.6252f, 115.4748f},
        {7.2166f, -6.5737f, 148.7249f},
        {38.3724f, -7.7979f, 146.7535f},
        {165.6040f, -8.7590f, 8.1228f},
        {150.2046f, -9.5266f, 78.3874f},
        {150.2046f, -9.5266f, 80.9224f},
        {-7.7407f, -2.4030f, 19.1373f},
        {-97.9068f, -10.3876f, 4.8458f}};

    std::vector<glm::vec3> rotations = {
        {7.6584f, 11.0591f, -74.6419f},
        {7.6584f, 11.0591f, -74.6419f},
        {7.6584f, 11.0591f, -74.6419f},
        {7.6584f, 11.0591f, -74.6419f},
        {7.6584f, 11.0591f, -74.6419f},
        {7.6584f, 11.0591f, -74.6419f},
        {7.6584f, 11.0591f, -74.6419f},
        {7.6584f, 11.0591f, -74.6419f},
        {7.6584f, 11.0591f, -74.6419f}};

    std::vector<glm::vec3> scales = {
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f}};
    for (size_t i = 0; i < positions.size(); ++i)
    {
      auto barrelInstance = std::make_shared<BarrelMesh>();
      glm::vec3 pos = positions[i];
      glm::vec3 rot = rotations[i];
      glm::vec3 scale = scales[i];

      barrelInstance->transform.setPosition(pos);
      barrelInstance->transform.setRotation(rot);
      barrelInstance->transform.setScale(scale);

      meshes.push_back(barrelInstance);
    }
    this->setMeshes(meshes);
  }
};

#endif // BARRELOBJECT_HPP