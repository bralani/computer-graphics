#ifndef CHURCHMESH_HPP
#define CHURCHMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/ChurchMaterial.hpp"

class ChurchMesh : public Mesh {
public:
    ChurchMesh() : Mesh("assets/models/church.obj") {
      
      ChurchMaterial material;
      this->setMaterial(std::make_shared<ChurchMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

#endif // CHURCHMESH_HPP
