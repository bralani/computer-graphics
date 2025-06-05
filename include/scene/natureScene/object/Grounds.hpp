#ifndef GROUNDS_HPP
#define GROUNDS_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Ground.hpp"
#include "scene/natureScene/mesh/Water.hpp"
#include "scene/natureScene/mesh/Island.hpp"
#include "scene/natureScene/mesh/Cavern.hpp"
#include "scene/natureScene/mesh/Bridge.hpp"
#include "scene/natureScene/mesh/Church.hpp"

#include "scene/natureScene/object/Pozzo.hpp"
#include "scene/natureScene/object/Mulino.hpp"
#include "scene/natureScene/object/Molo.hpp"

class Grounds : public Object
{
public:
  Grounds() : Object()
  {
    auto groundMesh = std::make_shared<GroundMesh>();
    auto waterMesh = std::make_shared<WaterMesh>();
    auto islandMesh = std::make_shared<IslandMesh>();
    auto cavernMesh = std::make_shared<CavernMesh>();
    auto bridgeMesh = std::make_shared<BridgeMesh>();
    auto churchMesh = std::make_shared<ChurchMesh>();

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(groundMesh);
    meshes.push_back(waterMesh);
    meshes.push_back(islandMesh);
    meshes.push_back(cavernMesh);
    meshes.push_back(bridgeMesh);
    meshes.push_back(churchMesh);

    this->setMeshes(meshes);
    auto objectschildren = std::vector<std::shared_ptr<Object>>();
    objectschildren.push_back(std::make_shared<Pozzo>());
    objectschildren.push_back(std::make_shared<Mulino>());
    objectschildren.push_back(std::make_shared<Molo>());

    this->setChildrenObjects(objectschildren);
  }

};

#endif // GROUNDS_HPP