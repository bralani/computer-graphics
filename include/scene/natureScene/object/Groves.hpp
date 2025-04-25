#ifndef GROVES_HPP
#define GROVES_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Grove.hpp"

class Groves : public Object
{
public:
  Groves() : Object()
  {
    auto groundMesh = std::make_shared<GroveMesh>();

    groundMesh->transform.setPosition(glm::vec3(6.0, -11, 0.0));

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(groundMesh);

    this->setMeshes(meshes);
  }

};

#endif // GROVES_HPP