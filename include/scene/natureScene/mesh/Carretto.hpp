#ifndef CARRETTO_MESH_HPP
#define CARRETTO_MESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/CarrettoMaterial.hpp"

class CarrettoMesh : public Mesh {
public:
    CarrettoMesh() : Mesh("assets/models/carretto.obj") {
      
      CarrettoMaterial material;
      this->setMaterial(std::make_shared<CarrettoMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

#endif // CARRETTO_MESH_HPP
