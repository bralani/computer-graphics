#ifndef ROCKS_HPP
#define ROCKS_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Rock.hpp"

class Rocks : public Object
{
public:
  Rocks() : Object()
  {
    auto rock1 = std::make_shared<RockMesh>();
    rock1->transform.setPosition(glm::vec3(5.0f, 0.0f, 0.0f));

    auto rock2 = std::make_shared<RockMesh>();

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(rock1);
    meshes.push_back(rock2);

    this->setMeshes(meshes);
  }

};

#endif // ROCKS_HPP