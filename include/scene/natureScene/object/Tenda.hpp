#ifndef TENDA_OBJECT
#define TENDA_OBJECT

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Tenda.hpp"
#include <cmath>

class Tenda : public Object
{
public:
  Tenda() : Object()
  {
    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    auto tenda = std::make_shared<TendaMesh>();
    tenda->transform.setPosition(glm::vec3(49.5854, -4.95031, 19.852));
    tenda->transform.setRotation(glm::vec3(90.0f, -5.14, 0.0f));
    meshes.push_back(tenda);

    this->setMeshes(meshes);
  }

};

#endif // TENDA_OBJECT