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

    this->transform.setScale(glm::vec3(3.0f));
    this->transform.setPosition(glm::vec3(0.0f, -55.0f, 0.0f));

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(groundCollisionMesh);

    this->setMeshes(meshes);
  }

};

#endif // COLLISIONWATER_HPP