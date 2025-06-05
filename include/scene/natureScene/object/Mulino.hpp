#ifndef MULINOOBJECT_HPP
#define MULINOOBJECT_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Mulino.hpp"

class Mulino : public Object
{
public:
  Mulino() : Object()
  {
    auto ruota = std::make_shared<RuotaMulinoMesh>();

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(ruota);

    this->setMeshes(meshes);
  }

};

#endif // MULINOOBJECT_HPP