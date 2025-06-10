#ifndef POZZOOBJECT_HPP
#define POZZOOBJECT_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Pozzo.hpp"

class Pozzo : public Object
{
public:
  Pozzo() : Object()
  {
    auto muretto = std::make_shared<MurettoPozzoMesh>();
    auto legno = std::make_shared<LegnoPozzoMesh>();
    auto secchio = std::make_shared<SecchioMesh>();
    auto acqua = std::make_shared<AcquaPozzoMesh>();

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(muretto);
    meshes.push_back(legno);
    meshes.push_back(secchio);
    meshes.push_back(acqua);

    this->setMeshes(meshes);

    transform.setPosition(glm::vec3(0.0f, -0.5f, 0.0f));
  }

};

#endif // POZZOOBJECT_HPP