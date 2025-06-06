#ifndef FABBROOBJECT_HPP
#define FABBROOBJECT_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Fabbro.hpp"

class Fabbro : public Object
{
public:
  Fabbro() : Object()
  {
    auto edificio = std::make_shared<LegnoFabbro>();
    auto spade = std::make_shared<SpadeFabbro>();
    auto scudi = std::make_shared<ScudiFabbro>();

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(edificio);
    meshes.push_back(spade);
    meshes.push_back(scudi);

    this->setMeshes(meshes);
  }

};

class Fabbri : public Object
{
public:
  Fabbri() : Object()
  {
    auto objectschildren = std::vector<std::shared_ptr<Object>>();

    auto fabbro1 = std::make_shared<Fabbro>();
    fabbro1->transform.setPosition(glm::vec3(-14.1404f, 0.590407f, 11.9116));
    fabbro1->transform.setRotation(glm::vec3(0, -13.7418f, 0));

    auto fabbro2 = std::make_shared<Fabbro>();
    fabbro2->transform.setPosition(glm::vec3(29.78f, -5.2505, 152.632));
    fabbro2->transform.setRotation(glm::vec3(0.0f, -197.892, 0.0f));

    objectschildren.push_back(fabbro1);
    objectschildren.push_back(fabbro2);

    this->setChildrenObjects(objectschildren);
  }

};

#endif // FABBROOBJECT_HPP