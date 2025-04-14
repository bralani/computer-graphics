#ifndef GROUNDS_HPP
#define GROUNDS_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Ground.hpp"

class Grounds : public Object
{
public:
  Grounds() : Object()
  {
    auto groundMesh = std::make_shared<GroundMesh>();

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(groundMesh);

    this->setMeshes(meshes);
  }

};

#endif // GROUNDS_HPP