#ifndef COLLISIONWATER_HPP
#define COLLISIONWATER_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Ground.hpp"
#include "scene/natureScene/mesh/Water.hpp"
#include "scene/natureScene/mesh/Island.hpp"
#include "scene/natureScene/mesh/Cavern.hpp"

class CollisionWater : public Object
{
public:
  CollisionWater() : Object()
  {
    auto groundCollisionMesh = std::make_shared<GroundCollisionMesh>();

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(groundCollisionMesh);

    this->setMeshes(meshes);
  }

};

#endif // COLLISIONWATER_HPP