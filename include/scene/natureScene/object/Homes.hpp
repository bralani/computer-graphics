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
        {60.5884f, -9.1375f, 158.9125f},
        {-80.1233f, -7.8061f, 122.3405f},
        {118.2782f, -5.4700f, -2.5687f},
        {46.8042f, -9.1375f, 156.0304f}};

    std::vector<glm::vec3> rotations = {
        {90.0000f, 77.2055f, 0.0000f},
        {88.9294f, 73.2540f, 0.3222f},
        {90.2492f, -81.4248f, -1.2107f},
        {90.0000f, 77.2055f, 0.0000f}};

    std::vector<glm::vec3> scales = {
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f},
        {1.0000f, 1.0000f, 1.0000f}};

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