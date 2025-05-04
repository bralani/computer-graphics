#ifndef GROUNDS_HPP
#define GROUNDS_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Ground.hpp"
#include "scene/natureScene/mesh/Water.hpp"
#include "scene/natureScene/mesh/Island.hpp"
#include "scene/natureScene/mesh/Cavern.hpp"

class Grounds : public Object
{
public:
  Grounds() : Object()
  {
    auto groundMesh = std::make_shared<GroundMesh>();
    auto waterMesh = std::make_shared<WaterMesh>();
    auto islandMesh = std::make_shared<IslandMesh>();
    auto cavernMesh = std::make_shared<CavernMesh>();

    this->transform.setScale(glm::vec3(3.0f));
    this->transform.setPosition(glm::vec3(0.0f, -55.0f, 0.0f));

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(groundMesh);
    meshes.push_back(waterMesh);
    meshes.push_back(islandMesh);
    meshes.push_back(cavernMesh);

    this->setMeshes(meshes);
  }

};

#endif // GROUNDS_HPP