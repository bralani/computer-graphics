#ifndef FIENILEOBJECT_HPP
#define FIENILEOBJECT_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Fienile.hpp"

class Fienile : public Object
{
public:
  Fienile() : Object()
  {
    auto edificio = std::make_shared<EdificioFienile>();
    auto tettoOpacity = std::make_shared<TettoOpacity>();
    auto tettoNoOpacity = std::make_shared<TettoNoOpacity>();
    auto tetto3 = std::make_shared<Tetto3Fienile>();

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(edificio);
    meshes.push_back(tettoOpacity);
    meshes.push_back(tettoNoOpacity);
    meshes.push_back(tetto3);

    this->setMeshes(meshes);
  }

};

#endif // FIENILEOBJECT_HPP