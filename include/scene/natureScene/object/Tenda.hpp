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

    auto tenda2 = std::make_shared<TendaMesh>();
    tenda2->transform.setPosition(glm::vec3(13.5176, -4.13593, 14.1644));
    tenda2->transform.setRotation(glm::vec3(90.0f, -16.6, 0.0f));
    meshes.push_back(tenda2);


    this->setMeshes(meshes);
  }

};

#endif // TENDA_OBJECT