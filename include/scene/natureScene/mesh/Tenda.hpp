#ifndef TENDAMESH_HPP
#define TENDAMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/TendaMaterial.hpp"

class TendaMesh : public Mesh {
public:
    TendaMesh() : Mesh("assets/models/tenda.obj") {
      
      TendaMaterial material;
      this->setMaterial(std::make_shared<TendaMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

#endif // TENDAMESH_HPP
