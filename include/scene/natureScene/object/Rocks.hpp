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
    rock1->transform.setPosition(glm::vec3(0.0, 0.4, 0.0));


    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(rock1);

    this->setMeshes(meshes);
  }

};

#endif // ROCKS_HPP