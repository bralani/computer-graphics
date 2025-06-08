#ifndef WALLSOBJECT_HPP
#define WALLSOBJECT_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Walls.hpp"

class Walls : public Object
{
public:
  Walls() : Object()
  {
    auto wall = std::make_shared<WallMesh>();
    auto gate = std::make_shared<CancelloMesh>();

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(wall);
    meshes.push_back(gate);

    this->setMeshes(meshes);
  }

};

#endif // WALLSOBJECT_HPP