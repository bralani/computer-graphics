#ifndef GROUNDS_HPP
#define GROUNDS_HPP

#include <vector>
#include <memory>
#include "lights/PointLight.hpp"
#include "scene/natureScene/mesh/Ground.hpp"
#include "scene/natureScene/mesh/Water.hpp"
#include "scene/natureScene/mesh/Island.hpp"
#include "scene/natureScene/mesh/Cavern.hpp"
#include "scene/natureScene/mesh/Bridge.hpp"
#include "scene/natureScene/mesh/Church.hpp"

#include "scene/natureScene/object/Pozzo.hpp"
#include "scene/natureScene/object/Molo.hpp"
#include "scene/natureScene/object/Fienile.hpp"
#include "scene/natureScene/object/Fabbro.hpp"
#include "scene/natureScene/object/House2.hpp"
#include "scene/natureScene/object/House3.hpp"
#include "scene/natureScene/object/House4.hpp"
#include "scene/natureScene/object/Barrels.hpp"
#include "scene/natureScene/object/Fences.hpp"
#include "scene/natureScene/object/Fires.hpp"
#include "scene/natureScene/object/Tenda.hpp"


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
    objectschildren.push_back(std::make_shared<Molo>());
    objectschildren.push_back(std::make_shared<Fienile>());
    objectschildren.push_back(std::make_shared<Fabbri>());
    objectschildren.push_back(std::make_shared<House2>());
    objectschildren.push_back(std::make_shared<House3>());
    objectschildren.push_back(std::make_shared<House4>());
    objectschildren.push_back(std::make_shared<Barrels>());
    objectschildren.push_back(std::make_shared<Fences>());
    objectschildren.push_back(std::make_shared<Fires>());
    objectschildren.push_back(std::make_shared<Tenda>());

    this->setChildrenObjects(objectschildren);
  }

};

#endif // GROUNDS_HPP