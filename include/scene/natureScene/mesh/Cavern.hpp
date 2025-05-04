#ifndef CAVERNMESH_HPP
#define CAVERNMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/CavernMaterial.hpp"

class CavernMesh : public Mesh {
public:
    CavernMesh() : Mesh("assets/models/cavern.obj") {
      
      CavernMaterial material;
      this->setMaterial(std::make_shared<CavernMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

#endif // CAVERNMESH_HPP
