#ifndef HOMES_HPP
#define HOMES_HPP

#include <vector>
#include <memory>
#include <fstream>
#include <random>
#include "scene/natureScene/mesh/Home.hpp"
#include "objects/Object.hpp"
#include "utilities/Input.hpp"

class Homes : public Object
{
public:
  Homes() : Object()
  {

    std::vector<glm::vec3> positions = {
        {58.1328f, -9.1375f, 157.2755f},
        {32.1078f, -8.7110f, 150.4863f},
        {1.3304f, -7.5237f, 142.7920f},
        {-28.7681f, -6.6137f, 135.3239f},
        {-58.1876f, -7.1128f, 126.9507f},
        {-80.8181f, -7.7331f, 118.8037f}};

    std::vector<glm::vec3> rotations = {
        {90.0000f, -73.2510f, 0.0000f},
        {90.0000f, -73.2510f, 0.0000f},
        {90.0000f, -73.2510f, 0.0000f},
        {91.3826f, -73.0981f, -1.5553f},
        {90.0000f, -73.2510f, 0.0000f},
        {90.0000f, -73.2510f, 0.0000f}};

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.reserve(positions.size());

    for (size_t i = 0; i < positions.size(); ++i)
    {
      auto home = std::make_shared<HomeMesh>();
      glm::vec3 pos = positions[i];
      glm::vec3 rot = rotations[i];

      home->transform.setPosition(pos);
      home->transform.setRotation(rot);

      meshes.push_back(home);
    }

    this->setMeshes(meshes);
  }
};

#endif // HOMES_HPP