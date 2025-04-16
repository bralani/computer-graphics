#ifndef BOAT_HPP
#define BOAT_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Boat.hpp"

class Boat : public Object
{
public:
  Boat() : Object()
  {
    auto boatMesh = std::make_shared<BoatMesh>();

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(boatMesh);

    this->setMeshes(meshes);
  }

};

#endif // BOAT_HPP