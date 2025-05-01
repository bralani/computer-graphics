#ifndef TREASURE_HPP
#define TREASURE_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Chest.hpp"

class Treasure : public Object
{
public:
  Treasure() : Object()
  {
    auto chestMesh = std::make_shared<ChestMesh>();
    auto chestGoldMesh = std::make_shared<ChestGoldMesh>();


    this->transform.setPosition(glm::vec3(5.0f, 3.0f, 0.0f));

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(chestMesh);
    meshes.push_back(chestGoldMesh);

    this->setMeshes(meshes);
  }

};

#endif // TREASURE_HPP